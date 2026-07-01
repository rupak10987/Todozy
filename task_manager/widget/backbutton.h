#ifndef BACKBUTTON_H
#define BACKBUTTON_H
#include <QPushButton>
#include "../layoutconstant.h"
class BackButton:public QPushButton
{
    Q_OBJECT
public:
    explicit BackButton(QString text, QWidget* parent = nullptr):QPushButton(text,parent)
    {

    }
private:
    bool hovered = false;
protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        emit clicked();
        QPushButton::mousePressEvent(event);
    }
    void enterEvent(QEnterEvent *event) override{hovered = true; update();}
    void leaveEvent(QEvent *event) override{hovered = false; update();}
    void paintEvent(QPaintEvent* event) override
    {
        if(hovered)
            this->setStyleSheet(QString("color: %1;").arg(LayoutConstant::AccentColor.name()));
        else
            this->setStyleSheet("color: white;");
        QPushButton::paintEvent(event);
    }
signals:
    void clicked();
};
#endif // BACKBUTTON_H
