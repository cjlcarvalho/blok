#ifndef SNOWBACKGROUNDIMAGE_H
#define SNOWBACKGROUNDIMAGE_H

#include "../blok-images/ibackgroundimage.h"

class SnowBackgroundImage : public IBackgroundImage
{
    Q_OBJECT
    Q_INTERFACES(IBackgroundImage)
public:
    SnowBackgroundImage();
    void createBackground(QGraphicsScene*);
};

#endif // SNOWBACKGROUNDIMAGE_H
