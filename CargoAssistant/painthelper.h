#ifndef PAINTHELPER_H
#define PAINTHELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

class paintHelper
{
public:
    paintHelper();

public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
};

#endif // PAINTHELPER_H
