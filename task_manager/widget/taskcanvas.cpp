#include"./taskcanvas.h"
#include "taskcard.h"
#include"../task/task.h"
#include "../layout/tasklayoutengine.h"
TaskCanvas::TaskCanvas(QWidget* parent):QWidget(parent)
{
    m_root = nullptr;
    m_engine = new TaskLayoutEngine();
}

void TaskCanvas::setRoot(Task* task)
{
    if(!task)
        return;
    m_root = task;
    rebuild();
}

void TaskCanvas::rebuild()
{
    for(TaskCard *card : m_cards)
    {
        delete card;
    }
    m_cards.clear();
    auto layout = m_engine->calculate(m_root);
    for(auto it = layout.begin(); it!= layout.end(); ++it)
    {
        Task* task = it.key();
        QRect geo = it.value();
        TaskCard* card = new TaskCard(task, this);
        card->setGeometry(geo);
        m_cards.insert(task, card);
        card->show();
    }
    update();
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
