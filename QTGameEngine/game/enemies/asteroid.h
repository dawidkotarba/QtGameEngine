#ifndef ASTEROID_H
#define ASTEROID_H
#include "engine/items/item.h"
#include "game/constants.h"
#include "game/resources.h"
#include "game/particles/particleexplosiondust.h"

class Asteroid: public Item {
public:
    Asteroid();
    Asteroid(const QString& imgPath, QPointF position);
    virtual ~Asteroid();

private:
    QPointer<ParticleExplosionDust> explosion;
    QPointer<ParticlesProcessor> dustPuff;
    void die();
    void spawnChildren(int countPerSize);
    bool isChildren;
    QList<QPointer<Asteroid> > children;
};


#endif // ASTEROID_H
