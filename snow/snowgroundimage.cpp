#include <QCoreApplication>

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QBrush>

#include "snowgroundimage.h"

SnowGroundImage::SnowGroundImage()
{

}

void SnowGroundImage::createGround(QGraphicsScene *scene)
{
    QGraphicsRectItem *ground = scene->addRect(-450, -10, 900, 20);
    ground->setPos(0, 260);
    QBrush brush(QPixmap(":/images/snowground.png"));
    brush.setTransform(brush.transform().translate(-450, -10));
    ground->setBrush(brush);
}
