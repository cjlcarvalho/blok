#ifndef STARWARSGROUNDIMAGE_H
#define STARWARSGROUNDIMAGE_H

#include "../blok-images/igroundimage.h"

class QGraphicsScene;

class StarWarsGroundImage : public IGroundImage
{
public:
    StarWarsGroundImage();
    void createGround(QGraphicsScene *scene);
};

#endif // STARWARSGROUNDIMAGE_H
