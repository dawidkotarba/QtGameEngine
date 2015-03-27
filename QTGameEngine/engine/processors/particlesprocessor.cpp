#include "particlesprocessor.h"

ParticlesProcessor::ParticlesProcessor(Asset asset, int count):
    particlesCount(count),
    position(ITEM_ZERO_POS),
    radius(0),
    attachedItem(NULL),
    lastUpdatedParticle(CODE_NOT_INITIALIZED),
    spawnDelay(1),
    shallLoop(true){

    for (int particlesCount = 0; particlesCount<count; particlesCount++){
        QPointer<Item> particle = new Item(asset);
        particle->setItemId(IND_PARTICLE);
        particles.append(particle);
    }

    itemsModifier = new ItemsModifier(particles);
}

ParticlesProcessor::ParticlesProcessor(Asset asset, int count, QPointer<Item> owner):
    ParticlesProcessor(asset, count)
{
    attachedItem = owner;
    position = owner->pos();

    ItemUtils::getInstance().setPos(particles, position);
}

ParticlesProcessor::~ParticlesProcessor(){
    clear_qptr_list(particles);
    clear_qptr(itemsModifier);
}

void ParticlesProcessor::start(){
    Item::start();
    ItemUtils::getInstance().setVisible(particles, false);
    ItemUtils::getInstance().setStarted(particles, true);
}

void ParticlesProcessor::stop(){
    Item::stop();
    ItemUtils::getInstance().stop(particles);
}

void ParticlesProcessor::advance(int step){

    if (started){

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
            particle->resetTransformation();

            position = calculateRelativePos(particle);
            particle->setPos(position);

            int xBias = Utils::getInstance().randInt(-radius,radius);
            int yBias = Utils::getInstance().randInt(-radius,radius);
            particle->moveBy(xBias, yBias);
            particle->show();

            if (!shallLoop)
                finishedParticles.append(particle);
        }
    }
}

QPointF ParticlesProcessor::calculateRelativePos(QPointer<Item> particle){
    if (attachedItem){
        qreal posX = attachedItem->x() + particle->getBiasX();
        qreal posY = attachedItem->y() + particle->getBiasY();
        position = QPointF(posX, posY);
    }

    return position;
}

void ParticlesProcessor::attachToItem(QPointer<Item> item){
    attachedItem = item;
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
