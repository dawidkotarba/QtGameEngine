#include "fighter.h"

Fighter::Fighter():
    Item(Asset(PATH_FIGHTER), FIGHTER_INIT_POSITION),
    isGoingLeft(false),
    isGoingRight(false),
    isGoingUp(false),
    isGoingDown(false),
    currentWeapon(WeaponsEnum(BULLET)),
    fireRate(0){
    animationProcessor->shallRandomPictures(true);
    itemId = FIGHTER_ID;
    controlId = FIGHTER_CONTROL_ID;
    acceleration = FIGHTER_ACCELERATION;
    speed = FIGHTER_SPEED;
    stoppedImage = new Image(PATH_FIGHTER_STOPPED);
    initParticles();
}

Fighter::~Fighter(){
    clear_qptr(particles);
    clear_qptr(stoppedImage);
}

void Fighter::testArea(){
}

void Fighter::initParticles(){
    particles = new ParticlesProcessor(Asset(PATH_STEAM_S), 30, this);
    particles->getItemsModifier()->setBias(FIGHTER_PARTICLES_BIAS_X, FIGHTER_PARTICLES_BIAS_Y);
    particles->getItemsModifier()->setInitialScale(0.1);
    particles->getItemsModifier()->rotate(2, 20, true);
    particles->getItemsModifier()->fadeAway(0.04, 0.05);
    particles->getItemsModifier()->scale(0.04, 0.09);
    particles->setRadius(3);
    particles->setSpawnDelay(2);
    particles->start();
}

void Fighter::move(){
    if (isGoingLeft && x() > 0)
        go(DirectionsEnum(LEFT));
    else if (isGoingRight && x() <= SceneUtils::getInstance().getTranslatedWidth(100))
        go(DirectionsEnum(RIGHT));

    if (isGoingUp && y() > 0)
        go(DirectionsEnum(UP));
    else if (isGoingDown && y() <= SceneUtils::getInstance().getTranslatedHeight(100))
        go(DirectionsEnum(DOWN));
}

bool Fighter::isMoving(){
    return isGoingLeft || isGoingRight || isGoingUp || isGoingDown;
}

void Fighter::action(){

    if (isDead() && isVisible()){
        fadeAway(0.02);
        rotate(10);
        scale(-0.01);
    }
    else if (currentOpacity <= 0){
        setPos(QPoint(0,0));
        resetTransformation();
        health = 100;
        particles->start();
    }

    QList<QPointer<Item> > collisions = getCollidingItems();

    if (!collisions.isEmpty())
    foreach (QPointer<Item> col, collisions)
        if (col->isDestroyable()){
            decreaseHealth(100);
            col->decreaseHealth(100);
            die();
            playSound("bomb2");
            return;
        }

    fire();
}

void Fighter::go(DirectionsEnum direction){

    switch(direction){
    case UP:
        moveBy(0, -acceleration);
        break;
    case DOWN:
        moveBy(0, acceleration);
        break;
    case LEFT:
        moveBy(-acceleration, 0);
        break;
    case RIGHT:
        moveBy(acceleration, 0);
        break;
    }
}

void Fighter::controlKeyPress(QKeyEvent* event){

    if (!isDead()){

        switch(event->key()){
        case Qt::Key_Up:
            isGoingUp = true;
            isGoingDown = false;
            break;
        case Qt::Key_Left:
            isGoingLeft = true;
            isGoingRight = false;
            break;
        case Qt::Key_Right:
            isGoingRight = true;
            isGoingLeft = false;
            break;
        case Qt::Key_Down:
            isGoingDown = true;
            isGoingUp = false;
            break;
        case Qt::Key_Shift:           
            currentWeapon = WeaponsEnum(ROCKET);
            fireRate = WEAPON_ROCKET_FIRE_RATE;
            break;
        case Qt::Key_Space:
            currentWeapon = WeaponsEnum(BULLET);
            fireRate = WEAPON_BULLET_FIRE_RATE;
            break;
        }
    }
}

void Fighter::controlKeyRelease(QKeyEvent* event){

    if (event->isAutoRepeat()){
        event->ignore();
        return;
    }

    if (!isDead()){

        switch(event->key()){
        case Qt::Key_Up:
            isGoingUp = false;
            break;
        case Qt::Key_Left:
            isGoingLeft = false;
            break;
        case Qt::Key_Right:
            isGoingRight = false;
            break;
        case Qt::Key_Down:
            isGoingDown = false;
            break;
        case Qt::Key_Shift:
            fireRate = 0;
            break;
        case Qt::Key_Space:
            fireRate = 0;
            break;
        }

        event->accept();
    }
}

void Fighter::fire(){

    if (fireRate && TimerUtils::getInstance().countEachFrame(fireRate)){

        QPointer<Weapon> weapon;

        switch(currentWeapon){
            case BULLET:
                weapon = new Bullet(this);
                break;
             case ROCKET:
                weapon = new Rocket(this);
                break;
        }
        if (weapon)
            weapon->start();
    }
}

void Fighter::die(){
    stop();
}

void Fighter::stop(){
    isGoingDown = false;
    isGoingUp = false;
    isGoingRight = false;
    isGoingLeft = false;
}

void Fighter::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    if (isMoving())
        Item::paint(painter, option, widget);
    else
        painter->drawImage(pos(), *stoppedImage);
}

