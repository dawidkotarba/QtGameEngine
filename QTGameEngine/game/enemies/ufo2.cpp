#include "ufo2.h"

Ufo2::Ufo2():
    Item(Asset(PATH_UFO_RED)),
    explosionColor(255,0,0){
    setDestroyable(true);
    setEnemy(true);
}

Ufo2::~Ufo2(){
    clear_qptr(particleExplosion);
}

void Ufo2::move(){
    qreal x = this->x() - ENEMY_UFO2_SPEED;
    qreal y = 0;

    if (ENEMY_UFO2_SIN_FACTOR != 0)
        y = (sin(x/ENEMY_UFO2_SIN_FACTOR)*ENEMY_UFO2_SIN_FACTOR) + initPos.y();

    setPos(x,y);
}

void Ufo2::die(){

    particleExplosion = new ParticleExplosion(this, PATH_FIREBALL, PATH_FIREBALL2, ENEMY_UFO_PARTICLES_OFFSET, explosionColor);
    Item::die();
    playSound("chamb");
}
