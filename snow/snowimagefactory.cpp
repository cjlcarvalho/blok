#include "snowimagefactory.h"
#include "snowbackgroundimage.h"
#include "snowgroundimage.h"
#include "snowplayerimage.h"
#include "snowblockimage.h"

SnowImageFactory::SnowImageFactory()
{
}

IBackgroundImage* SnowImageFactory::createBackgroundImage(){
    return new SnowBackgroundImage;
}

IGroundImage* SnowImageFactory::createGroundImage(){
    return new SnowGroundImage;
}

IPlayerImage* SnowImageFactory::createPlayerImage(){
    return new SnowPlayerImage;
}

IBlockImage* SnowImageFactory::createBlockImage(){
    return new SnowBlockImage;
}

Q_EXPORT_PLUGIN2(snow, SnowImageFactory)
