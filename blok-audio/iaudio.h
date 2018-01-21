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

#ifndef IAUDIO_H
#define IAUDIO_H

#include "blok-audio_global.h"

#include <QObject>

class BLOKAUDIOSHARED_EXPORT IAudio : public QObject
{
    Q_OBJECT

public:
    virtual ~IAudio() = 0;
    virtual void startBackgroundAudio(const QString &audioPath) = 0;
    virtual void playClickAudio(const QString &audioPath) = 0;
    virtual void playYouWonAudio(const QString &audioPath) = 0;
    virtual void playYouLostAudio(const QString &audioPath) = 0;

protected Q_SLOTS:
    virtual void enqueueBackgroundAudioSlot() = 0;

protected:
    virtual void play(const QString &audioPath) = 0;
};

Q_DECLARE_INTERFACE(IAudio, "org.qt-project.blok-audio.IAudio")

#endif // IAUDIO_H
