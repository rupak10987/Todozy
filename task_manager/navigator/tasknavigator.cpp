#include"../navigator/tasknavigator.h"
#include"../task/task.h"
TaskNavigator::TaskNavigator(QObject* parent):QObject(parent)
{
    m_currentRoot = nullptr;
}
void TaskNavigator::setRoot(Task* root)
{
    m_currentRoot = root;

    emit rootChanged(m_currentRoot);
}
Task* TaskNavigator::currentRoot() const
{
    return m_currentRoot;
}
void TaskNavigator::navigateTo(Task* task)
{
    if(!task)
        return;

    m_currentRoot = task;

    emit rootChanged(m_currentRoot);
}
void TaskNavigator::goUp()
{
    if(!m_currentRoot)
        return;
    if(m_currentRoot->parent)
    {
        m_currentRoot = m_currentRoot->parent;
        emit rootChanged(m_currentRoot);
    }
}