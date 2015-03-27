#ifndef ITEMUTILS_H
#define ITEMUTILS_H
#include <QList>
#include <QPointer>
#include <QList>
#include "engine/enums/enums.h"
#include "engine/items/item.h"

class ItemUtils{

public:

    static ItemUtils& getInstance(){
        static ItemUtils instance;
        return instance;
    }

    void makeVisible(QList<QPointer<Item> >& items, boolean condition){
        foreach(QPointer<Item> item, items)
            condition ? item->show() : item->hide();
    }

    void moveEveryFrame(QList<QPointer<Item> >& items, QPointF& move){
        foreach(QPointer<Item> item, items)
            item->moveEveryFrame(move);
    }

    void rotate(QList<QPointer<Item> >& items, int minAngle, int maxAngle, bool allowNegative, int interval = 1){
        foreach(QPointer<Item> item, items){

            int angle = Utils::getInstance().randInt(minAngle, maxAngle);

            if (allowNegative && Utils::getInstance().randInt(0,1))
                angle = -angle;

            ItemEffect effect(ItemEffectType(ROTATE), angle, interval);
            item->transform(effect);
        }
    }

    void fadeAway(QList<QPointer<Item> >& items, qreal minSpeed, qreal maxSpeed, int interval = 1){
        foreach(QPointer<Item> item, items){
            ItemEffect effect(ItemEffectType(FADE_AWAY), Utils::getInstance().randFloat(minSpeed, maxSpeed), interval);
            item->transform(effect);
        }
    }

    void scale(QList<QPointer<Item> >& items, qreal minSpeed, qreal maxSpeed, int interval = 1){
        foreach(QPointer<Item> item, items){
            ItemEffect effect(ItemEffectType(SCALE), Utils::getInstance().randFloat(minSpeed, maxSpeed), interval);
            item->transform(effect);
        }
    }

    void setInitialScale(QList<QPointer<Item> >& items, qreal scale){
        foreach(QPointer<Item> item, items)
            item->setInitialScale(scale);
    }

    void setInitialOpacity(QList<QPointer<Item> >& items, qreal opacity){
        foreach(QPointer<Item> item, items)
            item->setInitialOpacity(opacity);
    }

    void stop(QList<QPointer<Item> >& items){
        foreach(QPointer<Item> item, items)
            item->stop();
    }

    void start(QList<QPointer<Item> >& items){
        foreach(QPointer<Item> item, items)
            item->start();
    }

    void setVisible(QList<QPointer<Item> >& items, boolean value){
        foreach(QPointer<Item> item, items)
            item->setVisible(value);
    }

    void setStarted(QList<QPointer<Item> >& items, boolean value){
        foreach(QPointer<Item> item, items)
            item->setStarted(value);
    }

    void setPos(QList<QPointer<Item> >& items, QPointF& pos){
        foreach(QPointer<Item> item, items)
            item->setPos(pos);
    }

    void setBias(QList<QPointer<Item> >& items, qreal x, qreal y){
        foreach(QPointer<Item> item, items)
            item->setBias(x, y);
    }

    void setDestroyable(QList<QPointer<Item> >& items, bool value){
        foreach(QPointer<Item> item, items)
            item->setDestroyable(value);
    }

    void setRepeatable(QList<QPointer<Item> >& items, bool value){
        foreach(QPointer<Item> item, items)
            item->setRepeatable(value);
    }

    void addToScene(QList<QPointer<Item> >& items) {
        foreach(QPointer<Item> item, items)
            item->addToScene();
    }

    void removeFromScene(QList<QPointer<Item> >& items) {
        foreach(QPointer<Item> item, items)
            item->removeFromScene();
    }

    void shallBlink(QList<QPointer<Item> >& items, bool value, int minFrequency, int maxFrequency){
        foreach(QPointer<Item> item, items)
            item->shallBlink(value, minFrequency, maxFrequency);
    }

private:
    ItemUtils(){}
    ItemUtils(const ItemUtils &){}
    ItemUtils& operator=(const ItemUtils&);
    ~ItemUtils(){}
};

#endif // ITEMUTILS_H
