/********************************************************************************
 *   Copyright (C) 2012 by Sandro Andrade <sandroandrade@kde.org>               *
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

#include "mainwindow.h"

#include <QtCore/QTimer>
#include <QtCore/QDebug>

#include <QtGui/QSound>
#include <QtGui/QBrush>
#include <QtGui/QMouseEvent>
#include <QtGui/QGraphicsPixmapItem>
#include <QtGui/QGraphicsItemAnimation>

#include <phonon/MediaObject>

#include <Box2D/Dynamics/b2Body.h>

#include "ui_mainwindow.h"

#include <simulator.h>
#include "pluginloader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _timer(500)
{
    qsrand(1);
    ui->setupUi(this);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    _scene = new QGraphicsScene;
    _scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    _pluginLoader = new PluginLoader;
    _imageFactory = _pluginLoader->getImageFactory();

    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setMaximumSize(1000, 600);
    ui->graphicsView->setMinimumSize(1000, 600);
    ui->graphicsView->installEventFilter(this);

    _timer.setFrameRange(0, 100);
    _animation.setTimeLine(&_timer);

    _simulator = new Simulator(this);
    connect(_simulator, SIGNAL(bodiesCreated(QList<b2Body*>)),
                        SLOT(bodiesCreated(QList<b2Body*>)));
    connect(_simulator, SIGNAL(bodiesUpdated(QList<b2Body*>)),
                        SLOT(bodiesUpdated(QList<b2Body*>)));
    connect(this, SIGNAL(bodyClicked(b2Body*)),
            _simulator, SLOT(removeBody(b2Body*)));

    _initialState = new QState();
    _runningState = new QState();
    _youWonState  = new QState();
    _youLostState = new QState();

    connect(_initialState, SIGNAL(entered()), this, SLOT(init()));
    connect(_initialState, SIGNAL(entered()), _simulator, SLOT(init()));
    connect(_initialState, SIGNAL(entered()), this, SLOT(bannerEnter()));
    connect(_initialState, SIGNAL(exited()), this, SLOT(bannerLeave()));
    _initialState->addTransition(this, SIGNAL(keyPressed()), _runningState);

    connect(_runningState, SIGNAL(entered()), _simulator, SLOT(start()));
    _runningState->addTransition(_simulator, SIGNAL(youWon()), _youWonState);
    _runningState->addTransition(_simulator, SIGNAL(youLost()), _youLostState);

    connect(_youWonState, SIGNAL(entered()), this, SLOT(bannerEnter()));
    connect(_youWonState, SIGNAL(entered()), this, SLOT(youWon()));
    _youWonState->addTransition(this, SIGNAL(keyPressed()), _initialState);

    connect(_youLostState, SIGNAL(entered()), this, SLOT(bannerEnter()));
    connect(_youLostState, SIGNAL(entered()), this, SLOT(youLost()));
    _youLostState->addTransition(this, SIGNAL(keyPressed()), _initialState);

    _stateMachine.addState(_initialState);
    _stateMachine.addState(_runningState);
    _stateMachine.addState(_youWonState);
    _stateMachine.addState(_youLostState);
    _stateMachine.setInitialState(_initialState);

    _stateMachine.start();

    _backgroundAudio = Phonon::createPlayer(Phonon::NoCategory, Phonon::MediaSource(":/resources/sounds/background.wav"));
    connect(_backgroundAudio, SIGNAL(aboutToFinish()), SLOT(enqueueBackgroundAudio()));
    _backgroundAudio->play();
}

MainWindow::~MainWindow()
{
    _backgroundAudio->stop();
    delete _backgroundAudio;
}

void MainWindow::init()
{
    _scene->clear();
    _scene->setSceneRect(-450, -250, 900, 500);

    // Background
    _imageFactory->createBackgroundImage()->createBackground(_scene);
    qDebug() << "criou background";

    // Banner
    _banner = _scene->addRect(-250, -50, 500, 100);
    _banner->setPos(800, -200);
    _banner->setBrush(QColor(0xDF, 0xC1, 0x01));

    _bannerMessage = new QGraphicsTextItem(_banner);
    _bannerMessage->setFont(QFont("Times", 18, QFont::Bold));
    _bannerMessage->setPos(-_bannerMessage->boundingRect().width()/2, -_bannerMessage->boundingRect().height()/1.25);

    QGraphicsTextItem *text2 = new QGraphicsTextItem("Press any key to start", _banner);
    text2->setFont(QFont("Times", 10, QFont::Bold));
    text2->setPos(-text2->boundingRect().width()/2, text2->boundingRect().height());

    // Ground
    _imageFactory->createGroundImage()->createGround(_scene);
    qDebug() << "criou ground";
}

void MainWindow::bannerEnter()
{
    if(_stateMachine.configuration().contains(_initialState))
        setBannerMessage("Remove all the blocks but do not\nlet this guy hit the ground, okay ?");
    if(_stateMachine.configuration().contains(_youWonState))
        setBannerMessage("Congratulations ! You won !");
    if(_stateMachine.configuration().contains(_youLostState))
        setBannerMessage("I'm sorry, you lost ! Try again !");

    _animation.setItem(_banner);

    for (int i = 0; i < 200; ++i)
        _animation.setPosAt(i / 200.0, QPointF(800-i*4, -200));

    _timer.start();
}

void MainWindow::bannerLeave()
{
    _animation.setItem(_banner);

    for (int i = 0; i < 200; ++i)
        _animation.setPosAt(i / 200.0, QPointF(i*4, -200));

    _timer.start();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (_stateMachine.configuration().contains(_runningState) && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(event);
        if (mouseEvent)
        {
            QPoint point =  mouseEvent->pos();
            QPointF scenePoint = ui->graphicsView->mapToScene(point);
            QGraphicsItem *item = ui->graphicsView->scene()->itemAt(scenePoint);

            if (item)
            {
                foreach(b2Body *body, m_bodyRect.keys())
                    if (m_bodyRect[body] == item && item != _player)
                    {
                        emit bodyClicked(body);
                        Phonon::MediaObject *audio = Phonon::createPlayer(Phonon::NoCategory, Phonon::MediaSource(":/resources/sounds/click.wav"));
                        connect(audio, SIGNAL(finished()), audio, SLOT(deleteLater()));
                        audio->play();
                        _scene->removeItem(item);
                        break;
                    }
            }
        }
    }
    if ((_stateMachine.configuration().contains(_initialState) ||
         _stateMachine.configuration().contains(_youWonState) ||
         _stateMachine.configuration().contains(_youLostState)) &&
         event->type() == QEvent::KeyPress && _timer.state() == QTimeLine::NotRunning)
        emit keyPressed();

    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::bodiesUpdated(const QList<b2Body *> &bodies)
{
    foreach (b2Body *body, bodies)
    {
        const b2Vec2 &pos = body->GetPosition();
        m_bodyRect[body]->setPos(pos.x, -pos.y);
    }
}

void MainWindow::bodiesCreated(const QList<b2Body *> &bodies)
{
    m_bodyRect.clear();
    foreach (b2Body *body, bodies)
    {
        const b2Vec2 &position = body->GetPosition();
        QGraphicsRectItem *rect = 0;
        if (body->GetUserData())
        {
            // Player
            rect = _imageFactory->createPlayerImage()->createPlayer(_scene);
            qDebug() << "criou player";
        }
        else
        {
            // Block
            rect = _imageFactory->createBlockImage()->createBlock(_scene);
            qDebug() << "criou block";
        }
        rect->setPos(position.x, -position.y);
        rect->setPen(QPen(Qt::NoPen));

        m_bodyRect[body] = rect;
    }
}

void MainWindow::setBannerMessage(const QString &bannerMessage)
{
    _bannerMessage->setPlainText(bannerMessage);
    _bannerMessage->setPos(-_bannerMessage->boundingRect().width()/2, -_bannerMessage->boundingRect().height()/1.25);
}

void MainWindow::enqueueBackgroundAudio()
{
    _backgroundAudio->enqueue(Phonon::MediaSource(":/resources/sounds/background.wav"));
}

void MainWindow::youWon()
{
    Phonon::MediaObject *audio = Phonon::createPlayer(Phonon::NoCategory, Phonon::MediaSource(":/resources/sounds/youwon.wav"));
    connect(audio, SIGNAL(finished()), audio, SLOT(deleteLater()));
    audio->play();
}

void MainWindow::youLost()
{
    Phonon::MediaObject *audio = Phonon::createPlayer(Phonon::NoCategory, Phonon::MediaSource(":/resources/sounds/youlost.wav"));
    connect(audio, SIGNAL(finished()), audio, SLOT(deleteLater()));
    audio->play();
}
