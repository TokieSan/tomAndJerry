#ifndef PELLET_H
#define PELLET_H
#include <QGraphicsPixmapItem>


class pellet:public QGraphicsPixmapItem
{
private:
    int row3, column3;
public:
    pellet(int initialRow, int initialColumn);
    void setRow3(int newRow3);
    int getRow3();
    void setColumn3(int newColumn3);
    int getColumn3();
};


#endif // PELLET_H
