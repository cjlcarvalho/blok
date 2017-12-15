#ifndef IBACKGROUNDIMAGE_H
#define IBACKGROUNDIMAGE_H

#include <QtPlugin>
#include "blok-images_global.h"

class QGraphicsScene;

class BLOKIMAGESSHARED_EXPORT IBackgroundImage
{
public:
    IBackgroundImage();
    virtual void createBackground(QGraphicsScene*) = 0;
};

Q_DECLARE_INTERFACE(IBackgroundImage, "org.qt-project.blok-images.IBackgroundImage/1.0")

#endif // IBACKGROUNDIMAGE_H
