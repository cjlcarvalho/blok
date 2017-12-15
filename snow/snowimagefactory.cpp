#include "snowimagefactory.h"


SnowImageFactory::SnowImageFactory()
{
}

IBackgroundImage* SnowImageFactory::createBackgroundImage(){
    return nullptr;
}

IGroundImage* SnowImageFactory::createGroundImage(){
    return nullptr;
}

IPlayerImage* SnowImageFactory::createPlayerImage(){
    return nullptr;
}

IBlockImage* SnowImageFactory::createBlockImage(){
    return nullptr;
}
