#ifndef PARTICLES_H
#define PARTICLES_H
#include <QList>
#include <QPointer>
#include <QGraphicsItem>
#include "engine/items/item.h"
#include "engine/items/asset.h"
#include "engine/utils/utils.h"
#include "engine/utils/itemutils.h"
#include "engine/items/itemeffect.h"
#include "engine/items/itemsmodifier.h"

class ParticlesProcessor : public Item
{
public:
    ParticlesProcessor(Asset asset, int count);
    ParticlesProcessor(Asset asset, int count, QPointer<Item> owner);
    ~ParticlesProcessor();

    void setRadius(int radius);
    void setPos(QPointF& position);
    void setPos(qreal x, qreal y);
    void setSpawnDelay(int frames);
    void attachToItem(QPointer<Item> item);
    void start();
    void stop();
    void setLooping(bool value);
    bool isLoopFinished();
    bool isLoopingEnabled();
    void moveEveryFrame(QPoint& move);
    QPointer<ItemsModifier> getItemsModifier();

private:
    void advance(int step);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){}
    QPointF calculateRelativePos(QPointer<Item> particle);
    QList<QPointer<Item> > particles;
    QPointer<ItemsModifier> itemsModifier;
    int particlesCount;
    QPointF position;
    int radius;
    int spawnDelay;
    int lastUpdatedParticle;
    bool shallLoop;
    bool loopFinished;
    QList<QPointer<Item> > finishedParticles;
    QPointer<Item> attachedItem;
};

#endif // PARTICLES_H
