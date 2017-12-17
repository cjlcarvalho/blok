#ifndef DEFAULTBACKGROUNDIMAGE_H
#define DEFAULTBACKGROUNDIMAGE_H

#include "../blok-images/ibackgroundimage.h"

class DefaultBackgroundImage : public IBackgroundImage
{
    Q_OBJECT
    Q_INTERFACES(IBackgroundImage)
public:
    DefaultBackgroundImage();
    void createBackground(QGraphicsScene*);
};

#endif // DEFAULTBACKGROUNDIMAGE_H
