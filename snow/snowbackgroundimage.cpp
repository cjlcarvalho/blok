#include <QCoreApplication>
#include <QDebug>
#include "snowbackgroundimage.h"

SnowBackgroundImage::SnowBackgroundImage()
{

}

void SnowBackgroundImage::createBackground(QGraphicsScene *_scene){
    _scene->addPixmap(QPixmap(":/images/background.png"))->setPos(-500, -300);
}
