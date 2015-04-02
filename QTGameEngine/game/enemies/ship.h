#ifndef SHIP_H
#define SHIP_H
#include "engine/items/item.h"
#include "game/constants.h"
#include "game/resources.h"
#include "game/particles/particleexplosion.h"
#include "game/weapons/enemyrocket.h"

class Ship: public Item
{
public:
    Ship();
    virtual ~Ship();
    virtual void action();

private:
    QPointer<ParticleExplosion> explosion;
    QPointer<ParticlesProcessor> particles;
    ItemEffect* itemEffect;
    qreal posYBias;
    bool hasFired;

    void die();
    void move();
    void initParticles();

};

#endif // SHIP_H
