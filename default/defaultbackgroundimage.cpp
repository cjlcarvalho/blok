#include "defaultbackgroundimage.h"

DefaultBackgroundImage::DefaultBackgroundImage()
{

}

void DefaultBackgroundImage::createBackground(QGraphicsScene *scene){
    scene->addPixmap(QPixmap(":/images/background.png"))->setPos(-500, -300);
}
