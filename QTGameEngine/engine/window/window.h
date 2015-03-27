#ifndef WINDOW_H
#define WINDOW_H
#include <QGraphicsScene>
#include <QtOpenGL>
#include <QtWidgets>
#include <QPointer>
#include <QMediaPlayer>
#include <iostream>
#include "engine/controls/inputcontroller.h"
#include "engine/constants.h"
#include "engine/utils/sceneutils.h"
#include "engine/utils/timerutils.h"
#include "engine/items/monitoritem.h"
#include "game/fighter.h"
#include "game/enemies/ufo.h"
#include "game/enemies/ufo2.h"
#include "game/enemies/ufo3.h"
#include "engine/items/itemspawner.h"
#include "engine/items/itemsmodifier.h"
#include "game/environment/clouds.h"
#include "game/environment/stars.h"
#include "game/enemies/asteroid.h"
#include "game/enemies/ship.h"
#include "splash.h"

class Window : public QGraphicsView
{
    Q_OBJECT
public:
    virtual ~Window();
    explicit Window(QObject* parent = 0);
    QGraphicsScene scene;
    QTimer timer;
    InputController inputController;

private:
    QPointer<QMediaPlayer> player;
    QPointer<Splash> splash;

    // Actors management
    QPointer<Item> monitorItem;
    QPointer<Fighter> fighter;
    QPointer<ItemSpawner<Ufo> > enemiesUfo;
    QPointer<ItemSpawner<Ufo2> > enemiesUfo2;
    QPointer<ItemSpawner<Ufo3> > enemiesUfo3;
    QPointer<ItemSpawner<Ship> > enemiesShip;
    QPointer<ItemSpawner<Asteroid> > enemiesAsteroid;

    // environment
    QPointer<ItemSpawner<Star16> > envStar16;
    QPointer<ItemSpawner<Star32> > envStar32;

    QPointer<ItemSpawner<Cloud> > envCloud;
    QPointer<ItemSpawner<Cloud2> > envCloud2;
    QPointer<ItemSpawner<Cloud3> > envCloud3;
    QPointer<ItemSpawner<Cloud4> > envCloud4;
    QPointer<ItemSpawner<Cloud5> > envCloud5;
    QPointer<ItemSpawner<Cloud6> > envCloud6;

    void initActors();    
    void deleteActors();

    void initBackgroundEnvironment();
    void initForegroundEnvironment();
    void deleteEnvironment();

    // testing    

signals:

public slots:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private slots:
    void MainClockTick();

};

#endif // WINDOW_H
