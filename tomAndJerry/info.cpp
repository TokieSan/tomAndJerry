#include "info.h"
#include "jerry.h"

info::info()
{
    std::string scoreText="Cheese: ";
    scoreText.append( std::to_string(0));
    setPlainText(QString::fromUtf8(scoreText.c_str()));
    setDefaultTextColor(QColor("#24d1ac"));
    setX(1000);
    setScale(2);
}
void info::doTheThing(jerry *jer){
    std::string scoreText="Cheesse: ";
    scoreText.append( std::to_string(jer->getScore()));
    setPlainText(QString::fromUtf8(scoreText.c_str()));
    setDefaultTextColor(QColor("#24d1ac"));
    setX(1000);
    setScale(2);
    QGraphicsTextItem x;
    x.setPlainText(QString::fromUtf8(scoreText.c_str()));
    x.setDefaultTextColor(QColor("#24d1ac"));
    x.setX(1000);
    x.setScale(2);
    scene()->addItem(&x);
}
