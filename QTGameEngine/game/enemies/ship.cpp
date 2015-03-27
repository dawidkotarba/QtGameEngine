#include "ship.h"

Ship::Ship():
    Item(Asset(PATH_ENEMY_SHIP, 28)),
    hasFired(false){
    setDestroyable(true);
    setEnemy(true);
    setHealth(ENEMY_SHIP_HEALTH);
    posYBias = Utils::getInstance().randInt(-5, 5);
    getAnimationProcessor()->setLooping(true);
    initParticles();
}

Ship::~Ship(){
    clear_qptr(explosion);
}

void Ship::move(){
    qreal x = pos().x() - ENEMY_SHIP_SPEED;
    qreal y = pos().y();

    if (x < SceneUtils::getInstance().getTranslatedWidth(50)){
        y+=posYBias;
        x-=2;
        rotate(5);
    }

    setPos(x,y);
}

void Ship::action(){
    if (!hasFired && pos().x() < SceneUtils::getInstance().getTranslatedWidth(60)){
        QPointer<EnemyRocket> rocket = new EnemyRocket(this);
        rocket->start();
        hasFired = true;
    }
}

void Ship::die(){
    explosion = new ParticleExplosion(this, ENEMY_SHIP_PARTICLES_BIAS);
    particles->setLooping(false);
    Item::die();
    playSound("bomb");
}

void Ship::initParticles(){
    particles = new ParticlesProcessor(Asset(PATH_STEAM), 10, this);
    particles->getItemsModifier()->setBias(20, -30);
    particles->getItemsModifier()->setInitialScale(0.2);
    particles->getItemsModifier()->rotate(5, 5, true);
    particles->getItemsModifier()->fadeAway(0.04, 0.05);
    particles->getItemsModifier()->scale(0.04, 0.05);
    particles->setRadius(3);
    particles->setSpawnDelay(7);
    particles->start();
}
