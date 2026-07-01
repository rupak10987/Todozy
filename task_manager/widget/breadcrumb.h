#ifndef BREADCRUMB_H
#define BREADCRUMB_H
#include<QWidget>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include "../labels/clickablelabel.h"

class Task;
class BreadCrumb:public QWidget
{
    Q_OBJECT;
public:
    explicit BreadCrumb(QWidget* parent = nullptr, Task* task = nullptr);
    void setTask(Task* task);
    void buildBreadCrumb();

protected:

private:
    QHBoxLayout* m_layout;
    QVector<ClickableLabel*> m_buttons;
    Task* m_task;
signals:
    void navigateTo(Task* task);
};
#endif // BREADCRUMB_H
