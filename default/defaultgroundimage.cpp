#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "defaultgroundimage.h"

DefaultGroundImage::DefaultGroundImage()
{

}

void DefaultGroundImage::createGround(QGraphicsScene *scene)
{
    QGraphicsRectItem *ground = scene->addRect(-450, -10, 900, 20);
    ground->setPos(0, 260);
    QBrush brush(QPixmap(":/images/ground.png"));
    brush.setTransform(brush.transform().translate(-450, -10));
    ground->setBrush(brush);
}
