#ifndef TASKNAVIGATOR_H
#define TASKNAVIGATOR_H
#include <QObject>
class Task;
class TaskNavigator: public QObject
{
    Q_OBJECT
public:
    explicit TaskNavigator(QObject *parent = nullptr);
    void setRoot(Task* root);
    Task* currentRoot() const;
    void navigateTo(Task* task);
    void goUp();
private:
    Task* m_currentRoot;
signals:
    void rootChanged(Task* newRoot);

};
#endif // TASKNAVIGATOR_H
