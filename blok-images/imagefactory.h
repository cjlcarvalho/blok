#ifndef BLOKIMAGES_H
#define BLOKIMAGES_H

#include <QtPlugin>

#include "blok-images_global.h"

class IBackgroundImage;
class IGroundImage;
class IPlayerImage;
class IBlockImage;

class BLOKIMAGESSHARED_EXPORT ImageFactory : public QObject
{
public:
    virtual IBackgroundImage *createBackgroundImage() = 0;
    virtual IGroundImage *createGroundImage() = 0;
    virtual IPlayerImage *createPlayerImage() = 0;
    virtual IBlockImage *createBlockImage() = 0;
};

Q_DECLARE_INTERFACE(ImageFactory, "org.qt-project.blok-images.ImageFactory")

#endif // BLOKIMAGES_H
