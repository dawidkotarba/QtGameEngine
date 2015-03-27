#ifndef PARTICLEEXPLOSION_H
#define PARTICLEEXPLOSION_H
#include "engine/utils/utils.h"
#include "game/resources.h"
#include "engine/items/item.h"
#include "engine/processors/particlesprocessor.h"
#include "game/constants.h"
#include "game/particles/particleexplosiondust.h"

class ParticleExplosion : public ParticleExplosionDust {

public:
    ParticleExplosion(QPointer<Item> owner, qreal bias = 0):
    ParticleExplosionDust(owner, bias){
       initFireballs(owner, PATH_FIREBALL, PATH_FIREBALL2, bias);
    }

    ParticleExplosion(QPointer<Item> owner, const QString fireBallPath1, const QString fireBallPath2, qreal bias = 0):
    ParticleExplosionDust(owner, bias){
       initFireballs(owner, fireBallPath1, fireBallPath2, bias);
    }

    virtual ~ParticleExplosion(){
        clear_qptr(fireball);
        clear_qptr(fireball2);
    }

private:
    QPointer<ParticlesProcessor> fireball;
    QPointer<ParticlesProcessor> fireball2;

    void initFireballs(QPointer<Item> owner, const QString fireBallPath1, const QString fireBallPath2, qreal bias = 0){
        fireball = new ParticlesProcessor(Asset(fireBallPath1),1, owner);
        fireball->getItemsModifier()->setBias(bias,bias);
        fireball->getItemsModifier()->rotate(5,5,true);
        fireball->getItemsModifier()->setInitialScale(0.1);
        fireball->getItemsModifier()->scale(0.04, 0.04);
        fireball->getItemsModifier()->fadeAway(0.02, 0.02);
        fireball->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_1));
        fireball->setLooping(false);
        fireball->start();

        fireball2 = new ParticlesProcessor(Asset(fireBallPath2),1, owner);
        fireball2->getItemsModifier()->setBias(bias,bias);
        fireball2->getItemsModifier()->setInitialScale(0.1);
        fireball2->getItemsModifier()->scale(0.05, 0.10);
        fireball2->getItemsModifier()->fadeAway(0.02, 0.08);
        fireball2->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_1));
        fireball2->setLooping(false);
        fireball2->setRadius(3);
        fireball2->start();
    }

};

#endif // PARTICLEEXPLOSION_H
