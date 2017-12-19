#ifndef STARWARSBLOCKIMAGE_H
#define STARWARSBLOCKIMAGE_H

#include <QGraphicsRectItem>
#include "../blok-images/iblockimage.h"

class StarWarsBlockImage : public IBlockImage
{
public:
    StarWarsBlockImage();
    QGraphicsRectItem* createBlock(QGraphicsScene*);
};

#endif // STARWARSBLOCKIMAGE_H
