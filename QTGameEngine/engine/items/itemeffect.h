#ifndef ITEMEFFECT_H
#define ITEMEFFECT_H
#include <QGraphicsItem>
#include <QPainter>

enum ItemEffectType {
    FADE_AWAY,
    SCALE,
    ROTATE,
    LIGHT
};

class ItemEffect {

public:
    ItemEffect(ItemEffectType effectType, double effectFactorValue);
    ItemEffect(ItemEffectType effectType, double effectFactorValue, double frameDelayValue);
    ItemEffect(ItemEffectType effectType, double effectFactorValue, double frameDelayValue, QGraphicsItem* owner);
    ItemEffectType getEffectType();
    double getEffectFactorValue();
    double getFrameDelayValue();
    void setBias(int biasX, int biasY);
    void paintLightEffect(QPainter* painter);

private:
    ItemEffectType effectType;
    double effectFactorValue; // angle: rotation, speed: scale, rotate, light: radius
    double frameDelayValue;
    bool shallAddLightEffect;
    QGraphicsItem* owner;
    int biasX;
    int biasY;
};

#endif // ITEMEFFECT_H
