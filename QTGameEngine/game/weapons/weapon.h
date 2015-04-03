#ifndef WEAPON_H
#define WEAPON_H
#include "engine/items/item.h"
#include "engine/processors/particlesprocessor.h"
#include "game/enums/weaponsEnum.h"
#include "game/resources.h"
#include "game/constants.h"
#include "engine/utils/sceneutils.h"

class Weapon: public Item {
protected:
    QPointer<ParticlesProcessor> particles;
    QPointer<ParticlesProcessor> explParticles;
    QPointer<Item> explosion;
    QPointer<Item> owner;
    int damage;
    virtual void die();
    virtual void action();

public:
    Weapon(QPointer<Item> owner, Asset itemAsset, QPoint speed);
    Weapon(QPointer<Item> owner, Asset itemAsset, Asset particlesAsset, int particlesCount, QPoint speed);
    virtual ~Weapon();
    virtual void start();

};

#endif // WEAPON_H
