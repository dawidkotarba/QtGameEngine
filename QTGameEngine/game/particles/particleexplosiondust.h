#ifndef PARTICLEEXPLOSIONDUST_H
#define PARTICLEEXPLOSIONDUST_H
#include "engine/utils/utils.h"
#include "game/resources.h"
#include "engine/items/item.h"
#include "engine/processors/particlesprocessor.h"
#include "game/constants.h"

class ParticleExplosionDust: public QObject
{
public:
    ParticleExplosionDust(QPointer<Item> owner, qreal bias = 0){

        QPointF dustMove(-1,-1);

        dust = new ParticlesProcessor(Asset(PATH_DUST),3, owner);
        dust->getItemsModifier()->setBias(bias,bias);
        dust->getItemsModifier()->applyRotateEffect(5,10,true);
        dust->getItemsModifier()->setDefaultScale(0.1);
        dust->getItemsModifier()->applyScaleEffect(0.01, 0.04);
        dust->getItemsModifier()->applyFadeEffect(0.01, 0.03);
        dust->getItemsModifier()->moveEveryFrame(dustMove);
        dust->setLooping(false);
        dust->setRadius(20);
        dust->start();

        dust2 = new ParticlesProcessor(Asset(PATH_STEAM),2, owner);
        dust2->getItemsModifier()->setBias(bias,bias);
        dust2->getItemsModifier()->applyRotateEffect(2,3,true);
        dust2->getItemsModifier()->setDefaultScale(0.1);
        dust2->getItemsModifier()->applyScaleEffect(0.01, 0.04);
        dust2->getItemsModifier()->applyFadeEffect(0.01, 0.03);
        dust2->getItemsModifier()->moveEveryFrame(dustMove);
        dust2->setLooping(false);
        dust2->setRadius(30);
        dust2->start();
    }

    ~ParticleExplosionDust(){
        clear_qptr(dust);
        clear_qptr(dust2);
    }

private:
    QPointer<ParticlesProcessor> dust;
    QPointer<ParticlesProcessor> dust2;
};

#endif // PARTICLEEXPLOSIONDUST_H
