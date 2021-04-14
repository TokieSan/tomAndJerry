#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <QTextStream>
#include "tom.h"
#include "jerry.h"
#include "cheese.h"
#include "pellet.h"
#include <QTimer>
#include "../mazeGenerator.cpp"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    QGraphicsView view;
    QGraphicsScene scene;

    view.setWindowTitle("Tom and Jerry");
    view.setMinimumSize(800,800);
    view.setBackgroundBrush(QBrush(Qt::black));

    int boardData[15][15];
    QFile file("board.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString temp;


    for(int i = 0; i<15; i++)
        for(int j = 0; j<15; j++)
        {
            stream >> temp;
            boardData[i][j] = temp.toInt();
        }


    QGraphicsPixmapItem boardImages[15][15];
    QPixmap q1("Bricks.png");
    q1 = q1.scaledToWidth(50);
    q1 = q1.scaledToHeight(50);
    QPixmap q2("Grass.png");
    q2 = q2.scaledToWidth(50);
    q2 = q2.scaledToHeight(50);
    for(int i = 0; i<15; i++)
        for(int j = 0; j<15; j++)
        {
            if (boardData[i][j] == -1)
                boardImages[i][j].setPixmap(q1);
            else
                boardImages[i][j].setPixmap(q2);

            boardImages[i][j].setPos(25+50*j, 25+50*i);


            scene.addItem(&boardImages[i][j]);
        }

    Tom t(13,7,boardData);
    scene.addItem(&t);

    jerry j(7,7,boardData);
    scene.addItem(&j);
    j.setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    j.setFocus();

    cheese c1(1,1);
     scene.addItem(&c1);
    cheese c2(13,1);
     scene.addItem(&c2);
    cheese c3(1,13);
     scene.addItem(&c3);
     cheese c4(13,13);
      scene.addItem(&c4);
     pellet p1(11,11);
     scene.addItem(&p1);
     pellet p2(3,1);
     scene.addItem(&p2);

     QTimer timer;
     timer.start(70);
     timer.connect(&timer,SIGNAL(timeout()),&t, SLOT(move()));

    view.setScene(&scene);
    view.show();
    return a.exec();
}
