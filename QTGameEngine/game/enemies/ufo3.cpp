#include "ufo3.h"

Ufo3::Ufo3():
    Item(Asset(PATH_UFO_GREEN)),
    speed(ENEMY_UFO3_SPEED,0){
    setDestroyable(true);
    setEnemy(true);
    int y = Utils::getInstance().randInt(10, 90);
    pos().setY(SceneUtils::getInstance().getTranslatedWidth(y));
    setSpeed(speed);

    ItemEffect effect(this, ItemEffectType(ROTATE), 10);
    addEffect(effect);
}

Ufo3::~Ufo3(){
    clear_qptr(particleExplosion);
}

void Ufo3::die(){

    particleExplosion = new ParticleExplosion(this, PATH_FIREBALL, PATH_FIREBALL4, ENEMY_UFO_PARTICLES_BIAS);
    Item::die();
    playSound("chamb");
}
