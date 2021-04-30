#ifndef INFO_H
#define INFO_H

#include <QWidget>
#include <QtGui>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QList>
#include "cheese.h"
#include <QGraphicsScene>
#include "jerry.h"

class info: public QGraphicsTextItem
{
private:
public:
    info();
    void doTheThing(jerry *jer);
};

#endif // INFO_H
