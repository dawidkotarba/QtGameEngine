#include "ship.h"

Ship::Ship():
    Item(Asset(PATH_ENEMY_SHIP, 28)),
    itemEffect(NULL),
    hasFired(false){
    setDestroyable(true);
    setEnemy(true);
    setHealth(ENEMY_SHIP_HEALTH);
    posYOffset = Utils::getInstance().randInt(-5, 5);
    getAnimationProcessor()->setLooping(true);
    initParticles();
}

Ship::~Ship(){
    clear_qptr(explosion);
}

void Ship::move(){
    qreal x = this->x() - ENEMY_SHIP_SPEED;
    qreal y = this->y();

    if (x < SceneUtils::getInstance().getTranslatedWidth(50)){
        y+=posYOffset;
        x-=2;

        if (itemEffect == NULL){
            itemEffect = new ItemEffect(this, ItemEffectType(ROTATE), 5);
            addEffect(*itemEffect);
        }
    }

    setPos(x,y);
}

void Ship::action(){
    if (!hasFired && x() < SceneUtils::getInstance().getTranslatedWidth(60)){
        QPointer<EnemyRocket> rocket = new EnemyRocket(this);
        rocket->start();
        hasFired = true;
    }
}

void Ship::die(){
    explosion = new ParticleExplosion(this, ENEMY_SHIP_PARTICLES_OFFSET);
    particles->setLooping(false);
    Item::die();
    playSound("bomb");
}

void Ship::initParticles(){
    particles = new ParticlesProcessor(Asset(PATH_STEAM), 10, this);
    particles->getItemsModifier()->setOffset(20, -30);
    particles->getItemsModifier()->setDefaultScale(0.2);
    particles->getItemsModifier()->applyRotateEffect(5, 5, true);
    particles->getItemsModifier()->applyFadeEffect(0.04, 0.05);
    particles->getItemsModifier()->applyScaleEffect(0.04, 0.05);
    particles->setRadius(3);
    particles->setSpawnDelay(7);
    particles->start();
}
