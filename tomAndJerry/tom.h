#ifndef TOM_H
#define TOM_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>


class Tom: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT;
private:
    char direction;
    int row1, column1;
    int data1[15][15];
public:
    Tom(int initialRow, int initialColumn, int d[15][15]);
    void setRow1(int newRow1);
    int getRow1();
    void setColumn1(int newColumn1);
    int getColumn1();
public slots:
    void keyPressEvent(QKeyEvent * event);
    void move();
};

#endif // TOM_H
