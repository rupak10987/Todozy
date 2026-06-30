#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include<QLabel>
#include<QPainter>
#include <qevent.h>
#include "../layoutconstant.h"
class ClickableLabel:public QLabel
{
    Q_OBJECT;
public:
    explicit ClickableLabel(QString text = "-", QWidget* parent = nullptr):QLabel(text,parent)
    {
        update();
    }
private:
    bool hovered = false;
protected:
    void enterEvent(QEnterEvent*) override
    {
        hovered = true;
        update();
    }
    void leaveEvent(QEvent*)override
    {
        hovered = false;
        update();
    }
    void paintEvent(QPaintEvent* event) override
    {

        if(hovered)
            this->setStyleSheet(QString("color: %1;").arg(LayoutConstant::AccentColor.name()));
        else
            this->setStyleSheet("color: white;");
        QLabel::paintEvent(event);
    }
    void mousePressEvent(QMouseEvent* e)override
    {
        if(e->button()==Qt::LeftButton)
            emit labelClicked();
    }
signals:
    void labelClicked();
};
#endif // CLICKABLELABEL_H
