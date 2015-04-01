#ifndef ENEMYROCKET_H
#define ENEMYROCKET_H
#include "game/weapons/weapon.h"
#include "game/resources.h"
#include "game/weapons/rocket.h"
#include "engine/items/item.h"

class EnemyRocket: public Rocket
{
public:
    EnemyRocket(QPointer<Item> owner):
        Rocket(owner){
        QPoint speed(ENEMY_WEAPON_ROCKET_SPEED,0);
        setSpeed(speed);
        setBias(ENEMY_WEAPON_ROCKET_BIAS_X, ENEMY_WEAPON_ROCKET_BIAS_Y);
        addLightEffect(100, 50, 10);
    }

    void action(){
        if (pos().x() > SceneUtils::getInstance().getTranslatedWidth(100))
            return;

        QList<QPointer<Item> > collisions = getCollidingItems();

        if (!collisions.isEmpty())
            foreach (QPointer<Item> col, collisions)
                if (col->getItemId() == FIGHTER_ID){
                    col->decreaseHealth(damage);
                    die();
                    return;
                }
    }
};


#endif // ENEMYROCKET_H
