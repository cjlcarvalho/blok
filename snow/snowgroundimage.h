#ifndef SNOWGROUNDIMAGE_H
#define SNOWGROUNDIMAGE_H

#include "../blok-images/igroundimage.h"

class QGraphicsScene;

class SnowGroundImage : public IGroundImage
{
public:
    SnowGroundImage();
    void createGround(QGraphicsScene *scene);
};

#endif // SNOWGROUNDIMAGE_H
