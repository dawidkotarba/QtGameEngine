#include "itemeffect.h"

ItemEffect::ItemEffect(ItemEffectType effectType, double effectFactorValue):
    shallAddLightEffect(false),
    biasX(0),
    biasY(0){
    this->effectType = effectType;
    this->effectFactorValue = effectFactorValue;
}

ItemEffect::ItemEffect(ItemEffectType effectType, double effectFactorValue, double frameDelayValue):
    ItemEffect(effectType, effectFactorValue){
    this->frameDelayValue = frameDelayValue;
}

ItemEffect::ItemEffect(ItemEffectType effectType, double effectFactorValue, double frameDelayValue, QGraphicsItem* owner):
    ItemEffect(effectType, effectFactorValue, frameDelayValue){

    this->owner = owner;

    if (effectType == ItemEffectType(LIGHT))
        shallAddLightEffect = true;

}

void ItemEffect::paintLightEffect(QPainter *painter){
    if (!shallAddLightEffect || painter == NULL)
        return;

    QPoint updatedPos(owner->pos().x()+biasX, owner->pos().y()+biasY);

    painter->setCompositionMode(QPainter::CompositionMode_Plus);
    painter->setPen(Qt::NoPen);

    QRadialGradient light(updatedPos, effectFactorValue, updatedPos);
    light.setColorAt(0.0f, QColor(255,200,75,25+qrand()%75));
    light.setColorAt(1.0f, QColor(255,255,255,0));
    painter->setBrush(light);
    painter->drawEllipse(updatedPos,effectFactorValue,effectFactorValue);
}

ItemEffectType ItemEffect::getEffectType(){
    return effectType;
}

double ItemEffect::getEffectFactorValue(){
    return effectFactorValue;
}

double ItemEffect::getFrameDelayValue(){
    return frameDelayValue;
}

void ItemEffect::setBias(int biasX, int biasY){
    this->biasX = biasX;
    this->biasY = biasY;
}
