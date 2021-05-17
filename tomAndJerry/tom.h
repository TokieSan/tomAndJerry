#ifndef TOM_H
#define TOM_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QVector>
#include <queue>
#include "jerpos.h"
#include "jerry.h"
#include <QTimer>
#include <QKeyEvent>

class Tom: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT;
private:
    int row1, column1;
    int data1[15][15];
    int lastRand;

public:
    Tom(int initialRow, int initialColumn, int d[15][15]);
    QTimer* timer;
    void setRow1(int newRow1);
    int getRow1();
    void setColumn1(int newColumn1);
    int getColumn1();
    int rowJerry;
    int columnJerry;
    int adjacencyMatrix[107][107] = {{0}};
    int matrix_row;
    int matrix_colum;
    QVector<int> dijkestra(int adjacencyMatrix[107][107], int startVertex);
    int startVertex;
    int endVertex;
    QVector<int> path;
    const int COUNT = 107;
    const int INFINITE =  1000;
public slots:
    void move();
};

#endif // TOM_H
