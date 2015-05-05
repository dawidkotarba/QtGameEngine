#ifndef ENEMYROCKET_H
#define ENEMYROCKET_H
#include "game/weapons/weapon.h"
#include "game/resources.h"
#include "game/weapons/rocket.h"
#include "engine/items/item.h"

class EnemyRocket: public Rocket {
public:
    EnemyRocket(QPointer<Item> owner):
        Rocket(owner){
        QPoint speed(ENEMY_WEAPON_ROCKET_SPEED,0);
        setSpeed(speed);
        setOffset(ENEMY_WEAPON_ROCKET_OFFSET_X, ENEMY_WEAPON_ROCKET_OFFSET_Y);

        ItemEffect lightEffect(this, ItemEffectType(LIGHT), 100);
        lightEffect.setOffset(50, 10);
        addEffect(lightEffect);
    }

    void action(){
        if (x() > SceneUtils::getInstance().getTranslatedWidth(100))
            return;

        QList<QPointer<Item> > collisions = getCollidingItems();

        if (!collisions.isEmpty())
            foreach (QPointer<Item> col, collisions)
                if (col->getItemId() == FIGHTER){
                    col->decreaseHealth(damage);
                    die();
                    return;
                }
    }
};


#endif // ENEMYROCKET_H
