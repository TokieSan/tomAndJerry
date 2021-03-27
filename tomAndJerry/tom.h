#ifndef TOM_H
#define TOM_H
#include <QGraphicsPixmapItem>
#include <QObject>

class Tom: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT;
public:
    Tom(int initialRow, int initialColumn, int d[20][20]);
};

#endif // TOM_H
