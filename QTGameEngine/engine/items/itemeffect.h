#ifndef ITEMEFFECT_H
#define ITEMEFFECT_H
#include "qglobal.h"

enum ItemEffectType{
    FADE_AWAY,
    SCALE,
    ROTATE
};

class ItemEffect
{
public:

    ItemEffect(ItemEffectType effectType, qreal effectFactorValue){
        this->effectType = effectType;
        this->effectFactorValue = effectFactorValue;
        frameDelayValue = 1;
    }

    ItemEffect(ItemEffectType effectType, qreal effectFactorValue, qreal frameDelayValue):
    ItemEffect(effectType, effectFactorValue){
        this->frameDelayValue = frameDelayValue;
    }

    ItemEffectType getEffectType(){
        return effectType;
    }

    qreal getEffectFactorValue(){
        return effectFactorValue;
    }

    qreal getFrameDelayValue(){
        return frameDelayValue;
    }

private:
    ItemEffectType effectType;
    qreal effectFactorValue; // angle: rotation, speed: scale, rotate
    qreal frameDelayValue;
};

#endif // ITEMEFFECT_H
