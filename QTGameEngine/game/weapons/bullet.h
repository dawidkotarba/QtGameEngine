#ifndef BULLET_H
#define BULLET_H
#include "game/weapons/weapon.h"

class Bullet: public Weapon {

public:
    Bullet(QPointer<Item> owner):
        Weapon(owner, Asset(PATH_BULLET), QPoint(WEAPON_BULLET_SPEED,0)){
        setOffset(WEAPON_BULLET_OFFSET_X, WEAPON_BULLET_OFFSET_Y);
        damage = WEAPON_BULLET_DAMAGE;
        playSound("laser");

        ItemEffect lightEffect(this, ItemEffectType(LIGHT), 50);
        lightEffect.setOffset(90, 10);
        addEffect(lightEffect);
    }

    void die(){
        playSound("aliendeath");
        Weapon::die();
    }
};

#endif // BULLET_H
