#include <QCoreApplication>
#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "snowbackgroundimage.h"

SnowBackgroundImage::SnowBackgroundImage()
{

}

void SnowBackgroundImage::createBackground(QGraphicsScene *scene)
{
    scene->addPixmap(QPixmap(":/images/snowbackground.png"))->setPos(-500, -300);
}
