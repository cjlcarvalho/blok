#ifndef SNOWPLAYERIMAGE_H
#define SNOWPLAYERIMAGE_H

#include "../blok-images/iplayerimage.h"

class SnowPlayerImage : public IPlayerImage
{
public:
    SnowPlayerImage();
    QGraphicsRectItem* createPlayer(QGraphicsScene*);
};

#endif // SNOWPLAYERIMAGE_H
