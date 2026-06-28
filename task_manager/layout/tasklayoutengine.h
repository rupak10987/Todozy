#ifndef TASKLAYOUTENGINE_H
#define TASKLAYOUTENGINE_H
#include<QRect>
#include<QHash>
class Task;
class TaskCard;
class TaskLayoutEngine
{
public:
    TaskLayoutEngine();
    QHash<Task*, QRect> calculate(Task* root);
protected:
private:
    void layoutChildren(Task* root, QHash<Task*, QRect>& layout);
};
#endif // TASKLAYOUTENGINE_H
