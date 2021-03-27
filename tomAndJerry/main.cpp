#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include <QTimer>

#define tt(n) for (int i=0; i<n; i++)
#define FOR(i,a,n) for (auto i=a; i!=n; i++)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsView view;
    QGraphicsScene scene;

    view.setFixedSize(800, 800);
    view.setWindowTitle("Tom and Jerry");
    view.setBackgroundBrush(QBrush(Qt::blue));

    int boardData[20][20];

    QFile file("../file");

    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);

    FOR(i,0,20)
            FOR(j,0,20)
                stream >> boardData[i][j];


    QPixmap backGround("Grass.png"), border("Bricks.png");
    border = border.scaledToWidth(40);
    border = border.scaledToHeight(40);
    backGround = backGround.scaledToWidth(40);
    backGround = backGround.scaledToHeight(40);
    QGraphicsPixmapItem boardImg[20][20];

    FOR(i,0,20)
            FOR(j,0,20){
            if(boardData[i][j]==-1)
                boardImg[i][j].setPixmap(border);
            else
                boardImg[i][j].setPixmap(backGround);
            boardImg[i][j].setPos(40+(j*40),40+(i*40));
            scene.addItem(&boardImg[i][j]);
        }

    view.setScene(&scene);
    view.show();
    return a.exec();
}
