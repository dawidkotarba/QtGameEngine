#include "item.h"

Item::Item():
    itemId(CODE_NOT_INITIALIZED),
    addedToScene(false),
    currentImage(NULL),
    animationProcessor(NULL),
    monitor(0),
    initPos(ITEM_ZERO_POS),
    moveOffset(ITEM_ZERO_POS),
    destroyable(false),
    health(ITEM_MAX_HEALTH),
    acceleration(0),
    speed(ITEM_ZERO_POS),
    shallRemoveWhenOut(false),
    offsetX(0),
    blinks(false),
    blinkMinFrequency(0),
    blinkMaxFrequency(0),
    offsetY(0),
    repeatable(false),
    forcePaint(false),
    defaultScale(1),
    defaultOpacity(1),
    defaultRotation(0),
    enemy(false),
    markedAsForDelete(false),
    started(false){
    setPos(ITEM_ZERO_POS);
    MemoryManager::getInstance().addToItemsList(this);
    SceneUtils::getInstance().addToScene(this);
}

Item::Item(const QString& sourceFolder, const QString& imgPattern, int imgCount):
    Item(){
    animationProcessor = new AnimationProcessor(sourceFolder, imgPattern, imgCount);
    qDebug() <<  "Item of " + sourceFolder + STRING_SLASH + imgPattern + "loaded.";
}

Item::Item(const QString& sourceFolder, const QString& imgPattern, int imgCount, QPoint& position)
    : Item(sourceFolder, imgPattern, imgCount){
    setPos(position);
    setInitPos(position);
}

Item::~Item(){
    clear_qptr(animationProcessor);
}

void Item::start(){
    started = true;
}

void Item::stop(){
    started = false;
    SceneUtils::getInstance().removeFromScene(this);
    markAsForDelete();
}

void Item::setStarted(bool value){
    started = value;
}

bool Item::isStarted(){
    return started;
}

void Item::moveEveryFrame(QPointF& point){
    moveOffset = point;
}

QPointer<AnimationProcessor> Item::getAnimationProcessor(){
    return animationProcessor;
}

QPoint Item::calculateTransformOriginPoint(){
    qreal pX = x() + boundingRect().height() /2;
    qreal pY = y()+ + boundingRect().width() /2;
    return QPoint(pX, pY);
}

void Item::move(){
    moveBy(speed.x(), speed.y());
}

void Item::removeWhenOut(){
    if (SceneUtils::getInstance().isOutOfScene(this)){
        stop();
        SceneUtils::getInstance().removeFromScene(this);
    }
}

void Item::die(){
    health = ITEM_HEALTH_NOT_INIT;
    stop();
}

void Item::advance(int step){

    if (!step || !started)
        return;

    if (shallRemoveWhenOut && !repeatable)
        removeWhenOut();

    if (repeatable)
        repeat();

    if(health != ITEM_HEALTH_NOT_INIT && health <= 0)
        die();

    setTransformOriginPoint(calculateTransformOriginPoint());

    move();
    moveBy(moveOffset.x(), moveOffset.y());

    foreach(ItemEffect effect, transformationEffects)
        effect.apply();

    action();

    if (animationProcessor->isAnimated() && !SceneUtils::getInstance().isOutOfScene(this))
        update();

    qDebug() <<  "Position for item " << itemId << ": " << x() << ", " << y();
}

void Item::repeat(){
    if (!currentImage.isNull() && x() < -(currentImage->width()))
        setPos(initPos.x() + SceneUtils::getInstance().getSceneWidth(), initPos.y());
}

void Item::addEffect(ItemEffect& effect){

    if (effect.getEffectType() == ItemEffectType(LIGHT)){
        lightEffect.clear();
        lightEffect.append(effect);
    }
    else
        transformationEffects.append(effect);
}

bool Item::setLightEffectColor(QColor &color){
    if (!lightEffect.isEmpty() && color.isValid()){
        ItemEffect modifiedLightEffect = lightEffect.at(0);
        modifiedLightEffect.setLightEffectColor(color);
        lightEffect.clear();
        lightEffect.append(modifiedLightEffect);
        return true;
    }
    return false;
}

void Item::removeEffect(ItemEffectType& effectType){

    for (int i=0; i<transformationEffects.size(); i++){

        ItemEffect effect = transformationEffects.at(i);

        if (effect.getEffectType() == effectType)
            transformationEffects.removeAt(i);
    }
}

void Item::setDestroyable(bool value){
    destroyable = value;
}

bool Item::isDestroyable(){
    return destroyable;
}

void Item::makeMonitor(){
    setItemId(ItemIds(MONITORING_ITEM));
    monitor = true;
}

QRectF Item::boundingRect() const {
    if (animationProcessor)
        return QRectF(x(),y(),animationProcessor->getSize().width(), animationProcessor->getSize().height());

    return ITEM_ZERO_SQUARE;
}

