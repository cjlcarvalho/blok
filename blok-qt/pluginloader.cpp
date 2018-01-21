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
#include <QPluginLoader>

#include "../blok-images/imagefactory.h"
#include "../blok-simulator/isimulator.h"
#include "../blok-audio/iaudio.h"

#include "pluginloader.h"

PluginLoader::PluginLoader() :
    m_imageFactory(nullptr),
    m_simulator(nullptr),
    m_audio(nullptr)
{
    update();
}

void PluginLoader::update()
{
    QObject *imagePlugin = retrievePlugin("images_plugins/");
    if (imagePlugin)
        m_imageFactory = dynamic_cast<ImageFactory *>(imagePlugin);

    QObject *simulatorPlugin = retrievePlugin("simulator_plugins/");
    if (simulatorPlugin)
        m_simulator = dynamic_cast<ISimulator *>(simulatorPlugin);

    QObject *audioPlugin = retrievePlugin("audio_plugins/");
    if (audioPlugin)
        m_audio = dynamic_cast<IAudio *>(audioPlugin);
}

QObject *PluginLoader::retrievePlugin(QString pluginDirPath)
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
    pluginsDir.cd(pluginDirPath);

    for (const QString &file : pluginsDir.entryList(QDir::Files)) {
        if (!QLibrary::isLibrary(pluginsDir.absoluteFilePath(file)))
            continue;

        qDebug() << "Arquivo: " << pluginsDir.absoluteFilePath(file);
        QPluginLoader loader(pluginsDir.absoluteFilePath(file));

        return loader.instance();
    }

    return nullptr;
}

ImageFactory *PluginLoader::imageFactory() const
{
    return m_imageFactory;
}

ISimulator *PluginLoader::simulator() const
{
    return m_simulator;
}

IAudio *PluginLoader::audio() const
{
    return m_audio;
}
