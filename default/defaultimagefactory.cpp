#include "../blok-images/ibackgroundimage.h"
#include "../blok-images/igroundimage.h"
#include "../blok-images/iplayerimage.h"
#include "../blok-images/iblockimage.h"

#include "defaultimagefactory.h"
#include "defaultbackgroundimage.h"
#include "defaultgroundimage.h"
#include "defaultplayerimage.h"
#include "defaultblockimage.h"


DefaultImageFactory::DefaultImageFactory()
{
}

IBackgroundImage *DefaultImageFactory::createBackgroundImage()
{
    return new DefaultBackgroundImage;
}

IGroundImage *DefaultImageFactory::createGroundImage()
{
    return new DefaultGroundImage;
}

IPlayerImage *DefaultImageFactory::createPlayerImage()
{
    return new DefaultPlayerImage;
}

IBlockImage *DefaultImageFactory::createBlockImage()
{
    return new DefaultBlockImage;
}

Q_EXPORT_PLUGIN2(default_, DefaultImageFactory)
