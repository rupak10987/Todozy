#ifndef TASKCARD_H
#define TASKCARD_H
#include<QFrame>
class QLabel;
class Task;
class TaskCard : public QFrame
{
    Q_OBJECT
public:
    explicit TaskCard(Task* task, QWidget* parent = nullptr);
    Task* task() const;
protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override;

signals:
    void doubleClicked(Task* task);

private:
    void buildUi();
    Task* m_task;
    QLabel* m_nameLabel;
    QLabel* m_priorityLabel;
    QLabel* m_durationLabel;
    QLabel* m_statusLabel;
};
#endif // TASKCARD_H
