#include"./taskcanvas.h"
#include "taskcard.h"
#include"../task/task.h"
TaskCanvas::TaskCanvas(QWidget* parent):QWidget(parent)
{
    m_root = nullptr;
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
    const int leftMargin = 40;
    const int topMargin = 40;
    const int rowSpacing = 120 + 30;
    const int colSpaccing = 180 + 30;
    for(int i = 0; i < m_root->children.size(); ++i)
    {
        Task* task = m_root->children[i];
        TaskCard* card = new TaskCard(task, this);
        card->show();
        m_hash[task] = card;
        card->move(leftMargin,topMargin + i * rowSpacing);
        for(int j = 0;j<task->children.size();++j)
        {
            Task* task_c = task->children[j];
            TaskCard* card_c  = new TaskCard(task_c,this);
            card_c->move(leftMargin+(j+1)*(colSpaccing),topMargin + i * rowSpacing);
            card_c->show();
            m_hash[task_c] = card_c;
        }

        update();
    }
}
void TaskCanvas::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    rebuild();
}

void TaskCanvas::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    for(Task* task: m_hash.keys())//prototype for now
    {
        if(task->parent && m_hash[task->parent])
            painter.drawLine(m_hash[task]->x(),m_hash[task]->y()+60,m_hash[task->parent]->x(),m_hash[task->parent]->y()+60);
    }
    painter.drawLine(20,20,300,20);

}
