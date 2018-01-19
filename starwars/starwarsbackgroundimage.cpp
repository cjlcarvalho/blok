#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "starwarsbackgroundimage.h"

StarWarsBackgroundImage::StarWarsBackgroundImage()
{

}

void StarWarsBackgroundImage::createBackground(QGraphicsScene *scene)
{
    scene->addPixmap(QPixmap(":/images/background.png"))->setPos(-500, -300);
}
