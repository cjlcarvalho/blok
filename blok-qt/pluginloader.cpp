/********************************************************************************
 *   Copyright (C) 2018 by Caio Carvalho <caiojcarvalho@gmail.com>              *
 *                                                                              *
 *   This program is free software; you can redistribute it and/or modify       *
 *   it under the terms of the GNU General Public License as published by       *
 *   the Free Software Foundation; either version 2 of the License, or          *
 *   (at your option) any later version.                                        *
 *                                                                              *
 *   This program is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 *   GNU General Public License for more details.                               *
 *                                                                              *
 *   You should have received a copy of the GNU General Public License          *
 *   along with this program; if not, write to the                              *
 *   Free Software Foundation, Inc.,                                            *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .             *
 *******************************************************************************/

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileSystemWatcher>
#include <QPluginLoader>

#include "../blok-images/imagefactory.h"
#include "../blok-simulator/isimulator.h"
#include "../blok-audio/iaudio.h"

#include "pluginloader.h"

PluginLoader::PluginLoader()
{
    update();

    QFileSystemWatcher *watcher = new QFileSystemWatcher;

    watcher->addPaths({ retrievePluginDir("images_plugins/").absolutePath(),
                        retrievePluginDir("simulator_plugins/").absolutePath(),
                        retrievePluginDir("audio_plugins/").absolutePath() });

    connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(updatePlugins(QString)));
}

void PluginLoader::update()
{
    QList<QObject *> imagesPlugins = retrievePlugin("images_plugins/");

    m_imageFactories.clear();

    for (QObject *item : imagesPlugins)
        m_imageFactories.append(dynamic_cast<ImageFactory *>(item));

    QList<QObject *> simulatorPlugins = retrievePlugin("simulator_plugins/");

    m_simulators.clear();

    for (QObject *item : simulatorPlugins)
        m_simulators.append(dynamic_cast<ISimulator *>(item));

    QList<QObject *> audioPlugins = retrievePlugin("audio_plugins/");

    m_audios.clear();

    for (QObject *item : audioPlugins)
        m_audios.append(dynamic_cast<IAudio *>(item));
}

void PluginLoader::updatePlugins(const QString &pluginDirPath)
{
    QList<QObject *> plugins = retrievePlugin(pluginDirPath);

    if (pluginDirPath == retrievePluginDir("images_plugins/").absolutePath())
    {
        m_imageFactories.clear();

        for (QObject *item : plugins)
            m_imageFactories.append(qobject_cast<ImageFactory *>(item));

        emit updateImageFactories(m_imageFactories);
    }
    else if (pluginDirPath == retrievePluginDir("simulator_plugins/").absolutePath())
    {
        m_simulators.clear();

        for (QObject *item : plugins)
            m_simulators.append(dynamic_cast<ISimulator *>(item));

        emit updateSimulators(m_simulators);
    }
    else if (pluginDirPath == retrievePluginDir("audio_plugins/").absolutePath())
    {
        m_audios.clear();

        for (QObject *item : plugins)
            m_audios.append(dynamic_cast<IAudio *>(item));

        emit updateAudios(m_audios);
    }
}

QDir PluginLoader::retrievePluginDir(const QString &pluginFile)
{
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
    pluginsDir.cd(pluginFile);

    return pluginsDir;
}

QList<QObject *> PluginLoader::retrievePlugin(const QString &pluginDirPath)
{
    QDir pluginsDir = retrievePluginDir(pluginDirPath);

    QList<QObject *> resultList;

    for (const QString &file : pluginsDir.entryList(QDir::Files)) {
        if (!QLibrary::isLibrary(pluginsDir.absoluteFilePath(file)))
            continue;

        qDebug() << "Arquivo: " << pluginsDir.absoluteFilePath(file);
        QPluginLoader loader(pluginsDir.absoluteFilePath(file));

        resultList.append(loader.instance());
    }

    return resultList;
}

QList<ImageFactory *> PluginLoader::imageFactories() const
{
    return m_imageFactories;
}

QList<ISimulator *> PluginLoader::simulators() const
{
    return m_simulators;
}

QList<IAudio *> PluginLoader::audios() const
{
    return m_audios;
}
