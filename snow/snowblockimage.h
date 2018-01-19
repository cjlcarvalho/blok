#ifndef SNOWBLOCKIMAGE_H
#define SNOWBLOCKIMAGE_H

#include "../blok-images/iblockimage.h"

class QGraphicsRectItem;
class QGraphicsScene;

class SnowBlockImage : public IBlockImage
{
public:
    SnowBlockImage();
    QGraphicsRectItem *createBlock(QGraphicsScene *scene);
};

#endif // SNOWBLOCKIMAGE_H
