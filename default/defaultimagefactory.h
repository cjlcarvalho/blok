#ifndef DEFAULTIMAGEFACTORY_H
#define DEFAULTIMAGEFACTORY_H

#include <QObject>
#include <QtPlugin>
#include "default_global.h"
#include "../blok-images/imagefactory.h"

class DEFAULTSHARED_EXPORT DefaultImageFactory : public ImageFactory
{
    Q_OBJECT
    Q_INTERFACES(ImageFactory)
public:
    DefaultImageFactory();
    virtual IBackgroundImage* createBackgroundImage();
    virtual IGroundImage* createGroundImage();
    virtual IPlayerImage* createPlayerImage();
    virtual IBlockImage* createBlockImage();
};

#endif // DEFAULTIMAGEFACTORY_H
