#ifndef UFO_H
#define UFO_H
#include "engine/items/item.h"
#include "game/constants.h"
#include "game/resources.h"
#include "game/particles/particleexplosion.h"

class Ufo: public Item
{
public:
    Ufo();
    virtual ~Ufo();

private:
    QPointer<ParticleExplosion> particleExplosion;
    void die();
    void move();

};

#endif // UFO_H
