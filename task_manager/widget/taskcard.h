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
    void enterEvent(QEnterEvent*) override;
    void leaveEvent(QEvent*) override;
    void paintEvent(QPaintEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;//probably neeed to remove

signals:
    void doubleClicked(Task* task);//probably neeed to remove

private:
    bool m_hovered = false;
    void buildUi();
    Task* m_task;
    QLabel* m_nameLabel;//probably neeed to remove
    QLabel* m_priorityLabel;//probably neeed to remove
    QLabel* m_durationLabel;//probably neeed to remove
    QLabel* m_statusLabel;//probably neeed to remove
};
#endif // TASKCARD_H
