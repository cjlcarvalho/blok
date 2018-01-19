#ifndef IPLAYERIMAGE_H
#define IPLAYERIMAGE_H

#include <QtPlugin>

#include "blok-images_global.h"

class QGraphicsRectItem;
class QGraphicsScene;

class BLOKIMAGESSHARED_EXPORT IPlayerImage : public QObject
{
public:
    IPlayerImage();
    virtual QGraphicsRectItem *createPlayer(QGraphicsScene *scene) = 0;
};

Q_DECLARE_INTERFACE(IPlayerImage, "org.qt-project.blok-images.IPlayerImage")

#endif // IPLAYERIMAGE_H
