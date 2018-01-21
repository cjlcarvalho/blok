#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "starwarsbackgroundimage.h"

StarWarsBackgroundImage::StarWarsBackgroundImage()
{

}

void StarWarsBackgroundImage::createBackground(QGraphicsScene *scene)
{
    scene->addPixmap(QPixmap(":/images/starwarsbackground.png"))->setPos(-500, -300);
}
