#ifndef STARWARSPLAYERIMAGE_H
#define STARWARSPLAYERIMAGE_H

#include "../blok-images/iplayerimage.h"

class QGraphicsRectItem;
class QGraphicsScene;

class StarWarsPlayerImage : public IPlayerImage
{
public:
    StarWarsPlayerImage();
    QGraphicsRectItem *createPlayer(QGraphicsScene *scene);
};

#endif // STARWARSPLAYERIMAGE_H
