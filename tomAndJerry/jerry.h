#ifndef JERRY_H
#define JERRY_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QList>
#include "cheese.h"
#include <QGraphicsScene>
#include "pellet.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaContent>
class jerry: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT;
private:
    int lives;
    bool hasCheese, invincible;
    QGraphicsTextItem x;
    QGraphicsTextItem y;
    QGraphicsPixmapItem cheeseR;

public:
    static int row4;
    static int column4;
    static int data4[15][15];

    int score;
    void endGame();
    jerry(int initialRow, int initialColumn, int d[15][15], QGraphicsScene &scene);
    bool checkIfWon();
    void setRow4(int newRow4);
    int getRow4();
    static int getVertex();
    void setColumn4(int newColumn4);
    int getColumn4();
    int getScore(){return score;}
    void doIt(){invincible =false;}
    void doTheThing(jerry *jer);
    void setItToFls(){invincible=false;}
    void updateLives();
    void updateScore();

private slots:
    void keyPressEvent(QKeyEvent * event);

};

#endif // JERRY_H
