#ifndef ROCKET_H
#define ROCKET_H
#include "game/weapons/weapon.h"
#include "game/resources.h"

class Rocket: public Weapon
{
public:
    Rocket(QPointer<Item> owner):
        Weapon(owner, Asset(PATH_ROCKET), Asset(PATH_ROCKET_SMOKE_S), 10, QPoint(WEAPON_ROCKET_SPEED,0)){
        setBias(WEAPON_ROCKET_BIAS_X, WEAPON_ROCKET_BIAS_Y);
        particles->getItemsModifier()->setBias(WEAPON_ROCKET_PARTICLE_BIAS_X, WEAPON_ROCKET_PARTICLE_BIAS_Y);
        particles->getItemsModifier()->setInitialScale(0.1);
        particles->getItemsModifier()->fadeAway(0.1, 0.1);
        particles->getItemsModifier()->scale(0.2, 0.2);
        particles->setSpawnDelay(2);

        damage = WEAPON_ROCKET_DAMAGE;
        playSound("swoosh");
    }

    void die(){
        playSound("bomb2");
        Weapon::die();
    }
};

#endif // ROCKET_H
