#include <QCoreApplication>
#include "snowblockimage.h"

SnowBlockImage::SnowBlockImage()
{

}

QGraphicsRectItem* SnowBlockImage::createBlock(QGraphicsScene *scene){
    QGraphicsRectItem* rect = scene->addRect(-14, -14, 28, 28);
    QBrush brush(QPixmap(":/images/brick.png"));
    brush.setTransform(brush.transform().translate(-14, -14));
    rect->setBrush(brush);
    return rect;
}
