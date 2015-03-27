#ifndef FIGHTER_H
#define FIGHTER_H
#include "engine/items/item.h"
#include "engine/controls/controlable.h"
#include "enums/dierctionsEnum.h"
#include "enums/weaponsEnum.h"
#include "game/constants.h"
#include "game/resources.h"
#include "game/weapons/rocket.h"
#include "game/weapons/bullet.h"

class Fighter : public Item, public Controlable
{

public:
    Fighter();
    virtual ~Fighter();
    virtual void controlKeyPress(QKeyEvent* event);
    virtual void controlKeyRelease(QKeyEvent* event);

    void go(DirectionsEnum direction);
    void stopGoing();
    void fire();
    void stopFiring();
    bool isMoving();

private:
    void move();
    void action();
    void initParticles();
    void die();
    void stop();
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    QPointer<ParticlesProcessor> particles;
    QPointer<Image> stoppedImage;
    bool isGoingLeft;
    bool isGoingRight;
    bool isGoingUp;
    bool isGoingDown;

    bool isFiring;

    WeaponsEnum currentWeapon;
    int fireRate;
};

#endif // FIGHTER_H
