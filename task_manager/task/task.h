#ifndef TASK_H
#define TASK_H

#include <Qstring>
#include <QVector>
class Task
{
public:
    QString id;
    QString name;
    QString priority;
    QString duration;
    QString status;
    Task* parent;
    QVector<Task*> children;
    Task(QString name);
    ~Task();
    void addChild(Task* child);
    void removeChild(Task* child);
    QVector<Task*> ancestors() const;
    QString path() const;
};
#endif // TASK_H