#ifndef DEFAULTBLOCKIMAGE_H
#define DEFAULTBLOCKIMAGE_H

#include <QGraphicsRectItem>
#include "../blok-images/iblockimage.h"

class DefaultBlockImage : public IBlockImage
{
public:
    DefaultBlockImage();
    QGraphicsRectItem* createBlock(QGraphicsScene *);
};

#endif // DEFAULTBLOCKIMAGE_H
