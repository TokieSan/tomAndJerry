#include "pellet.h"

pellet::pellet(int initialRow, int initialColumn)
{
    row3 = initialRow;
    column3 = initialColumn;
    QPixmap pel("PelletWhite.png");
    pel = pel.scaledToWidth(50);
    pel = pel.scaledToHeight(50);
    setPixmap(pel);
    setPos(25+50*column3, 25+50*row3);

}
void pellet::setRow3(int newRow3)
{
    row3 = newRow3;
}
int pellet::getRow3()
{
    return row3;
}
void pellet::setColumn3(int newColumn3)
{
    column3 = newColumn3;
}
int pellet::getColumn3()
{
    return column3;
}
