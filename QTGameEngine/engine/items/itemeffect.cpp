#include "itemeffect.h"

ItemEffect::ItemEffect(QGraphicsItem *owner, ItemEffectType effectType, qreal effectFactorValue):
    owner(NULL),
    frameDelayValue(1),
    offsetX(0),
    offsetY(0){
    this->owner = owner;
    this->effectType = effectType;
    this->effectFactorValue = effectFactorValue;
}

void ItemEffect::paintLightEffect(QPainter *painter){
    if (effectType != ItemEffectType(LIGHT) || painter == NULL)
        return;

    QPoint updatedPos(owner->x()+offsetX, owner->y()+offsetY);

    painter->setCompositionMode(QPainter::CompositionMode_Plus);
    painter->setPen(Qt::NoPen);

    QRadialGradient light(updatedPos, effectFactorValue, updatedPos);

    updateInnerLightColor(light);

    if (lightColor.isValid())
        updateOuterLightColor(light, lightColor);
    else
        updateOuterLightColor(light, COLOR_LIGHT_YELLOW);

    painter->setBrush(light);
    painter->drawEllipse(updatedPos,effectFactorValue,effectFactorValue);
}

void ItemEffect::updateInnerLightColor(QRadialGradient& radialGradient){
    radialGradient.setColorAt(1.0f, COLOR_WHITE_TRANSPARENT);
}

void ItemEffect::updateOuterLightColor(QRadialGradient& radialGradient,const QColor& lightColor){
    QColor lightColAlpha(lightColor);
    lightColAlpha.setAlpha(randomLightAlpha());
    radialGradient.setColorAt(0.0f,lightColAlpha);
}

int ItemEffect::randomLightAlpha(){
    return Utils::getInstance().randInt(25,100);
}

void ItemEffect::setLightEffectColor(QColor& color){
    lightColor = color;
}

ItemEffectType& ItemEffect::getEffectType(){
    return effectType;
}

qreal ItemEffect::getEffectFactorValue(){
    return effectFactorValue;
}

double ItemEffect::getFrameDelayValue(){
    return frameDelayValue;
}

void ItemEffect::setOffset(int offsetX, int offsetY){
    this->offsetX = offsetX;
    this->offsetY = offsetY;
}

void ItemEffect::apply(QPainter* painter){
    switch(effectType){
    case LIGHT:
        paintLightEffect(painter);
        break;
    case FADE:
        fadeAway();
        break;
    case SCALE:
        scale();
        break;
    case ROTATE:
        rotate();
        break;
    case BLUR:
        owner->setGraphicsEffect(new QGraphicsBlurEffect());
        break;
    case SHADOW:
        owner->setGraphicsEffect(new QGraphicsDropShadowEffect());
        break;
    }
}

void ItemEffect::rotate(){
    if (TimerUtils::getInstance().countEachFrame(frameDelayValue)){

        qreal rotation = owner->rotation();

        if (rotation > 360)
            rotation-=360;

        owner->setRotation(rotation+effectFactorValue);
    }
}

void ItemEffect::fadeAway(){

    qreal opacity = owner->opacity();

    if (opacity > 0 && TimerUtils::getInstance().countEachFrame(frameDelayValue)){
        owner->setOpacity(opacity-=effectFactorValue);

        if (opacity <= 0)
            owner->hide();
    }
}

void ItemEffect::scale(){

    qreal scale = owner->scale();

    if (scale > 0 && TimerUtils::getInstance().countEachFrame(frameDelayValue)){
        owner->setScale(scale+=effectFactorValue);

        if (scale <= 0)
            owner->hide();
    }
}

void ItemEffect::setFrameDelayValue(int frameDelayValue){
    this->frameDelayValue = frameDelayValue;
}
