#ifndef STARWARSPLAYERIMAGE_H
#define STARWARSPLAYERIMAGE_H

#include "../blok-images/iplayerimage.h"

class StarWarsPlayerImage : public IPlayerImage
{
public:
    StarWarsPlayerImage();
    QGraphicsRectItem* createPlayer(QGraphicsScene*);
};

#endif // STARWARSPLAYERIMAGE_H
