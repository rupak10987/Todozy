#include"./taskcard.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "../task/task.h"
#include <QPainter>
#include"../layoutconstant.h"

TaskCard::TaskCard(Task* task, QWidget* parent):QFrame(parent),m_task(task)
{
    setAttribute(Qt::WA_Hover);
    setMouseTracking(true);
    buildUi();
}

void TaskCard::buildUi()
{
    update();
    // setFrameShape(QFrame::Box);
    // setMinimumSize(180,120);
    // QVBoxLayout* layout = new QVBoxLayout(this);
    // m_nameLabel = new QLabel(m_task->name);
    // m_priorityLabel = new QLabel("Priority: " + m_task->priority);
    // m_durationLabel = new QLabel("Duration: " + m_task->duration);
    // m_statusLabel = new QLabel("Status: " + m_task->status);
    // layout->addWidget(m_nameLabel);
    // layout->addWidget(m_priorityLabel);
    // layout->addWidget(m_durationLabel);
    // layout->addWidget(m_statusLabel);
}
Task* TaskCard::task() const
{
    return m_task;
}

void TaskCard::mouseDoubleClickEvent(
    QMouseEvent* event)
{
    emit doubleClicked(m_task);

    QFrame::mouseDoubleClickEvent(event);
}
void TaskCard::enterEvent(QEnterEvent*)
{
    m_hovered = true;
    update();
}

void TaskCard::leaveEvent(QEvent*)
{
    m_hovered = false;
    update();
}

void TaskCard::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect r = rect().adjusted(0,0,-1,-1);

    // ================= BACKGROUND =================
    QColor bg = m_hovered
                    ? LayoutConstant::CardBgHover
                    : LayoutConstant::CardBg;

    p.setPen(Qt::NoPen);
    p.setBrush(bg);
    p.drawRoundedRect(r, 10, 10);

    // ================= BORDER =================
    QColor border = m_hovered
                        ? LayoutConstant::CardBorderHover
                        : LayoutConstant::CardBorder;

    p.setPen(QPen(border, 1));
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(r, 10, 10);

    // ================= TEXT COLOR =================
    QColor textColor = m_hovered
                           ? LayoutConstant::CardTextHover
                           : LayoutConstant::CardText;

    // ================= PRIORITY STRIP =================
    QColor strip = LayoutConstant::priorityColor(m_task->priority);

    p.fillRect(QRect(0,0,8,height()), strip);

    // ================= TITLE =================
    QFont f = p.font();
    f.setBold(true);
    f.setPointSize(11);
    p.setFont(f);

    p.setPen(textColor);
    p.drawText(18, 25, m_task->name);

    // ================= PRIORITY TEXT =================
    f.setBold(false);
    f.setPointSize(9);
    p.setFont(f);

    p.setPen(textColor);

    int x = LayoutConstant::TextLeft;
    int y = 55;

    p.drawText(x, y, "Priority :");

    QFontMetrics fm(p.font());
    int valX = x + fm.horizontalAdvance("Priority : ");
    p.setPen(LayoutConstant::priorityColor(m_task->priority));
    p.drawText(valX, y, m_task->priority);

    // ================= STATUS =================
    y += 22;

    p.setPen(textColor);
    p.drawText(x, y, "Status :");

    valX = x + fm.horizontalAdvance("Status : ");

    p.setPen(LayoutConstant::statusColor(m_task->status));
    p.drawText(valX, y, m_task->status);

    // ================= DURATION =================
    y += 22;

    p.setPen(textColor);
    p.drawText(x, y, "⏱ " + m_task->duration);
}