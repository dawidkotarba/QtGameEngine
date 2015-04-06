#ifndef ITEMEFFECT_H
#define ITEMEFFECT_H
#include <QGraphicsItem>
#include <QGraphicsEffect>
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include "engine/utils/timerutils.h"
#include "engine/enums/enums.h"

class ItemEffect {

public:
    ItemEffect(QGraphicsItem* owner, ItemEffectType effectType, qreal effectFactorValue = 0);
    ItemEffectType& getEffectType();
    qreal getEffectFactorValue();
    double getFrameDelayValue();
    void setBias(int biasX, int biasY);
    void apply(QPainter* painter = NULL);
    void setFrameDelayValue(int frameDelayValue);
    void setLightEffectColor(int r, int g, int b);

private:
    ItemEffectType effectType;    
    qreal effectFactorValue; // angle: rotation, speed: scale, rotate, light: radius
    int frameDelayValue;
    QGraphicsItem* owner;
    int biasX;
    int biasY;

    // light colors
    int red;
    int green;
    int blue;

    void paintLightEffect(QPainter* painter);
    void rotate();
    void fadeAway();
    void scale();
};

#endif // ITEMEFFECT_H
