#ifndef IPLAYERIMAGE_H
#define IPLAYERIMAGE_H

#include <QtPlugin>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "blok-images_global.h"

class BLOKIMAGESSHARED_EXPORT IPlayerImage : public QObject
{
public:
    IPlayerImage();
    virtual QGraphicsRectItem* createPlayer(QGraphicsScene*) = 0;
};

Q_DECLARE_INTERFACE(IPlayerImage, "org.qt-project.blok-images.IPlayerImage")

#endif // IPLAYERIMAGE_H
