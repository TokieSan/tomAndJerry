#include "cheese.h"

cheese::cheese(int initialRow, int initialColumn)
{
    row2 = initialRow;
    column2 = initialColumn;
    QPixmap che("Cheese2.png");
    che = che.scaledToWidth(50);
    che = che.scaledToHeight(50);
    setPixmap(che);
    setPos(25+50*column2, 25+50*row2);
}
void cheese::setRow2(int newRow2)
{
    row2 = newRow2;
}
int cheese::getRow2()
{
    return row2;
}
void cheese::setColumn2(int newColumn2)
{
    column2 = newColumn2;
}
int cheese::getColumn2()
{
    return column2;
}
