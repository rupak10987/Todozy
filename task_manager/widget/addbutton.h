#ifndef ADDBUTTON_H
#define ADDBUTTON_H
#include<QWidget>
#include<QObject>
class Task;
class AddButton:public QWidget
{
    Q_OBJECT
public:
    explicit AddButton(Task* parentTask, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void enterEvent(QEnterEvent*) override;
    void leaveEvent(QEvent*) override;

private:
    Task* m_parentTask;
    bool m_hovered = false;
signals:
    void clicked(Task* parentTask);
};
#endif // ADDBUTTON_H
