#include"./taskcard.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "../task/task.h"

TaskCard::TaskCard(Task* task, QWidget* parent):QFrame(parent),m_task(task)
{
    buildUi();
}

void TaskCard::buildUi()
{
    setFrameShape(QFrame::Box);
    setMinimumSize(180,120);
    QVBoxLayout* layout = new QVBoxLayout(this);
    m_nameLabel = new QLabel(m_task->name);
    m_priorityLabel = new QLabel("Priority: " + m_task->priority);
    m_durationLabel = new QLabel("Duration: " + m_task->duration);
    m_statusLabel = new QLabel("Status: " + m_task->status);
    layout->addWidget(m_nameLabel);
    layout->addWidget(m_priorityLabel);
    layout->addWidget(m_durationLabel);
    layout->addWidget(m_statusLabel);
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