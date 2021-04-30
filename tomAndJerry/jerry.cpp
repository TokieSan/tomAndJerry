#include "jerry.h"
#include <QMessageBox>
#include <QTimer>
#include "info.h"
jerry::jerry(int initialRow, int initialColumn, int d[15][15], QGraphicsScene &scene)
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
    score=0;
    lives=3;
    hasCheese=false;
    invincible=false;
}
bool jerry::checkIfWon(){
    return score==4;
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

    else if(event->key() == Qt::Key_Right && data4[row4][column4+1] != -1){
        column4++;
        QPixmap jer("JerryRight.png");
        QPixmap jer2("JerryCheese.png");
       jer = jer.scaledToWidth(50);
        jer = jer.scaledToHeight(50);
        jer2 = jer2.scaledToWidth(50);
        jer2 = jer2.scaledToHeight(50);
        hasCheese?setPixmap(jer2):setPixmap(jer);
    }

    else if(event->key() == Qt::Key_Left && data4[row4][column4-1] != -1){
        column4--;
        QPixmap jer("Jerry3.png");
        QPixmap jer2("JerryCheeseLeft.png");
        jer = jer.scaledToWidth(50);
        jer = jer.scaledToHeight(50);
        jer2 = jer2.scaledToWidth(50);
        jer2 = jer2.scaledToHeight(50);
        hasCheese?setPixmap(jer2):setPixmap(jer);
    }

    setPos(25+50*column4, 25+50*row4);

    QList<QGraphicsItem*> items = collidingItems();

    if(row4 == 7 && column4 == 7 && hasCheese)
    {
        hasCheese=false;
        score++;
        QPixmap jer("Jerry3.png");
        jer = jer.scaledToWidth(50);
        jer = jer.scaledToHeight(50);
        setPixmap(jer);
        setPos(25+50*column4, 25+50*row4);
        QPixmap che("Cheese2.png");
        che=che.scaledToWidth(50);
        che=che.scaledToHeight(50);
        setPixmap(che);
        QGraphicsPixmapItem ch;
        ch.setPixmap(che);
        scene()->addItem(&ch);
        ch.setPos(25+50*7,25+50*7);

    }
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

            score++;
            hasCheese=true;


        }
        else if(typeid(*items[i]) == typeid(pellet))
        {
            scene()->removeItem(items[i]);
            //invincible
            //maybe add sth in the future to make jerry bigger when invincible
            int cnt = 10;
            invincible=true;
            QTimer cntDown;
             QObject::connect(&cntDown, &QTimer::timeout, [this,&cnt, &cntDown]()->void{
            if(--cnt<0){
                invincible = false;
                cntDown.stop();
            }
                     });
                 cntDown.start(10000);
        }
        else if(typeid(*items[i]) == typeid(Tom)){
            if(!invincible) lives--;
            if(lives<=0){
                //popup window with "You Lost"
                QMessageBox msg;
                msg.setText("You have lost! Starting a new game");
                QTimer cntDown;
                int cnt=10;
                   QObject::connect(&cntDown, &QTimer::timeout, [&msg,&cnt, &cntDown]()->void{
                                        if(--cnt < 0){
                                            cntDown.stop();
                                            msg.close();
                                        }
                                    });
                   cntDown.start(1000);
                   msg.exec();
            }
        }
    }
}

