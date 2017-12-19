#include <QGraphicsRectItem>
#include "starwarsgroundimage.h"

StarWarsGroundImage::StarWarsGroundImage()
{

}

void StarWarsGroundImage::createGround(QGraphicsScene *_scene){
    QGraphicsRectItem *ground = _scene->addRect(-450, -10, 900, 20);
    ground->setPos(0, 260);
    QBrush brush(QPixmap(":/images/ground.png"));
    brush.setTransform(brush.transform().translate(-450, -10));
    ground->setBrush(brush);
}
