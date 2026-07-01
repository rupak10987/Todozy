#include "./breadcrumb.h"
#include "../task/task.h"
#include <QHBoxLayout>


BreadCrumb::BreadCrumb(QWidget* parent, Task* task):QWidget(parent),m_task(task)
{
    m_layout = nullptr;
    buildBreadCrumb();
}
void BreadCrumb::setTask(Task* task)
{
    m_task = task;
    buildBreadCrumb();
}
void BreadCrumb::buildBreadCrumb()
{
    if(!m_task)
        return;
    if(m_layout == nullptr)
    {
        m_layout = new QHBoxLayout(this);
        this->setLayout(m_layout);
    }
    while (QLayoutItem* item = m_layout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
    }
    for(ClickableLabel* button:m_buttons)
    {
        button->hide();
        button->deleteLater();
    }
    m_buttons.clear();
    m_layout->setContentsMargins(40, 0, 0, 0);
    m_layout->setSpacing(0);
    QVector<Task*> ancestors = m_task->ancestors();
    for(Task* t:ancestors)
    {
        ClickableLabel* button = new ClickableLabel(t->name, this);
        connect(button, &ClickableLabel::labelClicked, this, [=](){emit navigateTo(t);});
        m_buttons.push_back(button);
        m_layout->addWidget(button);
        QLabel* separator = new QLabel("/",this);
        m_layout->addWidget(separator);
    }
    ClickableLabel* root_button = new ClickableLabel(m_task->name, this);
    connect(root_button, &ClickableLabel::labelClicked, this, [=](){emit navigateTo(m_task);});
    m_buttons.push_back(root_button);
    m_layout->addWidget(root_button);
     m_layout->addStretch(1);
    this->show();
    return;
}