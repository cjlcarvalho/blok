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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QList>
#include <QtCore/QTimeLine>
#include <QtCore/QStateMachine>
#include <QtCore/QSharedPointer>

#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsItemAnimation>

class QGraphicsScene;
class QGraphicsRectItem;
class QGraphicsTextItem;

namespace Ui {
class MainWindow;
}

class PluginLoader;
class ISimulator;
class ImageFactory;
class IAudio;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow *instance();
    static void destroyInstance();
    bool pluginsLoaded() const;

Q_SIGNALS:
    void bodyClicked(const QPointF &body);
    void keyPressed();

public Q_SLOTS:
    void init();
    void bannerEnter();
    void bannerLeave();

private Q_SLOTS:
    void bodiesUpdated(const QList<QPointF> &bodies);
    void bodiesCreated(const QList<QPointF> &bodies);
    void setBannerMessage(const QString &bannerMessage);
    void youWon();
    void youLost();
    void updateImageFactoriesMenu(const QList<ImageFactory *> &imageFactories);
    void updateSimulatorsMenu(const QList<ISimulator *> &simulators);
    void updateAudioMenu(const QList<IAudio *> &audios);
    void reloadWindow();

protected:
    explicit MainWindow(ImageFactory *imageFactory = 0,
                        ISimulator *simulator = 0,
                        IAudio *audio = 0,
                        QWidget *parent = 0);
    ~MainWindow();
    bool eventFilter(QObject *obj, QEvent *event);

private:
    static void reload(ImageFactory *imageFactory,
                       ISimulator *simulator,
                       IAudio *audio);
    void updateWindow();
    void startMenus();

private:
    static MainWindow *m_instance;

    QSharedPointer<Ui::MainWindow> ui;
    QGraphicsScene *_scene;

    PluginLoader *_pluginLoader;

    ISimulator *_simulator;
    ImageFactory *_imageFactory;
    IAudio *_audio;

    QGraphicsRectItem *_banner;
    QGraphicsTextItem *_bannerMessage;
    QTimeLine _timer;
    QGraphicsItemAnimation _animation;

    QList<QGraphicsRectItem *> _bodyRects;

    QStateMachine _stateMachine;
    QState *_initialState;
    QState *_runningState;
    QState *_youWonState;
    QState *_youLostState;
};

#endif // MAINWINDOW_H
