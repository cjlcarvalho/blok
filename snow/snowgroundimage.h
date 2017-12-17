#ifndef SNOWGROUNDIMAGE_H
#define SNOWGROUNDIMAGE_H

#include "../blok-images/igroundimage.h"

class SnowGroundImage : public IGroundImage
{
public:
    SnowGroundImage();
    void createGround(QGraphicsScene*);
};

#endif // SNOWGROUNDIMAGE_H
