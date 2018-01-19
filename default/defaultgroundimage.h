#ifndef DEFAULTGROUNDIMAGE_H
#define DEFAULTGROUNDIMAGE_H

#include "../blok-images/igroundimage.h"

class QGraphicsScene;

class DefaultGroundImage : public IGroundImage
{
public:
    DefaultGroundImage();
    void createGround(QGraphicsScene *scene);
};

#endif // DEFAULTGROUNDIMAGE_H
