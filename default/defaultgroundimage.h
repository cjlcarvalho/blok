#ifndef DEFAULTGROUNDIMAGE_H
#define DEFAULTGROUNDIMAGE_H

#include "../blok-images/igroundimage.h"

class DefaultGroundImage : public IGroundImage
{
public:
    DefaultGroundImage();
    void createGround(QGraphicsScene*);
};

#endif // DEFAULTGROUNDIMAGE_H
