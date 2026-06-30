#ifndef TASKCANVAS_H
#define TASKCANVAS_H
#include<QWidget>
#include <QPainter>
#include <QPen>
class AddButton;
class TaskLayoutEngine;
class Task;
class TaskCard;
class TaskCanvas: public QWidget
{
Q_OBJECT
public:
    explicit TaskCanvas(QWidget* parent = nullptr);
    void setRoot(Task* task);
    TaskLayoutEngine* m_engine;
    void onTaskDoubleClicked(Task* task);
protected:
     void paintEvent(QPaintEvent* event) override;

private:
    void rebuild();
    Task* m_root;
    QHash<Task*, TaskCard*> m_cards;
    QVector<AddButton*> m_addButtons;
    void onAddButtonClicked(Task* task);
signals:
    void navigateRequested(Task* task);
};
#endif // TASKCANVAS_H