QPainterPath Item::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Item::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {

    if (painterPtr == NULL)
        painterPtr = painter;

    if (blinks){
        int blinkFrame = Utils::getInstance().randInt(blinkMinFrequency, blinkMaxFrequency);
        if (blinkFrame > 0 && TimerUtils::getInstance().countEachFrame(blinkFrame))
            return;
    }

    if (!monitor && !SceneUtils::getInstance().isOutOfScene(this) || forcePaint){

        if (!animationProcessor->isLoopingEnabled() && animationProcessor->isLoopFinished())
            return;

        currentImage = animationProcessor->provideCurrentImage();

        if (!currentImage.isNull()){
            qDebug() << "Painting " << itemId << " for frame " << TimerUtils::getInstance().getFrameCount();

            // do not hide objects when they are larger than scene size
            if (!forcePaint && currentImage->width() >= SceneUtils::getInstance().getSceneWidth())
                forcePaint = true;

            painter->drawImage(pos(), *currentImage);

            if (!lightEffect.isEmpty()){
                ItemEffect lightEff = lightEffect.at(0);
                lightEff.apply(painter);
            }
        }
        else
            qWarning() << "Cannot paint img of item " << itemId;
    }
}

QList<QPointer<Item> > Item::getCollidingItems(){
    QList<QGraphicsItem *> collisions = collidingItems();

    QList<QPointer<Item> > items;

    if (!collisions.empty())
        foreach (QGraphicsItem* collision, collisions) {
            if (collision){
                Item* item = static_cast<Item*>(collision);
                items.append(item);
            }
        }
    return items;
}

void Item::setPercentPosition(QPoint& position){
    setPos(SceneUtils::getInstance().getTranslatedPosition(position));
}

void Item::setItemId(int id){
    itemId = id;
}

int Item::getItemId(){
    return itemId;
}

bool Item::collidesWithItemType(int itemId){
    QList<QPointer<Item> > collisions = getCollidingItems();

    if (!collisions.empty())
        foreach (QPointer<Item> collision, collisions)
            if (collision->getItemId() == itemId)
                return true;

    return false;
}

void Item::shallBlink(bool value, int minFrequency, int maxFrequency){
    blinkMinFrequency = minFrequency;
    blinkMaxFrequency = maxFrequency;
    blinks = value;
}

void Item::setHealth(int value){
    health = value;
}

void Item::increaseHealth(int value){
    health+=value;
}

void Item::decreaseHealth(int value){
    health-=value;
}

bool Item::isDead(){
    return health <= 0;
}

void Item::setSpeed(QPoint& speed){
    this->speed = speed;
}

QPoint& Item::getSpeed(){
    return speed;
}

void Item::addSpeed(QPoint& speed){
    this->speed+=speed;
}

int Item::getAcceleration(){
    return acceleration;
}

void Item::setAcceleration(int acceleration){
    this->acceleration = acceleration;
}

void Item::playSound(const QString& fileName, int volume){
    SoundUtils::getInstance().playSound(fileName, volume);
}

void Item::setOffset(qreal x, qreal y){
    setOffsetX(x);
    setOffsetY(y);
}

void Item::setOffsetX(qreal value){
    offsetX = value;
    setPos(x() + offsetX, y());
}

void Item::setOffsetY(qreal value){
    offsetY = value;
    setPos(x(), y() + offsetY);
}

qreal Item::getOffset(){
    return offsetX;
}

qreal Item::getOffsetY(){
    return offsetY;
}

void Item::setRepeatable(bool value){
    repeatable = value;
}

void Item::setInitPos(QPoint& value){
    initPos = value;
}

void Item::setRemoveWhenOut(bool value){
    shallRemoveWhenOut = value;
}

bool Item::isMarkedAsForDelete(){
    return markedAsForDelete;
}

void Item::markAsForDelete(){
    markedAsForDelete = true;
}

void Item::setAddedToScene(bool value){
    addedToScene = value;
}

bool Item::isAddedToScene(){
    return addedToScene;
}

void Item::addToScene(){
    SceneUtils::getInstance().addToScene(this);
    addedToScene = true;
}

void Item::removeFromScene(){
    SceneUtils::getInstance().removeFromScene(this);
    addedToScene = false;
}

bool Item::isOutOfScene(){
    return SceneUtils::getInstance().isOutOfScene(this);
}

void Item::setEnemy(bool value){
    enemy = value;
}

bool Item::isEnemy(){
    return enemy;
}

void Item::resetTransforationState(){
    setOpacity(defaultOpacity);
    setScale(defaultScale);
    setRotation(defaultRotation);
}

void Item::setDefaultScale(qreal defaultScale){
    this->defaultScale = defaultScale;
    setScale(defaultScale);
}

void Item::setDefaultOpacity(qreal defaultOpacity){
    this->defaultOpacity = defaultOpacity;
    setOpacity(defaultOpacity);
}

void Item::setDefaultRotation(qreal defaultRotation){
    this->defaultRotation = defaultRotation;
    setRotation(defaultRotation);
}

qreal Item::getDefaultScale(){
    return defaultScale;
}

qreal Item::getDefaultOpacity(){
    return defaultOpacity;
}

qreal Item::getDefaultRotation(){
    return defaultRotation;
}
