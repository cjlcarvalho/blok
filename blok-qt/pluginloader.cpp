#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include "pluginloader.h"

PluginLoader::PluginLoader()
{
    QObject* imagePlugin = _retrieveImagePlugin();
    if(imagePlugin)
        _imageFactory = qobject_cast<ImageFactory*>(imagePlugin);
}

QObject* PluginLoader::_retrieveImagePlugin(){
    QDir pluginsDir = QDir(QCoreApplication::applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cdUp();
    pluginsDir.cd("image_plugins/");
    foreach(QString file, pluginsDir.entryList(QDir::Files)){
        qDebug() << "Arquivo: " << pluginsDir.absoluteFilePath(file);
        QPluginLoader loader(pluginsDir.absoluteFilePath(file));
        return loader.instance();
    }
    return nullptr;
}

ImageFactory* PluginLoader::getImageFactory(){
    return _imageFactory;
}
