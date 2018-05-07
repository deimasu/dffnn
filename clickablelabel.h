#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include <QtCore>
#include <QLabel>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = 0);
    ~ClickableLabel();
signals:
    void clicked(QMouseEvent* event);
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif
