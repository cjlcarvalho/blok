#ifndef SNOWPLAYERIMAGE_H
#define SNOWPLAYERIMAGE_H

#include "../blok-images/iplayerimage.h"

class QGraphicsRectItem;
class QGraphicsScene;

class SnowPlayerImage : public IPlayerImage
{
public:
    SnowPlayerImage();
    QGraphicsRectItem *createPlayer(QGraphicsScene *scene);
};

#endif // SNOWPLAYERIMAGE_H
