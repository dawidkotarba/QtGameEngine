#ifndef ITEMEFFECT_H
#define ITEMEFFECT_H
#include <QGraphicsItem>
#include <QPainter>
#include "engine/utils/timerutils.h"

enum ItemEffectType {
    FADE_AWAY,
    SCALE,
    ROTATE,
    LIGHT
};

class ItemEffect {

public:
    ItemEffect(QGraphicsItem* owner, ItemEffectType effectType, qreal effectFactorValue = 0);
    ItemEffectType getEffectType();
    qreal getEffectFactorValue();
    double getFrameDelayValue();
    void setBias(int biasX, int biasY);
    void apply(QPainter* painter = NULL);
    void setFrameDelayValue(int frameDelayValue);

private:
    ItemEffectType effectType;
    qreal effectFactorValue; // angle: rotation, speed: scale, rotate, light: radius
    int frameDelayValue;
    QGraphicsItem* owner;
    int biasX;
    int biasY;

    void paintLightEffect(QPainter* painter);
    void rotate();
    void fadeAway();
    void scale();
};

#endif // ITEMEFFECT_H
