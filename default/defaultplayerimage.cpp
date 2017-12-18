#include "defaultplayerimage.h"

DefaultPlayerImage::DefaultPlayerImage()
{

}

QGraphicsRectItem* DefaultPlayerImage::createPlayer(QGraphicsScene *scene){
    QGraphicsRectItem* rect = scene->addRect(-28, -28, 56, 56);
    QPixmap pixmap(QString(":/images/player%1.png").arg(qrand() % 9));
    QBrush brush(pixmap);
    brush.setTransform(brush.transform().translate(-28, -28));
    rect->setBrush(brush);
    return rect;
}
