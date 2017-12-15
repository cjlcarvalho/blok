#include <QDir>
#include <QPluginLoader>
#include "pluginloader.h"

PluginLoader::PluginLoader()
{
    QObject* imagePlugin = _retrievePlugin(QCoreApplication::aplicationDirPath() + "/plugins/", "imagefactory.h");
    if(imagePlugin)
        _imageFactory = dynamic_cast<ImageFactory*>(imagePlugin);
}

QObject* PluginLoader::_retrievePlugin(const QString &path, const QString &interfaceName){
    QDir pluginPath(path);
    if(!pluginPath.exists() || path.isEmpty())
        return nullptr;
    QFileInfoList itemList = pluginPath.entryInfoList(QDir::AllDirs | QDir::NotDotAndDotDot, QDir::DirsFirst);
    foreach (const QFileInfo& folder, itemList) {
        QString fileName = folder.fileName() + interfaceName;
        QPluginLoader loader(folder.filePath() + "/" + fileName);
        QObject* instance = loader.instance();
        if(instance)
            return instance;
    }
    return nullptr;
}

ImageFactory* PluginLoader::getImageFactory(){
    return _imageFactory;
}
