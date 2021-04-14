#ifndef CHEESE_H
#define CHEESE_H

#include <QGraphicsPixmapItem>
class cheese:public QGraphicsPixmapItem
{
private:
    int row2, column2;
public:
    cheese(int initialRow, int initialColumn);
    void setRow2(int newRow2);
    int getRow2();
    void setColumn2(int newColumn2);
    int getColumn2();
};
#endif // CHEESE_H
