#ifndef JERRY_H
#define JERRY_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QList>
#include "cheese.h"
#include <QGraphicsScene>
#include "pellet.h"
#include "tom.h"

class jerry: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT;
private:
    int row4, column4;
    int data4[15][15];
public:
    jerry(int initialRow, int initialColumn, int d[15][15]);
    void setRow4(int newRow4);
    int getRow4();
    void setColumn4(int newColumn4);
    int getColumn4();
private slots:
    void keyPressEvent(QKeyEvent * event);

};

#endif // JERRY_H