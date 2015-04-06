#ifndef UFO3_H
#define UFO3_H
#include "engine/items/item.h"
#include "game/constants.h"
#include "game/resources.h"
#include "game/particles/particleexplosion.h"

class Ufo3: public Item {
public:
    Ufo3();
    virtual ~Ufo3();

private:
    QPointer<ParticleExplosion> particleExplosion;
    void die();
    QColor explosionColor;
    QPoint speed;    

};

#endif // UFO3_H
