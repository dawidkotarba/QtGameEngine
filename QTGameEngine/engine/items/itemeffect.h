#ifndef ITEMEFFECT_H
#define ITEMEFFECT_H
#include <QGraphicsItem>
#include <QGraphicsEffect>
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include "engine/utils/timerutils.h"
#include "engine/enums/enums.h"
#include "engine/utils/utils.h"

class ItemEffect {

public:
    ItemEffect(QGraphicsItem* owner, ItemEffectType effectType, qreal effectFactorValue = 0);
    ItemEffectType& getEffectType();
    qreal getEffectFactorValue();
    double getFrameDelayValue();
    void setOffset(int offsetX, int offsetY);
    void apply(QPainter* painter = NULL);
    void setFrameDelayValue(int frameDelayValue);
    void setLightEffectColor(QColor &color);

private:
    ItemEffectType effectType;    
    qreal effectFactorValue; // angle: rotation, speed: scale, rotate, light: radius
    int frameDelayValue;
    QGraphicsItem* owner;
    int offsetX;
    int offsetY;

    QColor lightColor;

    void paintLightEffect(QPainter* painter);
    int randomLightAlpha();
    void updateInnerLightColor(QRadialGradient& radialGradient);
    void updateOuterLightColor(QRadialGradient& radialGradient, const QColor& lightColor);
    void rotate();
    void fadeAway();
    void scale();
};

#endif // ITEMEFFECT_H
