#include "../blok-images/ibackgroundimage.h"
#include "../blok-images/igroundimage.h"
#include "../blok-images/iplayerimage.h"
#include "../blok-images/iblockimage.h"

#include "starwarsimagefactory.h"
#include "starwarsbackgroundimage.h"
#include "starwarsgroundimage.h"
#include "starwarsplayerimage.h"
#include "starwarsblockimage.h"

StarWarsImageFactory::StarWarsImageFactory()
{
}

IBackgroundImage *StarWarsImageFactory::createBackgroundImage()
{
    return new StarWarsBackgroundImage;
}

IGroundImage *StarWarsImageFactory::createGroundImage()
{
    return new StarWarsGroundImage;
}

IPlayerImage *StarWarsImageFactory::createPlayerImage()
{
    return new StarWarsPlayerImage;
}

IBlockImage *StarWarsImageFactory::createBlockImage()
{
    return new StarWarsBlockImage;
}

Q_EXPORT_PLUGIN2(starwars, StarWarsImageFactory)
