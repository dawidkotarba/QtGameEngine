#ifndef ITEM_H
#define ITEM_H
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsItem>
#include <QList>
#include <QMediaPlayer>
#include <math.h>
#include <iostream>
#include "engine/utils/utils.h"
#include "engine/utils/sceneutils.h"
#include "engine/utils/timerutils.h"
#include "engine/items/itemeffect.h"
#include "engine/items/asset.h"
#include "engine/utils/memorymanager.h"
#include "engine/processors/animationprocessor.h"
#include "engine/utils/soundutils.h"

class Item : public QGraphicsItem, public QObject {
public:
    Item();
    Item(const QString& sourceFolder, const QString& imgPattern, int imgCount);
    Item(const QString& sourceFolder, const QString& imgPattern, int imgCount, QPoint& position);

    Item(Asset asset):
        Item(asset.getPath(), asset.getImgPattern(), asset.getImgCount()){}

    Item(Asset asset, QPointF position):
        Item(asset){
        setPos(position);
    }

    virtual ~Item();
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void setPercentPosition(QPoint& position);
    QPoint getSpeed();
    void setSpeed(QPoint& speed);
    int getAcceleration();
    void setAcceleration(int acceleration);
    void shallBlink(bool value, int minFrequency, int maxFrequency);
    QList<QPointer<Item> > getCollidingItems();
    void setItemId(int id);
    int getItemId();
    bool collidesWithItemType(int itemId);
    void makeMonitor();
    QPointer<AnimationProcessor> getAnimationProcessor();
    void increaseHealth(int value);
    void decreaseHealth(int value);
    void setHealth(int value);
    bool isDead();
    void addEffect(ItemEffect& effect);
    void resetTransformation();
    void resetRotation();
    void resetOpacity();
    void resetScale();
    void setInitialScale(qreal scale);
    void setInitialOpacity(qreal opacity);
    void setBiasX(qreal value);
    void setBiasY(qreal value);
    void setBias(qreal x, qreal y);
    qreal getBiasX();
    qreal getBiasY();
    void setDestroyable(bool value);
    bool isDestroyable();
    virtual void start();
    virtual void stop();
    bool isStarted();
    void setStarted(bool value);
    void moveEveryFrame(QPointF &point);
    void setRepeatable(bool value);
    void setInitPos(QPoint& value);
    void setRemoveWhenOut(bool value);
    bool isMarkedAsForDelete();
    void markAsForDelete();
    void setAddedToScene(bool value);
    bool isAddedToScene();
    void addToScene();
    void removeFromScene();
    bool isOutOfScene();
    void setEnemy(bool value);
    bool isEnemy();
    void setBoundingRectDividers(qreal width, qreal height);
    void setBoundingRectBias(int width, int height);
    void addLightEffect(int radius, int biasX = 0, int biasY = 0);
    int getCurrentRotationAngle();
    void setCurrentRotationAngle(int currentRotationAngle);
    void setCurrentOpacity(qreal currentOpacity);
    void setCurrentScale(qreal currentScale);
    bool getShallCalculateTransformOP();
    void setShallCalculateTransformOP(bool shallCalculateTransformOP);
    qreal getCurrentOpacity();
    qreal getCurrentScale();
    qreal getInitialOpacity();
    qreal getInitialScale();

protected:
    void advance(int step);
    void initScene(const QString& sourceFolder, const QString& imgPattern, int imgCount);
    void playSound(const QString& fileName, int volume = 100);
    void repeat();
    virtual void move();
    virtual void action(){}
    virtual void die();
    QPointer<AnimationProcessor> animationProcessor;
    QPainter* painterPtr;
    QPoint percentPosition;
    QPoint speed;
    int acceleration;
    QTransform transformation;
    QPointF initPos;
    bool blinks;
    int blinkMinFrequency;
    int blinkMaxFrequency;
    int itemId;
    int controlId;
    bool monitor;
    int health;
    qreal biasX;
    qreal biasY;
    QPointF moveBias;
    bool started;
    bool enemy;
    qreal boundingRectWidthDivider;
    qreal boundingRectHeightDivider;
    int boundingRectWidthBias;
    int boundingRectHeightBias;

    // effects
    QList<ItemEffect> transformationEffects;
    ItemEffect* lightEffect;
    QPoint calculateTransformOriginPoint();
    bool shallCalculateTransformOP;
    int currentRotationAngle;
    qreal currentOpacity;
    qreal currentScale;
    qreal initialOpacity;
    qreal initialScale;

private:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    QPointer<Image> currentImage;
    bool shallRemoveWhenOut;
    void removeWhenOut();
    bool destroyable;
    bool repeatable;
    bool markedAsForDelete;
    bool addedToScene;
    bool forcePaint;
};

#endif // ITEM_H
