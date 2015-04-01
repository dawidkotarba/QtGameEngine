#ifndef BULLET_H
#define BULLET_H
#include "game/weapons/weapon.h"

class Bullet: public Weapon {

public:
    Bullet(QPointer<Item> owner):
        Weapon(owner, Asset(PATH_BULLET), QPoint(WEAPON_BULLET_SPEED,0)){
        setBias(WEAPON_BULLET_BIAS_X, WEAPON_BULLET_BIAS_Y);
        damage = WEAPON_BULLET_DAMAGE;
        playSound("laser");
        addLightEffect(50, 90, 10);
    }

    void die(){
        playSound("aliendeath");
        Weapon::die();
    }
};

#endif // BULLET_H
