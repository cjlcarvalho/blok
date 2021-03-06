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

#include "mainwindow.h"

#include <QtCore/QTimer>
#include <QtCore/QDebug>

#include <QtGui/QMouseEvent>
#include <QtGui/QGraphicsPixmapItem>
#include <QtGui/QGraphicsItemAnimation>

#include "ui_mainwindow.h"
#include "pluginloader.h"

#include "../blok-images/imagefactory.h"
#include "../blok-simulator/isimulator.h"
#include "../blok-audio/iaudio.h"

MainWindow *MainWindow::m_instance = nullptr;

MainWindow *MainWindow::instance()
{
    if (!m_instance)
        m_instance = new MainWindow;

    return m_instance;
}

void MainWindow::destroyInstance()
{
    delete m_instance;
}

MainWindow::MainWindow(ImageFactory *imageFactory,
                       ISimulator *simulator,
                       IAudio *audio,
                       QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _simulator(simulator),
    _imageFactory(imageFactory),
    _audio(audio),
    _timer(500)
{
    _pluginLoader = new PluginLoader;

    if (!_imageFactory && !_pluginLoader->imageFactories().empty())
        _imageFactory = _pluginLoader->imageFactories()[0];

    if (!_simulator && !_pluginLoader->simulators().empty())
        _simulator = _pluginLoader->simulators()[0];

    if (!_audio && !_pluginLoader->audios().empty())
        _audio = _pluginLoader->audios()[0];

    updateWindow();
}

MainWindow::~MainWindow()
{
    delete _audio;
}

void MainWindow::updateWindow()
{
    qsrand(1);
    ui->setupUi(this);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    setWindowTitle("Blok");

    _scene = new QGraphicsScene;
    _scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setMaximumSize(1000, 600);
    ui->graphicsView->setMinimumSize(1000, 600);
    ui->graphicsView->installEventFilter(this);

    if (!pluginsLoaded()) {
        qDebug() << "Couldn't load some plugins";
        return;
    }

    QMenu *imageMenu = ui->menuBar->addMenu(tr("&Image"));
    imageMenu->setObjectName(tr("&Image"));

    QMenu *simulatorMenu = ui->menuBar->addMenu(tr("&Simulator"));
    simulatorMenu->setObjectName(tr("&Simulator"));

    QMenu *audioMenu = ui->menuBar->addMenu(tr("&Audio"));
    audioMenu->setObjectName(tr("&Audio"));

    _timer.setFrameRange(0, 100);
    _animation.setTimeLine(&_timer);

    connect(_pluginLoader, SIGNAL(updateImageFactories(QList<ImageFactory*>)),
            this, SLOT(updateImageFactoriesMenu(QList<ImageFactory*>)));

    connect(_pluginLoader, SIGNAL(updateSimulators(QList<ISimulator*>)),
            this, SLOT(updateSimulatorsMenu(QList<ISimulator*>)));

    connect(_pluginLoader, SIGNAL(updateAudios(QList<IAudio*>)),
            this, SLOT(updateAudioMenu(QList<IAudio*>)));

    connect(_simulator, SIGNAL(bodiesCreated(QList<QPointF>)),
            SLOT(bodiesCreated(QList<QPointF>)));
    connect(_simulator, SIGNAL(bodiesUpdated(QList<QPointF>)),
            SLOT(bodiesUpdated(QList<QPointF>)));
    connect(this, SIGNAL(bodyClicked(QPointF)),
            _simulator, SLOT(removeBody(QPointF)));

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

    _audio->startBackgroundAudio("qrc:///resources/sounds/background.wav");

    startMenus();
}

bool MainWindow::pluginsLoaded() const
{
    return _imageFactory && _simulator && _audio;
}

void MainWindow::startMenus()
{
    updateImageFactoriesMenu(_pluginLoader->imageFactories());
    updateSimulatorsMenu(_pluginLoader->simulators());
    updateAudioMenu(_pluginLoader->audios());
}

void MainWindow::updateImageFactoriesMenu(const QList<ImageFactory *> &imageFactories)
{
    QList<QMenu *> imageMenu = ui->menuBar->findChildren<QMenu *>(tr("&Image"));

    if (imageMenu.empty())
        return;

    imageMenu[0]->clear();

    for (ImageFactory *factory : imageFactories) {
        QString title = QString(factory->metaObject()->className()).replace("ImageFactory", QString());

        QAction *action = new QAction(title, factory);

        connect(action, SIGNAL(triggered(bool)), this, SLOT(reloadWindow()));

        imageMenu[0]->addAction(action);
    }
}

void MainWindow::updateSimulatorsMenu(const QList<ISimulator *> &simulators)
{
    QList<QMenu *> simulatorMenu = ui->menuBar->findChildren<QMenu *>(tr("&Simulator"));

    if (simulatorMenu.empty())
        return;

    simulatorMenu[0]->clear();

    for (ISimulator *simulator : simulators) {
        QString title = QString(simulator->metaObject()->className()).replace("Simulator", QString());

        QAction *action = new QAction(title, simulator);

        connect(action, SIGNAL(triggered(bool)), this, SLOT(reloadWindow()));

        simulatorMenu[0]->addAction(action);
    }
}

void MainWindow::updateAudioMenu(const QList<IAudio *> &audios)
{
    QList<QMenu *> audioMenu = ui->menuBar->findChildren<QMenu *>(tr("&Audio"));

    if (audioMenu.empty())
        return;

    audioMenu[0]->clear();

    for (IAudio *audio : audios) {
        QString title = QString(audio->metaObject()->className()).replace("Audio", QString());

        QAction *action = new QAction(title, audio);

        connect(action, SIGNAL(triggered(bool)), this, SLOT(reloadWindow()));

        audioMenu[0]->addAction(action);
    }
}

void MainWindow::reloadWindow()
{
    QAction *action = dynamic_cast<QAction *>(sender());

    ImageFactory *factory = dynamic_cast<ImageFactory *>(action->parent());

    if (factory && factory->metaObject()->className() != _imageFactory->metaObject()->className()) {
        MainWindow::reload(factory, _simulator, _audio->clone());
        return;
    }

    ISimulator *simulator = dynamic_cast<ISimulator *>(action->parent());

    if (simulator && simulator->metaObject()->className() != _simulator->metaObject()->className()) {
        MainWindow::reload(_imageFactory, simulator, _audio->clone());
        return;
    }

    IAudio *audio = dynamic_cast<IAudio *>(action->parent());

    if (audio && audio->metaObject()->className() != _audio->metaObject()->className()) {
        MainWindow::reload(_imageFactory, _simulator, audio);
        return;
    }
}

void MainWindow::reload(ImageFactory *imageFactory, ISimulator *simulator, IAudio *audio)
{
    MainWindow *copyInstance = new MainWindow(imageFactory, simulator, audio);

    delete m_instance;

    copyInstance->show();

    m_instance = copyInstance;
}

void MainWindow::init()
{
    _scene->clear();
    _scene->setSceneRect(-450, -250, 900, 500);

    // Background
    _imageFactory->createBackgroundImage()->createBackground(_scene);

    // Banner
    _banner = _scene->addRect(-250, -50, 500, 100);
    _banner->setPos(800, -200);
    _banner->setBrush(QColor(0xDF, 0xC1, 0x01));

    _bannerMessage = new QGraphicsTextItem(_banner);
    _bannerMessage->setFont(QFont("Times", 18, QFont::Bold));
    _bannerMessage->setPos(-_bannerMessage->boundingRect().width() / 2,
                           -_bannerMessage->boundingRect().height() / 1.25);

    QGraphicsTextItem *text2 = new QGraphicsTextItem("Press any key to start", _banner);
    text2->setFont(QFont("Times", 10, QFont::Bold));
    text2->setPos(-text2->boundingRect().width() / 2, text2->boundingRect().height());

    // Ground
    _imageFactory->createGroundImage()->createGround(_scene);
}

void MainWindow::bannerEnter()
{
    if (_stateMachine.configuration().contains(_initialState))
        setBannerMessage("Remove all the blocks but do not\nlet this guy hit the ground, okay ?");
    if (_stateMachine.configuration().contains(_youWonState))
        setBannerMessage("Congratulations ! You won !");
    if (_stateMachine.configuration().contains(_youLostState))
        setBannerMessage("I'm sorry, you lost ! Try again !");

    _animation.setItem(_banner);

    for (int i = 0; i < 200; ++i)
        _animation.setPosAt(i / 200.0, QPointF(800 - i * 4, -200));

    _timer.start();
}

void MainWindow::bannerLeave()
{
    _animation.setItem(_banner);

    for (int i = 0; i < 200; ++i)
        _animation.setPosAt(i / 200.0, QPointF(i * 4, -200));

    _timer.start();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (_stateMachine.configuration().contains(_runningState)
            && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *>(event);
        if (mouseEvent) {
            QPoint point =  mouseEvent->pos();
            QPointF scenePoint = ui->graphicsView->mapToScene(point);
            QGraphicsItem *item = ui->graphicsView->scene()->itemAt(scenePoint);

            if (item) {
                for (int i = 0; i < _bodyRects.size(); i++) {
                    if (_bodyRects[i] == item && i != (_bodyRects.size() - 1)) {
                        emit bodyClicked(_bodyRects[i]->pos());

                        _bodyRects.removeAt(i);

                        _audio->playClickAudio("qrc:///resources/sounds/click.wav");

                        _scene->removeItem(item);

                        break;
                    }
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

void MainWindow::bodiesUpdated(const QList<QPointF> &bodies)
{
    for (int i = 0; i < bodies.size(); i++)
        _bodyRects[i]->setPos(bodies[i].x(), -bodies[i].y());
}

void MainWindow::bodiesCreated(const QList<QPointF> &bodies)
{
    _bodyRects.clear();

    for (int i = 0; i < bodies.size(); i++) {
        QGraphicsRectItem *rect = 0;

        if (i == (bodies.size() - 1)) // Player
            rect = _imageFactory->createPlayerImage()->createPlayer(_scene);
        else // Block
            rect = _imageFactory->createBlockImage()->createBlock(_scene);

        rect->setPos(bodies[i].x(), -bodies[i].y());
        rect->setPen(QPen(Qt::NoPen));

        _bodyRects.append(rect);
    }
}

void MainWindow::setBannerMessage(const QString &bannerMessage)
{
    _bannerMessage->setPlainText(bannerMessage);
    _bannerMessage->setPos(-_bannerMessage->boundingRect().width() / 2,
                           -_bannerMessage->boundingRect().height() / 1.25);
}

void MainWindow::youWon()
{
    _audio->playYouWonAudio("qrc:///resources/sounds/youwon.wav");
}

void MainWindow::youLost()
{
    _audio->playYouLostAudio("qrc:///resources/sounds/youlost.wav");
}
