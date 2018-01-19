#ifndef IGROUNDIMAGE_H
#define IGROUNDIMAGE_H

#include <QtPlugin>

#include "blok-images_global.h"

class QGraphicsScene;

class BLOKIMAGESSHARED_EXPORT IGroundImage : public QObject
{
public:
    IGroundImage();
    virtual void createGround(QGraphicsScene *scene) = 0;
};

Q_DECLARE_INTERFACE(IGroundImage, "org.qt-project.blok-images.IGroundImage")

#endif // IGROUNDIMAGE_H
