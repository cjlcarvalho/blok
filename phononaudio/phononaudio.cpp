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

#include <phonon/MediaObject>

#include "phononaudio.h"

PhononAudio::PhononAudio() :
    m_backgroundAudio(nullptr),
    m_backgroundAudioPath(QString())
{

}

PhononAudio::~PhononAudio()
{
    m_backgroundAudio->stop();
    delete m_backgroundAudio;
}

void PhononAudio::startBackgroundAudio(const QString &audioPath)
{
    m_backgroundAudioPath = audioPath;

    m_backgroundAudio = Phonon::createPlayer(Phonon::NoCategory,
                                             Phonon::MediaSource(QUrl(audioPath)));

    connect(m_backgroundAudio, SIGNAL(aboutToFinish()),
                               SLOT(enqueueBackgroundAudioSlot()));

    m_backgroundAudio->play();
}

void PhononAudio::play(const QString &audioPath)
{
    Phonon::MediaObject *audio = Phonon::createPlayer(Phonon::NoCategory,
                                                      Phonon::MediaSource(QUrl(audioPath)));

    connect(audio, SIGNAL(finished()), audio, SLOT(deleteLater()));

    audio->play();
}

void PhononAudio::playClickAudio(const QString &audioPath)
{
    play(audioPath);
}

void PhononAudio::playYouWonAudio(const QString &audioPath)
{
    play(audioPath);
}

void PhononAudio::playYouLostAudio(const QString &audioPath)
{
    play(audioPath);
}

void PhononAudio::enqueueBackgroundAudioSlot()
{
    m_backgroundAudio->enqueue(Phonon::MediaSource(QUrl(m_backgroundAudioPath)));
}
