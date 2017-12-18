#ifndef DEFAULTPLAYERIMAGE_H
#define DEFAULTPLAYERIMAGE_H

#include "../blok-images/iplayerimage.h"

class DefaultPlayerImage : public IPlayerImage
{
public:
    DefaultPlayerImage();
    QGraphicsRectItem* createPlayer(QGraphicsScene*);
};

#endif // DEFAULTPLAYERIMAGE_H
