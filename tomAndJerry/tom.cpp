#include "tom.h"

Tom::Tom(int initialRow, int initialColumn, int d[15][15])
{
    for(int i = 0; i<15; i++)
        for(int j = 0; j<15; j++)
            data1[i][j] = d[i][j];
    row1 = initialRow;
    column1 = initialColumn;
    QPixmap tom("Tom.png");
    tom = tom.scaledToWidth(50);
    tom = tom.scaledToHeight(50);
    setPixmap(tom);
    setPos(25+50*column1, 25+50*row1);
    lastRand=0;
}
void Tom::setRow1(int newRow1)
{
    row1 = newRow1;
}
int Tom::getRow1()
{
    return row1;
}
void Tom::setColumn1(int newColumn1)
{
    column1 = newColumn1;
}
int Tom::getColumn1()
{
    return column1;
}

void Tom::keyPressEvent(QKeyEvent * event)
{

    if(event->key() == Qt::Key_Up)
        move('u');
    else if(event->key() == Qt::Key_Down)
        move('d');
    else if(event->key() == Qt::Key_Right)
       move('r');
    else if(event->key() == Qt::Key_Left)
       move('l');
}
void Tom::move(char d)
{
    if(d == 'u' && data1[row1-1][column1] != -1){
       row1--;
    }

    else if(d == 'd' && data1[row1+1][column1] != -1){
        row1++;
    }

    else if(d == 'r' && data1[row1][column1+1] != -1){
        column1++;
        QPixmap tom("TomRight.png");
        tom = tom.scaledToWidth(50);
        tom = tom.scaledToHeight(50);
        setPixmap(tom);
    }

    else if(d == 'l' && data1[row1][column1-1] != -1){
        column1--;
        QPixmap tom("Tom.png");
        tom = tom.scaledToWidth(50);
        tom = tom.scaledToHeight(50);
        setPixmap(tom);
    }

    setPos(25+50*column1, 25+50*row1);
}
void Tom::randomlyMove(){
    char tmp[] = {'u', 'd', 'r', 'l'};

    int idx = rand()%4;

    move(tmp[idx]);

    lastRand=idx;
}
