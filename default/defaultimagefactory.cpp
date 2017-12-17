#include "defaultimagefactory.h"


DefaultImageFactory::DefaultImageFactory()
{
}

IBackgroundImage* DefaultImageFactory::createBackgroundImage(){
    return nullptr;
}

IGroundImage* DefaultImageFactory::createGroundImage(){
    return nullptr;
}

IPlayerImage* DefaultImageFactory::createPlayerImage(){
    return nullptr;
}

IBlockImage* DefaultImageFactory::createBlockImage(){
    return nullptr;
}

Q_EXPORT_PLUGIN2(default_, DefaultImageFactory)
