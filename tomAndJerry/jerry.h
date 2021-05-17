#ifndef JERRY_H
#define JERRY_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QList>
#include "cheese.h"
#include <QGraphicsScene>
#include "pellet.h"

class jerry: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT;
private:
    int row4, column4, lives;
    int data4[15][15];
    bool hasCheese, invincible;
    QGraphicsTextItem x;
    QGraphicsTextItem y;
    QGraphicsPixmapItem cheeseR;


public:
    int score;
    jerry(int initialRow, int initialColumn, int d[15][15], QGraphicsScene &scene);
    bool checkIfWon();
    void setRow4(int newRow4);
    int getRow4();
    void setColumn4(int newColumn4);
    int getColumn4();
    int getScore(){return score;}
    void doIt(){invincible =false;}
    void doTheThing(jerry *jer);
    void setItToFls(){invincible=false;}
    void updateLives();
    void updateScore();
    void endGame();
private slots:
    void keyPressEvent(QKeyEvent * event);

};

#endif // JERRY_H
