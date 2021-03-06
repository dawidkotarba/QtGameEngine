#include "particlesprocessor.h"

ParticlesProcessor::ParticlesProcessor(Asset asset, int count):
    particlesCount(count),
    position(ITEM_ZERO_POS),
    radius(0),
    owner(NULL),
    lastUpdatedParticle(CODE_NOT_INITIALIZED),
    spawnDelay(1),
    shallLoop(true){

    for (int particlesCount = 0; particlesCount<count; particlesCount++){
        QPointer<Item> particle = new Item(asset);
        particle->setItemId(PARTICLE);
        particles.append(particle);
    }

    itemsModifier = new ItemsModifier(particles);
}

ParticlesProcessor::ParticlesProcessor(Asset asset, int count, QPointer<Item> owner):
    ParticlesProcessor(asset, count){
    this->owner = owner;
}

ParticlesProcessor::~ParticlesProcessor(){
    clear_qptr_list(particles);
    clear_qptr(itemsModifier);
}

void ParticlesProcessor::start(){
    ItemUtils::getInstance().setVisible(particles, false);
}

void ParticlesProcessor::stop(){
    ItemUtils::getInstance().stop(particles);
}

void ParticlesProcessor::advance(int step){

    if (!TimerUtils::getInstance().countEachFrame(spawnDelay))
        return;

    if (!shallLoop){
        for (int partNo = 0; partNo<finishedParticles.size(); partNo++){

            QPointer<Item> finPart = finishedParticles.at(partNo);

            if (finPart && !finPart->isVisible()){
                finPart->stop();
                finishedParticles.removeOne(finPart);
                particles.removeOne(finPart);
            }
        }
    }

    if (++lastUpdatedParticle >= particles.size())
        lastUpdatedParticle = 0;

    QPointer<Item> particle;

    if (!particles.isEmpty())
        particle = particles.at(lastUpdatedParticle);

    if (particle && !particle->isVisible()){
        particle->resetTransforationState();
        particle->setScale(PARTICLE_MIN_SCALE);
        position = calculateRelativePos(particle);
        particle->setPos(position);

        if (radius > 0){
            int radiusOffset = Utils::getInstance().randInt(-radius,radius);
            particle->moveBy(radiusOffset, radiusOffset);
        }

        particle->setStarted(true);
        particle->show();

        if (!shallLoop)
            finishedParticles.append(particle);
    }
}

QPointF ParticlesProcessor::calculateRelativePos(QPointer<Item> particle){
    if (owner){
        qreal posX = owner->x() + particle->getOffset();
        qreal posY = owner->y() + particle->getOffsetY();
        position = QPointF(posX, posY);
    }

    return position;
}

void ParticlesProcessor::setRadius(int radius){
    this->radius = radius;
}

void ParticlesProcessor::setPos(QPointF& position){
    this->position = position;
}

void ParticlesProcessor::setPos(qreal x, qreal y){
    position = QPointF(x,y);
}

void ParticlesProcessor::setSpawnDelay(int frames){
    spawnDelay = frames;
}

void ParticlesProcessor::setLooping(bool value){
    shallLoop = value;
}

bool ParticlesProcessor::isLoopFinished(){
    return loopFinished;
}

bool ParticlesProcessor::isLoopingEnabled(){
    return shallLoop;
}

QPointer<ItemsModifier> ParticlesProcessor::getItemsModifier(){
    return itemsModifier;
}
