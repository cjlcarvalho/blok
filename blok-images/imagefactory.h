#ifndef BLOKIMAGES_H
#define BLOKIMAGES_H

#include <QtPlugin>
#include "blok-images_global.h"
#include "ibackgroundimage.h"
#include "igroundimage.h"
#include "iplayerimage.h"
#include "iblockimage.h"

class BLOKIMAGESSHARED_EXPORT ImageFactory
{
public:
    ImageFactory();
    virtual IBackgroundImage* createBackgroundImage() = 0;
    virtual IGroundImage* createGroundImage() = 0;
    virtual IPlayerImage* createPlayerImage() = 0;
    virtual IBlockImage* createBlockImage() = 0;
};

Q_DECLARE_INTERFACE(ImageFactory, "org.qt-project.blok-images.ImageFactory/1.0")

#endif // BLOKIMAGES_H
