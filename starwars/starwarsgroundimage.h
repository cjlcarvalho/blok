#ifndef STARWARSGROUNDIMAGE_H
#define STARWARSGROUNDIMAGE_H

#include "../blok-images/igroundimage.h"

class StarWarsGroundImage : public IGroundImage
{
public:
    StarWarsGroundImage();
    void createGround(QGraphicsScene*);
};

#endif // STARWARSGROUNDIMAGE_H
