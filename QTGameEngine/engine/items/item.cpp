#include "item.h"

Item::Item():
    itemId(CODE_NOT_INITIALIZED),
    addedToScene(false),
    currentImage(NULL),
    animationProcessor(NULL),
    monitor(0),
    initPos(ITEM_ZERO_POS),
    moveBias(ITEM_ZERO_POS),
    destroyable(false),
    health(ITEM_MAX_HEALTH),
    acceleration(0),
    shallCalculateTransformOP(false),
    speed(ITEM_ZERO_POS),
    initialScale(1),
    initialOpacity(1),
    shallRemoveWhenOut(false),
    biasX(0),
    blinks(false),
    blinkMinFrequency(0),
    blinkMaxFrequency(0),
    biasY(0),
    repeatable(false),
    forcePaint(false),
    boundingRectHeightDivider(1),
    boundingRectWidthDivider(1),
    boundingRectWidthBias(0),
    boundingRectHeightBias(0),
    enemy(false),
    markedAsForDelete(false),
    started(false),
    lightEffect(NULL){
    setPos(ITEM_ZERO_POS);
    resetTransformation();
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
    show();
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
    moveBias = point;
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
    moveBy(moveBias.x(), moveBias.y());

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

void Item::setInitialScale(qreal scale){
    initialScale = scale;
}

void Item::setInitialOpacity(qreal opacity){
    initialOpacity = opacity;
}

void Item::addEffect(ItemEffect& effect){
    transformationEffects.append(effect);
}

void Item::resetTransformation(){
    resetTransform();
    resetRotation();
    resetOpacity();
    resetScale();

    setRotation(currentRotationAngle);
    setOpacity(currentOpacity);
    setScale(currentScale);

    show();
}

void Item::resetRotation(){
    currentRotationAngle = 0;
}

void Item::resetOpacity(){
    currentOpacity = initialOpacity;
}

void Item::resetScale(){
    if (itemId == IND_PARTICLE)
        currentScale = 1e-100;
    else currentScale = initialScale;
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
        return QRectF(pos().x(),pos().y(),animationProcessor->getSize().width()/boundingRectWidthDivider+boundingRectWidthBias,
                      animationProcessor->getSize().height()/boundingRectHeightDivider+boundingRectHeightBias);

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

            if (lightEffect != NULL)
                lightEffect->apply(painter);

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

QPoint Item::getSpeed(){
    return speed;
}

void Item::setAcceleration(int acceleration){
    this->acceleration = acceleration;
}

void Item::playSound(const QString& fileName, int volume){
    SoundUtils::getInstance().playSound(fileName, volume);
}

void Item::setBias(qreal x, qreal y){
    setBiasX(x);
    setBiasY(y);
}

void Item::setBiasX(qreal value){
    biasX = value;
    setPos(x() + biasX, y());
}

void Item::setBiasY(qreal value){
    biasY = value;
    setPos(x(), y() + biasY);
}

qreal Item::getBiasX(){
    return biasX;
}

qreal Item::getBiasY(){
    return biasY;
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

void Item::setBoundingRectDividers(qreal width, qreal height){
    boundingRectWidthDivider = width;
    boundingRectHeightDivider = height;
}

void Item::setBoundingRectBias(int width, int height){
    boundingRectWidthBias = width;
    boundingRectHeightBias = height;
}

void Item::addLightEffect(int radius, int biasX, int biasY){
    lightEffect = new ItemEffect(this, ItemEffectType(LIGHT), radius);
    lightEffect->setBias(biasX, biasY);
}

int Item::getCurrentRotationAngle(){
    return currentRotationAngle;
}

qreal Item::getCurrentOpacity(){
    return currentOpacity;
}

qreal Item::getCurrentScale(){
    return currentScale;
}

qreal Item::getInitialOpacity(){
    return initialOpacity;
}

qreal Item::getInitialScale(){
    return initialScale;
}

void Item::setCurrentRotationAngle(int currentRotationAngle){
    this->currentRotationAngle = currentRotationAngle;
}

void Item::setCurrentOpacity(qreal currentOpacity){
    this->currentOpacity = currentOpacity;
}

void Item::setCurrentScale(qreal currentScale){
    this->currentScale = currentScale;
}

bool Item::getShallCalculateTransformOP(){
    return shallCalculateTransformOP;
}

void Item::setShallCalculateTransformOP(bool shallCalculateTransformOP){
    this->shallCalculateTransformOP = shallCalculateTransformOP;
}
