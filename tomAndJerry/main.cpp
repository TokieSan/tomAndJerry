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
#include <QApplication>
#include <QSignalMapper>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaContent>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    QGraphicsScene scene;
    QGraphicsView view;
    a .setFont (QFont ("Hack", 9));
    view.setWindowTitle("Tom and Jerry");
    view.setFixedSize(1200,800);
    view.setBackgroundBrush(QBrush(QColor("#111111")));

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
    QPixmap border("color.png");
    border = border.scaledToWidth(50);
    border = border.scaledToHeight(50);
    QPixmap road("black.png");
    road = road.scaledToWidth(50);
    road = road.scaledToHeight(50);
    for(int i = 0; i<15; i++)
        for(int j = 0; j<15; j++)
        {
            if (boardData[i][j] == -1)
                boardImages[i][j].setPixmap(border);
            else
                boardImages[i][j].setPixmap(road);

            boardImages[i][j].setPos(25+50*j, 25+50*i);


            scene.addItem(&boardImages[i][j]);
        }

    Tom t(13,7,boardData);
    scene.addItem(&t);

    jerry j(7,7,boardData,  scene);
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
     scene.addItem(&p2);;

     QTimer tomTimer;
     tomTimer.start(350);
     tomTimer.connect(&tomTimer, SIGNAL(timeout()),&t, SLOT(move()));

     QMediaPlayer *music = new QMediaPlayer();
     music->setMedia(QUrl("file:/home/elt0khy/tomAndJerry/backgroundmusic.mp3"));
     music->setVolume(15);
     music->play();
     music->connect(music,&QMediaPlayer::mediaStatusChanged,music,&QMediaPlayer::play);
     music->play();


    view.setScene(&scene);
    view.show();
    return a.exec();
}
