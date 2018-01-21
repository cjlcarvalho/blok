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

#ifndef PHONONAUDIO_H
#define PHONONAUDIO_H

#include <QtPlugin>

#include "phononaudio_global.h"

#include "../blok-audio/iaudio.h"

namespace Phonon {
class MediaObject;
}

class PHONONAUDIOSHARED_EXPORT PhononAudio : public IAudio
{
    Q_OBJECT
    Q_INTERFACES(IAudio)
public:
    PhononAudio();
    ~PhononAudio() override;
    void startBackgroundAudio(const QString &audioPath) override;
    void playClickAudio(const QString &audioPath) override;
    void playYouWonAudio(const QString &audioPath) override;
    void playYouLostAudio(const QString &audioPath) override;
    IAudio *clone() override;

protected Q_SLOTS:
    void enqueueBackgroundAudioSlot() override;

private:
    void play(const QString &audioPath) override;

private:
    Phonon::MediaObject *m_backgroundAudio;
    QString m_backgroundAudioPath;
};

#endif // PHONONAUDIO_H
