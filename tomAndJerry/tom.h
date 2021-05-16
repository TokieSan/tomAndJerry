#ifndef TOM_H
#define TOM_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <bits/stdc++.h>
#include "jerpos.h"

class Tom: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT;
private:
    int row1, column1;
    int data1[15][15];
    std::vector<std::vector<int>> adj;
    int lastRand;
    std::vector<int> road;
    std::vector<int> dist;
    char lastMove;
public:
    Tom(int initialRow, int initialColumn, int d[15][15]);
    void setRow1(int newRow1);
    int getRow1();
    void setColumn1(int newColumn1);
    int getColumn1();
public slots:
    void keyPressEvent(QKeyEvent * event);
    void move(char d);
    void randomlyMove();
    void dij(int s);
    void toJerry();
    std::pair<int,int> getPos(int x);
};

#endif // TOM_H
