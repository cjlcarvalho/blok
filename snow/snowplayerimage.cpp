#include <QCoreApplication>
#include <QDir>

#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "snowplayerimage.h"

SnowPlayerImage::SnowPlayerImage()
{

}

QGraphicsRectItem *SnowPlayerImage::createPlayer(QGraphicsScene *scene)
{
    QGraphicsRectItem *rect = scene->addRect(-28, -28, 56, 56);
    QPixmap pixmap(QString(":/images/snowplayer%1.png").arg(qrand() % 9));
    QBrush brush(pixmap);
    brush.setTransform(brush.transform().translate(-28, -28));
    rect->setBrush(brush);
    return rect;
}
