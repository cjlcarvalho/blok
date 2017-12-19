#ifndef STARWARSBACKGROUNDIMAGE_H
#define STARWARSBACKGROUNDIMAGE_H

#include "../blok-images/ibackgroundimage.h"

class StarWarsBackgroundImage : public IBackgroundImage
{
    Q_OBJECT
    Q_INTERFACES(IBackgroundImage)
public:
    StarWarsBackgroundImage();
    void createBackground(QGraphicsScene*);
};

#endif // STARWARSBACKGROUNDIMAGE_H
