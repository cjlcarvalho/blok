#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "../blok-images/imagefactory.h"

class PluginLoader
{
private:
    ImageFactory* _imageFactory;
    QObject* _retrieveImagePlugin();
public:
    PluginLoader();
    ImageFactory* getImageFactory();
};

#endif // PLUGINLOADER_H
