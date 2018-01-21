#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "starwarsplayerimage.h"

StarWarsPlayerImage::StarWarsPlayerImage()
{

}

QGraphicsRectItem *StarWarsPlayerImage::createPlayer(QGraphicsScene *scene)
{
    QGraphicsRectItem *rect = scene->addRect(-28, -28, 56, 56);
    QPixmap pixmap(QString(":/images/starwarsplayer%1.png").arg(qrand() % 9));
    QBrush brush(pixmap);
    brush.setTransform(brush.transform().translate(-28, -28));
    rect->setBrush(brush);
    return rect;
}
