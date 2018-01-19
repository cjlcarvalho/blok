#ifndef STARWARSIMAGEFACTORY_H
#define STARWARSIMAGEFACTORY_H

#include <QObject>
#include <QtPlugin>

#include "starwars_global.h"
#include "../blok-images/imagefactory.h"

class IBackgroundImage;
class IGroundImage;
class IPlayerImage;
class IBlockImage;

class STARWARSSHARED_EXPORT StarWarsImageFactory : public ImageFactory
{
    Q_OBJECT
    Q_INTERFACES(ImageFactory)

public:
    StarWarsImageFactory();
    virtual IBackgroundImage *createBackgroundImage();
    virtual IGroundImage *createGroundImage();
    virtual IPlayerImage *createPlayerImage();
    virtual IBlockImage *createBlockImage();
};

#endif // STARWARSIMAGEFACTORY_H
