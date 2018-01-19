#ifndef IBLOCKIMAGE_H
#define IBLOCKIMAGE_H

#include <QtPlugin>

#include "blok-images_global.h"

class QGraphicsRectItem;
class QGraphicsScene;

class BLOKIMAGESSHARED_EXPORT IBlockImage : public QObject
{
public:
    IBlockImage();
    virtual QGraphicsRectItem* createBlock(QGraphicsScene *scene) = 0;
};

Q_DECLARE_INTERFACE(IBlockImage, "org.qt-project.blok-images.IBlockImage")

#endif // IBLOCKIMAGE_H
