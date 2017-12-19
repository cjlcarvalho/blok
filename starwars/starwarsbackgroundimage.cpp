#include "starwarsbackgroundimage.h"

StarWarsBackgroundImage::StarWarsBackgroundImage()
{

}

void StarWarsBackgroundImage::createBackground(QGraphicsScene *_scene){
    _scene->addPixmap(QPixmap(":/images/background.png"))->setPos(-500, -300);
}
