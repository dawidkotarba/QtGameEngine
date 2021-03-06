#ifndef ITEMSMODIFIER_H
#define ITEMSMODIFIER_H
#include <QList>
#include <QPointer>
#include "engine/utils/itemutils.h"

class ItemsModifier : public QObject {

public:
    ItemsModifier(QList<QPointer<Item> >& attachedItems):
        items(attachedItems){
        qDebug() << "Attaching items: " << items.size();
    }

    void makeVisible(bool condition){
        ItemUtils::getInstance().makeVisible(items, condition);
    }

    void moveEveryFrame(QPointF& move){
        ItemUtils::getInstance().moveEveryFrame(items, move);
    }

    void applyRotateEffect(int minAngle, int maxAngle, bool allowNegative, int interval = 1){
        ItemUtils::getInstance().applyRotateEffect(items, minAngle, maxAngle, allowNegative, interval);
    }

    void applyFadeEffect(qreal minSpeed, qreal maxSpeed, int interval = 1){
        ItemUtils::getInstance().applyFadeEffect(items, minSpeed, maxSpeed, interval);
    }

    void applyScaleEffect(qreal minSpeed, qreal maxSpeed, int interval = 1){
        ItemUtils::getInstance().applyScaleEffect(items, minSpeed, maxSpeed, interval);
    }

    void setDefaultScale(qreal scale){
       ItemUtils::getInstance().setDefaultScale(items, scale);
    }

    void setDefaultOpacity(qreal opacity){
       ItemUtils::getInstance().setDefaultOpacity(items, opacity);
    }

    void setDefaultRotation(qreal defaultRotation){
        ItemUtils::getInstance().setDefaultRotation(items, defaultRotation);
    }

    void stop(){
        ItemUtils::getInstance().stop(items);
    }

    void start(){
        ItemUtils::getInstance().start(items);
    }

    void setVisible(bool value){
       ItemUtils::getInstance().setVisible(items, value);
    }

    void setStarted(bool value){
       ItemUtils::getInstance().setStarted(items, value);
    }

    void setPos(QPointF& pos){
       ItemUtils::getInstance().setPos(items, pos);
    }

    void setOffset(qreal x, qreal y){
        ItemUtils::getInstance().setOffset(items, x, y);
    }

    void setDestroyable(bool value){
       ItemUtils::getInstance().setDestroyable(items, value);
    }

    void setRepeatable(bool value){
        ItemUtils::getInstance().setRepeatable(items, value);
    }

    void shallBlink(bool value, int minFrequency, int maxFrequency){
        ItemUtils::getInstance().shallBlink(items, value, minFrequency, maxFrequency);
    }

    void addLightEffect(int radius, int offsetX = 0, int offsetY = 0){
        ItemUtils::getInstance().addLightEffect(items, radius, offsetX, offsetY);
    }

    bool setLightEffectColor(QColor& color){
        return ItemUtils::getInstance().setLightEffectColor(items, color);
    }

private:
    QList<QPointer<Item> > items;
};

#endif // ITEMSMODIFIER_H
