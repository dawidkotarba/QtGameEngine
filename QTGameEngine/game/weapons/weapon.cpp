#include "weapon.h"

Weapon::Weapon(QPointer<Item> owner, Asset itemAsset, QPoint speed):
    Item(itemAsset, owner->pos()),
    owner(owner),
    damage(WEAPON_DEFAULT_DAMAGE){
    setRemoveWhenOut(true);
    setSpeed(speed);
    setPos(owner->pos());
    animationProcessor->setLooping(true);

    ItemEffect lightEffect(this, ItemEffectType(LIGHT), 50);
    addEffect(lightEffect);

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

    if (x() > SceneUtils::getInstance().getTranslatedWidth(100))
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

    explParticles = new ParticlesProcessor(Asset(PATH_YELLOW_C), 3, this);
    explParticles->getItemsModifier()->applyRotateEffect(20,30,true);
    explParticles->getItemsModifier()->setDefaultScale(0.1);
    explParticles->getItemsModifier()->applyScaleEffect(0.01, 0.05);
    explParticles->getItemsModifier()->applyFadeEffect(0.03, 0.05);
    explParticles->setLooping(false);
    explParticles->setRadius(30);
    explParticles->getItemsModifier()->addLightEffect(300, 50, 50);
    explParticles->start();

    Item::die();

    if (particles)
        particles->stop();
}
