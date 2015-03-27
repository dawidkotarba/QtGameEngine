#include "ufo.h"

Ufo::Ufo():
    Item(Asset(PATH_UFO_BLUE)){
    setDestroyable(true);
    setEnemy(true);
}

Ufo::~Ufo(){
    clear_qptr(particleExplosion);
}

void Ufo::move(){
    qreal x = pos().x() - ENEMY_UFO_SPEED;
    qreal y = 0;

    if (ENEMY_UFO_SIN_FACTOR != 0)
        y = (sin(x/ENEMY_UFO_SIN_FACTOR)*ENEMY_UFO_SIN_FACTOR) + initPos.y();

    setPos(x,y);
}

void Ufo::die(){    

    particleExplosion = new ParticleExplosion(this, PATH_FIREBALL, PATH_FIREBALL3, ENEMY_UFO_PARTICLES_BIAS);
    Item::die();
    playSound("chamb");
}
