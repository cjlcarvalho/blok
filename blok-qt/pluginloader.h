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

#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QDir>
#include <QList>
#include <QObject>

class ImageFactory;
class ISimulator;
class IAudio;

class PluginLoader : public QObject
{
    Q_OBJECT

public:
    PluginLoader();
    void update();
    QList<ImageFactory *> imageFactories() const;
    QList<ISimulator *> simulators() const;
    QList<IAudio *> audios() const;

Q_SIGNALS:
    void updateImageFactories(const QList<ImageFactory *> &imageFactories);
    void updateSimulators(const QList<ISimulator *> &simulators);
    void updateAudios(const QList<IAudio *> &audios);

public Q_SLOTS:
    void updatePlugins(const QString &pluginDirPath);

protected:
    QList<QObject *> retrievePlugin(const QString &pluginDirPath);
    QDir retrievePluginDir(const QString &pluginFile);

private:
    QList<ImageFactory *> m_imageFactories;
    QList<ISimulator *> m_simulators;
    QList<IAudio *> m_audios;
};

#endif // PLUGINLOADER_H
