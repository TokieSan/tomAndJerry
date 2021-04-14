#include "jerry.h"

jerry::jerry(int initialRow, int initialColumn, int d[15][15])
{
    for(int i = 0; i<15; i++)
        for(int j = 0; j<15; j++)
            data4[i][j] = d[i][j];
    row4 = initialRow;
    column4 = initialColumn;
    QPixmap jer("Jerry3.png");
    jer = jer.scaledToWidth(50);
    jer = jer.scaledToHeight(50);
    setPixmap(jer);
    setPos(25+50*column4, 25+50*row4);
}
void jerry::setRow4(int newRow4)
{
    row4 = newRow4;
}
int jerry::getRow4()
{
    return row4;
}
void jerry::setColumn4(int newColumn4)
{
    column4 = newColumn4;
}
int jerry::getColumn4()
{
    return column4;
}
void jerry::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Up && data4[row4-1][column4] != -1)
        row4--;

    else if(event->key() == Qt::Key_Down && data4[row4+1][column4] != -1)
        row4++;

    else if(event->key() == Qt::Key_Right && data4[row4][column4+1] != -1)
        column4++;

    else if(event->key() == Qt::Key_Left && data4[row4][column4-1] != -1)
        column4--;

    setPos(25+50*column4, 25+50*row4);

    QList<QGraphicsItem*> items = collidingItems();

    for(int i = 0; i<items.size(); i++)
    {
        if(typeid(*items[i]) == typeid(cheese))
        {
            scene()->removeItem(items[i]);
            QPixmap jerr("JerryCheese.png");
            jerr = jerr.scaledToWidth(50);
            jerr = jerr.scaledToHeight(50);
            setPixmap(jerr);
            setPos(25+50*column4, 25+50*row4);

            if(row4 == 7 && column4 == 7)
            {
                QPixmap jer("Jerry3.png");
                jer = jer.scaledToWidth(50);
                jer = jer.scaledToHeight(50);
                setPixmap(jer);
                setPos(25+50*column4, 25+50*row4);
            }
        }
        else if(typeid(*items[i]) == typeid(pellet))
        {
            scene()->removeItem(items[i]);
        }
    }
}

