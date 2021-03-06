/********************************************************************************
 *   Copyright (C) 2012 by Sandro Andrade <sandroandrade@kde.org>               *
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

#include "box2dsimulator.h"

#include <QtCore/QDebug>
#include <QtCore/QTimerEvent>

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

static const float32 B2_TIMESTEP = 1.0f / 30.0f;    // krazy:exclude=staticobjects
static const int32 B2_VELOCITY_ITERATIONS = 8;      // krazy:exclude=staticobjects
static const int32 B2_POSITION_ITERATIONS = 4;      // krazy:exclude=staticobjects
static const float PI = 3.14159265359;

Box2DSimulator::Box2DSimulator(QObject *parent) :
    ISimulator(parent),
    _timerId(0),
    _world (0),
    _player(0),
    _ground(0),
    _playerString("Player")
{
}

Box2DSimulator::~Box2DSimulator()
{
    delete _world;
}

void Box2DSimulator::BeginContact(b2Contact *contact)
{
    if ((contact->GetFixtureA()->GetBody() == _ground && contact->GetFixtureB()->GetBody() == _player)
        || (contact->GetFixtureB()->GetBody() == _ground && contact->GetFixtureA()->GetBody() == _player)) {
        stop();
        emit youLost();
    }
}

void Box2DSimulator::start()
{
    if (!_timerId)
        _timerId = startTimer(3);
}

void Box2DSimulator::stop()
{
    killTimer(_timerId);
    _timerId = 0;
}

void Box2DSimulator::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == _timerId) {
        _world->Step(B2_TIMESTEP, B2_VELOCITY_ITERATIONS, B2_POSITION_ITERATIONS);

        for (int i = 0; i < m_bodies.size(); i++) {
            b2Vec2 pos = m_bodies[i]->GetPosition();
            m_bodiesPoints[i].setX(pos.x);
            m_bodiesPoints[i].setY(pos.y);
        }

        emit bodiesUpdated(m_bodiesPoints);
    }
    QObject::timerEvent(event);
}

void Box2DSimulator::init()
{
    delete _world;
    _world = new b2World(b2Vec2(0.0f, -10.0f));
    _world->SetContactListener(this);

    m_bodies.clear();
    m_bodiesPoints.clear();

    // Ground
    _ground = createBody(0.0f, -260.0f, 900.0f, 20.0f, false);

    // Blocks
    int i, j;
    for (i = 0; i < 10; ++i) {
        for (j = 0; j < 11 - i; ++j) {
            m_bodies.append(createBody(-150.0f + 15 * i + 30 * j, -236.0f + 30 * i,
                                       28.0f, 28.0f));
            m_bodiesPoints.append(QPointF(-150.0f + 15 * i + 30 * j, -236.0f + 30 * i));
        }
    }

    // Player
    j -= 2;

    m_bodies.append(_player = createBody(-150.0f + 15 * i + 30 * j, -236.0f + 30 * i + 14,
                                         56.0f, 56.0f));

    m_bodiesPoints.append(QPointF(-150.0f + 15 * i + 30 * j, -236.0f + 30 * i + 14));

    _player->SetUserData(&_playerString);

    emit bodiesCreated(m_bodiesPoints);
}

b2Body *Box2DSimulator::createBody(float32 x, float32 y, float32 width, float32 height,
                                   bool dynamic, float32 density, float32 friction, float32 restitution)
{
    b2BodyDef bodyDef;
    if (dynamic)
        bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    b2Body *body = _world->CreateBody(&bodyDef);
    b2PolygonShape box;
    box.SetAsBox(width / 2, height / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    body->CreateFixture(&fixtureDef);
    body->SetSleepingAllowed(true);

    return body;
}

void Box2DSimulator::removeBody(const QPointF &body)
{
    // buscando por um QPointF com o Y de body invertido
    QPointF bodyTemp(body.x(), -body.y());

    int index = m_bodiesPoints.indexOf(bodyTemp);

    if (index != -1) {
        b2Body *bodyBox2D = m_bodies[index];

        _world->DestroyBody(bodyBox2D);

        m_bodies.removeAt(index);
        m_bodiesPoints.removeAt(index);

        if (m_bodies.size() == 2) {
            stop();
            emit youWon();
        }
    }
}

Q_EXPORT_PLUGIN2(box2dsimulator, Box2DSimulator)
