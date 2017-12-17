#ifndef IBACKGROUNDIMAGE_H
#define IBACKGROUNDIMAGE_H

#include <QtPlugin>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "blok-images_global.h"

class BLOKIMAGESSHARED_EXPORT IBackgroundImage : public QObject
{
public:
    virtual void createBackground(QGraphicsScene*) = 0;
};

Q_DECLARE_INTERFACE(IBackgroundImage, "org.qt-project.blok-images.IBackgroundImage")

#endif // IBACKGROUNDIMAGE_H
