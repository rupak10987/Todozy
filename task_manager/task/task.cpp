#include "task.h"
#include <QUuid>

Task::Task(QString name)
{
    this->name = name;
    this->id = QUuid::createUuid().toString();
    this->priority = "None";
    this->duration = "";
    this->status = "Pending";
    this->parent = nullptr;

}

Task::~Task()
{
    for(auto &c:children)
        delete c;
}

void Task::addChild(Task* child)
{
    if(!child)
        return;

    child->parent = this;

    children.push_back(child);
}

void Task::removeChild(Task* child)
{
    children.removeOne(child);

    if(child)
        child->parent = nullptr;
}

QVector<Task*> Task::ancestors() const //for breadcrumb section
{
    QVector<Task*> result;

    Task* current = parent;

    while(current)
    {
        result.push_front(current);

        current = current->parent;
    }

    return result;
}

QString Task::path() const
{
    QStringList parts;

    const Task* current = this;

    while(current)
    {
        parts.prepend(current->name);

        current = current->parent;
    }

    return parts.join("/");
}