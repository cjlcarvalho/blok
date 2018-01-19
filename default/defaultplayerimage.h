#ifndef DEFAULTPLAYERIMAGE_H
#define DEFAULTPLAYERIMAGE_H

#include "../blok-images/iplayerimage.h"

class QGraphicsRectItem;
class QGraphicsScene;

class DefaultPlayerImage : public IPlayerImage
{
public:
    DefaultPlayerImage();
    QGraphicsRectItem *createPlayer(QGraphicsScene *scene);
};

#endif // DEFAULTPLAYERIMAGE_H
