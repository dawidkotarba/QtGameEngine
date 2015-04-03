#ifndef UFO2_H
#define UFO2_H
#include "engine/items/item.h"
#include "game/constants.h"
#include "game/resources.h"
#include "game/particles/particleexplosion.h"

class Ufo2: public Item {
public:
    Ufo2();
    virtual ~Ufo2();

private:
    QPointer<ParticleExplosion> particleExplosion;
    void die();
    void move();

};
#endif // UFO2_H
