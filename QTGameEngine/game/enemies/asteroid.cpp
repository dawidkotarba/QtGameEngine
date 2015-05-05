#include "asteroid.h"

Asteroid::Asteroid():
    Item(Asset(PATH_ASTEROID128)),
    isChildren(false){
    setDestroyable(true);
    setHealth(ENEMY_ASTEROID_HEALTH);
    QPoint speed(ENEMY_ASTEROID_SPEED, 0);
    setSpeed(speed);

    ItemEffect effect(this, ItemEffectType(ROTATE), ENEMY_ASTEROID_ROTATION);
    addEffect(effect);
}

Asteroid::Asteroid(const QString& imgPath, QPointF position):
    Item(Asset(imgPath)),
    isChildren(true){
    setDestroyable(true);
    setHealth(ENEMY_ASTEROID_CHILD_HEALTH);
    setPos(position);
    QPoint speed(ENEMY_ASTEROID_SPEED, 0);
    setSpeed(speed);

    ItemEffect effect(this, ItemEffectType(ROTATE), ENEMY_ASTEROID_CHILDREN_ROTATION);
    addEffect(effect);
}

Asteroid::~Asteroid(){
    clear_qptr(explosion);
}

void Asteroid::die(){
    QPointF dustMove(-1,0);
    dustPuff = new ParticlesProcessor(Asset(PATH_BROWN_DUST), 3, this);
    dustPuff->setRadius(15);
    dustPuff->getItemsModifier()->setOffset(-25,-25);
    dustPuff->getItemsModifier()->applyFadeEffect(0.03, 0.04);
    dustPuff->getItemsModifier()->applyScaleEffect(0.02, 0.03);
    dustPuff->getItemsModifier()->applyRotateEffect(1,5, true);
    dustPuff->getItemsModifier()->moveEveryFrame(dustMove);
    dustPuff->setLooping(false);
    dustPuff->start();

    explosion = new ParticleExplosionDust(this, 0);
    Item::die();

    if (!isChildren)
        spawnChildren(ENEMY_ASTEROID_CHILDREN_COUNT);
}

void Asteroid::spawnChildren(int countPerSize){

    for (int i=0; i<countPerSize; i++){
        children.append(new Asteroid(PATH_ASTEROID64, pos()));
        children.append(new Asteroid(PATH_ASTEROID32, pos()));
    }

    foreach (QPointer<Asteroid> child , children){
        child->setOffset(30,30);
        QPointF move(Utils::getInstance().randFloat(-3,3),Utils::getInstance().randFloat(-3,3));
        child->moveEveryFrame(move);
        child->start();
    }
}
