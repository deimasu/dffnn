#include "clickablelabel.h"
#include "mainwindow.h"

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{

}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{

    //qDebug() << "click";
    emit clicked(event);
    //return event;
}
