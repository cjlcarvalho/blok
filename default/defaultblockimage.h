#ifndef DEFAULTBLOCKIMAGE_H
#define DEFAULTBLOCKIMAGE_H

#include "../blok-images/iblockimage.h"

class QGraphicsRectItem;
class QGraphicsScene;

class DefaultBlockImage : public IBlockImage
{
public:
    DefaultBlockImage();
    QGraphicsRectItem *createBlock(QGraphicsScene *scene);
};

#endif // DEFAULTBLOCKIMAGE_H
