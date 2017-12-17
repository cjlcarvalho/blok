#ifndef SNOWBLOCKIMAGE_H
#define SNOWBLOCKIMAGE_H

#include <QGraphicsRectItem>
#include "../blok-images/iblockimage.h"

class SnowBlockImage : public IBlockImage
{
public:
    SnowBlockImage();
    QGraphicsRectItem* createBlock(QGraphicsScene*);
};

#endif // SNOWBLOCKIMAGE_H
