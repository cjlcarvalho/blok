#ifndef IBLOCKIMAGE_H
#define IBLOCKIMAGE_H

#include <QtPlugin>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "blok-images_global.h"

class QGraphicsRectItem;
class QGraphicsScene;

class BLOKIMAGESSHARED_EXPORT IBlockImage : public QObject
{
public:
    IBlockImage();
    virtual QGraphicsRectItem* createBlock(QGraphicsScene*) = 0;
};

Q_DECLARE_INTERFACE(IBlockImage, "org.qt-project.blok-images.IBlockImage")

#endif // IBLOCKIMAGE_H
