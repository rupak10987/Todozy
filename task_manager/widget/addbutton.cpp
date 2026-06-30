#include"./addbutton.h"
#include"../task/task.h"
#include <qevent.h>
#include <qpainter.h>
#include "../layoutconstant.h"

AddButton::AddButton(Task* task, QWidget* parent):QWidget(parent),m_parentTask(task)
{
    setFixedSize(34,34);
    setCursor(Qt::PointingHandCursor);
}
void AddButton::enterEvent(QEnterEvent*)
{
    m_hovered = true;
    update();
}

void AddButton::leaveEvent(QEvent*)
{
    m_hovered = false;
    update();
}
void AddButton::mousePressEvent(QMouseEvent* e)
{
    if(e->button()==Qt::LeftButton)
        emit clicked(m_parentTask);
}
void AddButton::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing,true);

    QColor bg =
        m_hovered ?
            LayoutConstant::AccentColor :
            LayoutConstant::SurfaceColor;

    QColor plus =
        m_hovered ?
            LayoutConstant::TextColor :
            LayoutConstant::AccentColor;

    p.setBrush(bg);

    p.setPen(QPen(LayoutConstant::AccentColor,2));

    p.drawEllipse(rect().adjusted(1,1,-1,-1));

    p.setPen(QPen(plus,2,Qt::SolidLine,Qt::RoundCap));

    int cx = width()/2;
    int cy = height()/2;

    int arm = 7;

    p.drawLine(cx-arm,cy,cx+arm,cy);

    p.drawLine(cx,cy-arm,cx,cy+arm);
}