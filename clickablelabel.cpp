#include "clickablelabel.h"
#include "mainwindow.h"

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{
    connect(this, SIGNAL(clicked(QMouseEvent*)) , this, SLOT(MainWindow::on_points_label_clicked()));
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
