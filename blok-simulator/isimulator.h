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

#ifndef ISIMULATOR_H
#define ISIMULATOR_H

#include <QtPlugin>

#include <QObject>
#include <QList>
#include <QPointF>

#include "blok-simulator_global.h"

class BLOKSIMULATORSHARED_EXPORT ISimulator : public QObject
{
    Q_OBJECT

Q_SIGNALS:
    void bodiesUpdated(const QList<QPointF> &bodies);
    void bodiesCreated(const QList<QPointF> &bodies);
    void youWon();
    void youLost();

public Q_SLOTS:
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void removeBody(const QPointF &body) = 0;

protected:
    explicit ISimulator(QObject *parent = 0);

protected:
    QList<QPointF> m_bodiesPoints;
};

Q_DECLARE_INTERFACE(ISimulator, "org.qt-project.blok-simulator.ISimulator")

#endif // ISIMULATOR_H
