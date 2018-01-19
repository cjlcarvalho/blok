#ifndef DEFAULTBACKGROUNDIMAGE_H
#define DEFAULTBACKGROUNDIMAGE_H

#include "../blok-images/ibackgroundimage.h"

class QGraphicsScene;

class DefaultBackgroundImage : public IBackgroundImage
{
    Q_OBJECT
    Q_INTERFACES(IBackgroundImage)

public:
    DefaultBackgroundImage();
    void createBackground(QGraphicsScene *scene);
};

#endif // DEFAULTBACKGROUNDIMAGE_H
