#ifndef STARWARSBLOCKIMAGE_H
#define STARWARSBLOCKIMAGE_H

#include "../blok-images/iblockimage.h"

class QGraphicsRectItem;
class QGraphicsScene;

class StarWarsBlockImage : public IBlockImage
{
public:
    StarWarsBlockImage();
    QGraphicsRectItem *createBlock(QGraphicsScene *scene);
};

#endif // STARWARSBLOCKIMAGE_H
