#include "jerry.h"
#include "tom.h"
#include "jerpos.h"
#include <QMessageBox>
#include <QTimer>
#include <QThread>
#include <QEventLoop>
#include <QApplication>
#include <QProcess>
#include "jerpos.h"

int jerry::row4 = 7;
int jerry::column4 = 7;
int jerry::data4[15][15] = {{0}};

jerry::jerry(int initialRow, int initialColumn, int d[15][15], QGraphicsScene &scene)
{
    for(int i = 0; i<15; i++)
        for(int j = 0; j<15; j++)
        {
            data4[i][j] = d[i][j];
        }

    row4 = initialRow;
    column4 = initialColumn;

    QPixmap jer("Jerry3.png");
    jer = jer.scaledToWidth(50);
    jer = jer.scaledToHeight(50);
    setPixmap(jer);
    setPos(25+50*jerry::column4, 25+50*jerry::row4);
    score=0;
    lives=3;
    hasCheese=false;
    invincible=false;
    std::string scoreText="Cheese: ";
    scoreText.append( std::to_string(this->getScore()));
    x.setPlainText(QString::fromUtf8(scoreText.c_str()));
    x.setDefaultTextColor(QColor("#24d1ac"));
    x.setX(850);
    x.setScale(2);
    scene.addItem(&x);
    scene.addItem(&cheeseR);
    scoreText="Lives: ";
    scoreText.append( std::to_string(lives));
    y.setPlainText(QString::fromUtf8(scoreText.c_str()));
    y.setDefaultTextColor(QColor("#24d1ac"));
    y.setX(850);
    y.setY(100);
    y.setScale(2);
    scene.addItem(&y);

}
bool jerry::checkIfWon(){
    return score==4;
}
void jerry::doTheThing(jerry *jer){
    std::string scoreText="Cheese: ";
    scoreText.append( std::to_string(jer->getScore()));
    x.setPlainText(QString::fromUtf8(scoreText.c_str()));
    x.setDefaultTextColor(QColor("#24d1ac"));
    x.setX(850);
    x.setScale(2);
    scene()->addItem(&x);
}
void jerry::setRow4(int newRow4)
{
    row4 = newRow4;
}
void jerry::updateLives(){
    std::string scoreText="Lives: ";
    scoreText.append( std::to_string(lives));
    y.setPlainText(QString::fromUtf8(scoreText.c_str()));
    y.setDefaultTextColor(QColor("#24d1ac"));
    y.setX(850);
    y.setY(100);
    y.setScale(2);
    scene()->addItem(&y);
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
void jerry::endGame(){
    if(lives<=0){
        //popup window with "You Lost"
        QMediaPlayer *music = new QMediaPlayer();
        music->setMedia(QUrl("file:/home/elt0khy/tomAndJerry/lose.wav"));
        music->setVolume(15);
        music->play();
        QMessageBox msg;
        msg.setText("You have lost!");
        QTimer cntDown;
        int cnt=3;
        std::string scoreText="YOU LOST";
        y.setPlainText(QString::fromUtf8(scoreText.c_str()));
        y.setDefaultTextColor(QColor("#ff0000"));
        y.setX(0);
        y.setY(200);
        y.setScale(10);
        scene()->addItem(&y);
           QObject::connect(&cntDown, &QTimer::timeout, [this,&msg,&cnt, &cntDown]()->void{
                                if(--cnt < 0){
                                    cntDown.stop();
                                    msg.close();
                                    lives=3;
                                    this->updateLives();
                                }
                            });
           cntDown.start(1000);
           msg.exec();
           qApp->quit();
           QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
           //TODO: ADD STH TO RESET THE WHOLE CHEESE & GAME
    }
}
void jerry::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Up && data4[row4-1][column4] != -1){
        row4--;
        jerpos=data4[row4][column4];
    }
    else if(event->key() == Qt::Key_Down && data4[row4+1][column4] != -1){
        row4++;
        jerpos=data4[row4][column4];

    }
    else if(event->key() == Qt::Key_Right && data4[row4][column4+1] != -1){
        column4++;
        jerpos=data4[row4][column4];

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
        jerpos=data4[row4][column4];

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
        QMediaPlayer *music = new QMediaPlayer();
        music->setMedia(QUrl("file:/home/elt0khy/tomAndJerry/eat.wav"));
        music->setVolume(15);
        music->play();

        hasCheese=false;
        score++;
        QPixmap jer("Jerry3.png");
        jer = jer.scaledToWidth(50);
        jer = jer.scaledToHeight(50);
        setPixmap(jer);
        setPos(25+50*column4, 25+50*row4);
        QPixmap ch("Cheese2.png");
        ch = ch.scaledToHeight(50);
        ch = ch.scaledToWidth(50);
        cheeseR.setPixmap(ch);
        cheeseR.setPos(25+50*7, 25+50*7);
        scene()->addItem(&cheeseR);
        doTheThing(this);
        if(score==4){
            QMediaPlayer *music = new QMediaPlayer();
            music->setMedia(QUrl("file:/home/elt0khy/tomAndJerry/win.wav"));
            music->setVolume(15);
            music->play();
            std::string scoreText="YOU WON";
            y.setPlainText(QString::fromUtf8(scoreText.c_str()));
            y.setDefaultTextColor(QColor("#11FF11"));
            y.setX(0);
            y.setY(200);
            y.setScale(10);
            scene()->addItem(&y);
            QMessageBox msg;
            msg.setText("You have won!");
            QTimer cntDown;
            int cnt=8;
               QObject::connect(&cntDown, &QTimer::timeout, [this,&msg,&cnt, &cntDown]()->void{
                                    if(--cnt < 0){
                                        cntDown.stop();
                                        msg.close();
                                    }
                                });
               cntDown.start(1000);
               msg.exec();
               qApp->quit();
               QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
               //TODO: ADD STH TO RESET THE WHOLE CHEESE & GAME
        }

    }
    for(int i = 0; i<items.size(); i++)
    {
        if(typeid(*items[i]) == typeid(cheese) && !hasCheese)
        {
            QMediaPlayer *music = new QMediaPlayer();
            music->setMedia(QUrl("file:/home/elt0khy/tomAndJerry/eat.wav"));
            music->setVolume(15);
            music->play();
            scene()->removeItem(items[i]);
            QPixmap jerr("JerryCheese.png");
            jerr = jerr.scaledToWidth(50);
            jerr = jerr.scaledToHeight(50);
            setPixmap(jerr);
            setPos(25+50*column4, 25+50*row4);

            hasCheese=true;


        }
        else if(typeid(*items[i]) == typeid(pellet))
        {
            QMediaPlayer *music = new QMediaPlayer();
            music->setMedia(QUrl("file:/home/elt0khy/tomAndJerry/pellet.wav"));
            music->setVolume(15);
            music->play();
            scene()->removeItem(items[i]);
            //invincible
            //maybe add sth in the future to make jerry bigger when invincible
            invincible=true;
            QEventLoop loop;
            QTimer::singleShot(5000, &loop, &QEventLoop::quit);
            loop.exec();
            invincible=false;
        }

        else if(typeid(*items[i]) == typeid(Tom)){
            if(!invincible) lives--;
            updateLives();
            endGame();


        }
    }
    jerpos=data4[row4][column4];

}
int jerry::getVertex()
{
    return data4[row4][column4];
}
