#ifndef SNOWIMAGEFACTORY_H
#define SNOWIMAGEFACTORY_H

#include <QObject>
#include <QtPlugin>

#include "snow_global.h"

#include "../blok-images/imagefactory.h"

class IBackgroundImage;
class IGroundImage;
class IPlayerImage;
class IBlockImage;

class SNOWSHARED_EXPORT SnowImageFactory : public ImageFactory
{
    Q_OBJECT
    Q_INTERFACES(ImageFactory)

public:
    SnowImageFactory();
    virtual IBackgroundImage *createBackgroundImage();
    virtual IGroundImage *createGroundImage();
    virtual IPlayerImage *createPlayerImage();
    virtual IBlockImage *createBlockImage();
};

#endif // SNOWIMAGEFACTORY_H
