#ifndef ROCKET_H
#define ROCKET_H
#include "game/weapons/weapon.h"
#include "game/resources.h"
#include "game/particles/particleexplosion.h"

class Rocket: public Weapon {
public:
    Rocket(QPointer<Item> owner):
        Weapon(owner, Asset(PATH_ROCKET), Asset(PATH_ROCKET_SMOKE_S), 10, QPoint(WEAPON_ROCKET_SPEED,0)){
        setBias(WEAPON_ROCKET_BIAS_X, WEAPON_ROCKET_BIAS_Y);
        particles->getItemsModifier()->setBias(WEAPON_ROCKET_PARTICLE_BIAS_X, WEAPON_ROCKET_PARTICLE_BIAS_Y);
        particles->getItemsModifier()->setDefaultScale(0.1);
        particles->getItemsModifier()->applyFadeEffect(0.1, 0.1);
        particles->getItemsModifier()->applyScaleEffect(0.2, 0.2);
        particles->setSpawnDelay(2);

        damage = WEAPON_ROCKET_DAMAGE;
        playSound("swoosh");
        addLightEffect(100, 50, 10);
    }

    void die(){

        fireball = new ParticlesProcessor(Asset(PATH_FIREBALL), 5, this);
        fireball->getItemsModifier()->applyRotateEffect(5,5,true);
        fireball->getItemsModifier()->setDefaultScale(0.1);
        fireball->getItemsModifier()->applyScaleEffect(0.06, 0.1);
        fireball->getItemsModifier()->applyFadeEffect(0.02, 0.02);
        fireball->getItemsModifier()->setBias(-50,-50);
        fireball->setRadius(50);
        fireball->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_1));
        fireball->setLooping(false);
        fireball->getItemsModifier()->addLightEffect(500,250,250);
        fireball->start();

        playSound("bomb2");
        Weapon::die();
    }

private:
    QPointer<ParticlesProcessor> fireball;
};

#endif // ROCKET_H
