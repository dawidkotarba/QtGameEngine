#include "weapon.h"

Weapon::Weapon(QPointer<Item> owner, Asset itemAsset, QPoint speed):
    Item(itemAsset, owner->pos()),
    owner(owner),
    damage(WEAPON_DEFAULT_DAMAGE){
    setRemoveWhenOut(true);
    setSpeed(speed);
    setPos(owner->pos());
    animationProcessor->setLooping(true);
}


Weapon::Weapon(QPointer<Item> owner, Asset itemAsset, Asset particlesAsset, int particlesCount, QPoint speed):
    Weapon(owner, itemAsset, speed){
    particles = new ParticlesProcessor(particlesAsset, particlesCount, this);
}

Weapon::~Weapon(){
    clear_qptr(particles);
    clear_qptr(explParticles);
    clear_qptr(explosion);

}

void Weapon::start(){
    Item::start();

    if (particles)
        particles->start();
}

void Weapon::action(){

    if (pos().x() > SceneUtils::getInstance().getTranslatedWidth(100))
        return;

    QList<QPointer<Item> > collisions = getCollidingItems();

    if (!collisions.isEmpty())
    foreach (QPointer<Item> col, collisions)
        if (col->isDestroyable() && !col->isOutOfScene()){
            col->decreaseHealth(damage);
            die();
            return;
        }
}

void Weapon::die(){

    explParticles = new ParticlesProcessor(Asset(PATH_YELLOW_C), 1, this);
    explParticles->getItemsModifier()->rotate(20,30,true);
    explParticles->getItemsModifier()->setInitialScale(1);
    explParticles->getItemsModifier()->scale(0.01, 0.05);
    explParticles->getItemsModifier()->fadeAway(0.03, 0.05);
    explParticles->setLooping(false);
    explParticles->setRadius(0);
    explParticles->start();

    Item::die();

    if (particles)
        particles->stop();
}
