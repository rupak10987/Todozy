#ifndef TASKCANVAS_H
#define TASKCANVAS_H
#include<QWidget>
#include <QPainter>
class Task;
class TaskCard;
class TaskCanvas: public QWidget
{
Q_OBJECT
public:
    explicit TaskCanvas(QWidget* parent = nullptr);
    void setRoot(Task* task);
protected:
    void resizeEvent(QResizeEvent* event) override;
     void paintEvent(QPaintEvent* event) override;
private:
    void rebuild();
    Task* m_root;
    QHash<Task*, TaskCard*> m_hash;
    QList<TaskCard*> m_cards;

};
#endif // TASKCANVAS_H
