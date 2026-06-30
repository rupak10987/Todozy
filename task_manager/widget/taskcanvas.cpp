#include"./taskcanvas.h"
#include "addbutton.h"
#include "taskcard.h"
#include"../task/task.h"
#include "../layout/tasklayoutengine.h"
#include "../layoutconstant.h"
#include "../dialogue/taskcreatedialogue.h"
#include <QTimer>
TaskCanvas::TaskCanvas(QWidget* parent):QWidget(parent)
{
    m_root = nullptr;
    m_engine = new TaskLayoutEngine();
}

void TaskCanvas::setRoot(Task* task)
{
    if (!task || task == m_root)
        return;

    m_root = task;

    QTimer::singleShot(0, this, [this]() {
        rebuild();
    });
}

void TaskCanvas::rebuild()
{
    for(AddButton* b : m_addButtons)
    {
        b->hide();
        b->deleteLater();
    }

    m_addButtons.clear();
    for(TaskCard *card : m_cards)
    {
        card->hide();
        card->deleteLater();
    }
    m_cards.clear();
    auto layout = m_engine->calculate(m_root);
    if(layout.isEmpty())
    {
        AddButton* btn = new AddButton(m_root,this);
        m_addButtons.push_back(btn);
        connect(btn,&AddButton::clicked,this,&TaskCanvas::onAddButtonClicked);
        QRect rect = QRect(LayoutConstant::TopMargin/2,LayoutConstant::LeftMargin/2,btn->width()/2,btn->height()/2);
        btn->move(rect.right() + LayoutConstant::ButtonOffset, rect.y() + LayoutConstant::CardHeight/2- btn->height()/2);
        btn->update();
        btn->show();
        update();
        return;
    }
    for(auto it = layout.begin(); it!= layout.end(); ++it)
    {
        Task* task = it.key();
        QRect geo = it.value();
        TaskCard* card = new TaskCard(task, this);
        card->setGeometry(geo);
        m_cards.insert(task, card);
        card->show();
        connect(card, &TaskCard::doubleClicked, this, &TaskCanvas::onTaskDoubleClicked);
        if(!task->children.empty())
        {
            AddButton* btn = new AddButton(task,this);
            m_addButtons.push_back(btn);
            connect(btn,&AddButton::clicked,this,&TaskCanvas::onAddButtonClicked);
            QRect rect = layout[task->children.last()];
            btn->move(rect.right() + LayoutConstant::ButtonOffset, rect.y() + LayoutConstant::CardHeight/2- btn->height()/2);
            btn->update();
            btn->show();
        }
        else if(task->parent == m_root)//only two level
        {
            AddButton* btn = new AddButton(task,this);
            m_addButtons.push_back(btn);
            connect(btn,&AddButton::clicked,this,&TaskCanvas::onAddButtonClicked);
            QRect rect = layout[task];
            btn->move(rect.right() + LayoutConstant::ButtonOffset, rect.y() + LayoutConstant::CardHeight/2- btn->height()/2);
            btn->update();
            btn->show();
        }
    }

    AddButton* btn = new AddButton(m_root,this);
    m_addButtons.push_back(btn);
    Task* lastChild = m_root->children.last();
    connect(btn,&AddButton::clicked,this,&TaskCanvas::onAddButtonClicked);
    QRect rect = layout[lastChild];
    // btn->move(100,100);
    btn->move(rect.x() + LayoutConstant::CardWidth/2- btn->width()/2,rect.bottom() + LayoutConstant::ButtonOffset);
    btn->update();
    btn->show();
    update();
}
void TaskCanvas::onAddButtonClicked(Task* parentTask)
{
    TaskCreateDialog dialog(this);

    if(dialog.exec()!=QDialog::Accepted)
        return;

    Task* task = new Task(dialog.taskName()==""?"Untitled":dialog.taskName());

    task->priority = dialog.priority();

    task->status = dialog.status();

    task->duration = dialog.duration();

    parentTask->addChild(task);

    rebuild();
}
void TaskCanvas::onTaskDoubleClicked(Task* task)
{
    emit navigateRequested(task);
}
void TaskCanvas::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    if (!m_root) return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    QPen linePen(QColor("#BDBDBD"), 1.5, Qt::SolidLine, Qt::FlatCap);
    p.setPen(linePen);
    p.setBrush(Qt::NoBrush);

    QColor dotColor("#0078D4");
    const int DOT_R = 4;

    // Helper: draw a filled dot and restore the line pen
    auto dot = [&](int cx, int cy) {
        p.setPen(Qt::NoPen);
        p.setBrush(QBrush(dotColor));
        p.drawEllipse(QPoint(cx, cy), DOT_R, DOT_R);
        p.setPen(linePen);
        p.setBrush(Qt::NoBrush);
    };

    auto children = m_root->children;
    if (children.isEmpty()) return;

    // ── Vertical spine left of all col-0 (child) cards ────────────────────
    // Spine x = left edge of first child card minus offset.
    // Spine runs straight from mid-Y of first child to mid-Y of last child.
    // Each child gets a horizontal stub: spine_x → card left edge, plus a dot.

    const int SPINE_OFFSET = 22;

    QWidget* firstW = m_cards.value(children.first(), nullptr);
    QWidget* lastW  = m_cards.value(children.last(),  nullptr);
    if (!firstW || !lastW) return;

    int spineX      = firstW->pos().x() - SPINE_OFFSET;
    int spineTop    = firstW->pos().y()  + firstW->height() / 2;
    int spineBottom = lastW->pos().y()   + lastW->height()  / 2;

    p.setPen(linePen);
    if (children.size() > 1)
        p.drawLine(spineX, spineTop, spineX, spineBottom);   // straight vertical

    for (Task* ch : children)
    {
        QWidget* w = m_cards.value(ch, nullptr);
        if (!w) continue;
        int midY  = w->pos().y() + w->height() / 2;
        int leftX = w->pos().x();
        p.setPen(linePen);
        p.drawLine(spineX, midY, leftX, midY);    // horizontal stub
        dot(leftX, midY);                          // dot at card entry
    }

    // ── Horizontal chain for each child's grandchildren ───────────────────
    // All GCs of the same parent share the same row (same Y as parent).
    // So the connection is a straight horizontal chain:
    //
    //   [parent] ──● [gc0] ──● [gc1] ──● [gc2] …
    //
    // Draw:
    //   • one segment: parent right edge → gc[0] left edge
    //   • one segment per consecutive GC pair: gc[i] right → gc[i+1] left
    //   • dot at BOTH ends of every segment

    for (Task* ch : children)
    {
        auto gcs = ch->children;
        if (gcs.isEmpty()) continue;

        QWidget* pw = m_cards.value(ch, nullptr);
        if (!pw) continue;

        int spineY   = pw->pos().y() + pw->height() / 2;   // same Y for all
        int parentRX = pw->pos().x() + pw->width();         // parent right edge

        // Segment: parent right → first GC left
        QWidget* gc0w = m_cards.value(gcs.first(), nullptr);
        if (!gc0w) continue;
        int gc0LX = gc0w->pos().x();

        p.setPen(linePen);
        p.drawLine(parentRX, spineY, gc0LX, spineY);
        dot(parentRX, spineY);   // dot on parent's right edge
        dot(gc0LX,    spineY);   // dot on first GC's left edge

        // Segments between consecutive GCs
        for (int i = 0; i < gcs.size() - 1; i++)
        {
            QWidget* wa = m_cards.value(gcs[i],     nullptr);
            QWidget* wb = m_cards.value(gcs[i + 1], nullptr);
            if (!wa || !wb) continue;

            int aRX  = wa->pos().x() + wa->width();   // right edge of gc[i]
            int bLX  = wb->pos().x();                  // left  edge of gc[i+1]
            // spineY is the same for all — no need to recompute

            p.setPen(linePen);
            p.drawLine(aRX, spineY, bLX, spineY);
            dot(aRX, spineY);   // dot exiting gc[i]
            dot(bLX, spineY);   // dot entering gc[i+1]
        }
    }
}
