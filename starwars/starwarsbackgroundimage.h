#ifndef STARWARSBACKGROUNDIMAGE_H
#define STARWARSBACKGROUNDIMAGE_H

#include "../blok-images/ibackgroundimage.h"

class QGraphicsScene;

class StarWarsBackgroundImage : public IBackgroundImage
{
    Q_OBJECT
    Q_INTERFACES(IBackgroundImage)

public:
    StarWarsBackgroundImage();
    void createBackground(QGraphicsScene *scene);
};

#endif // STARWARSBACKGROUNDIMAGE_H
