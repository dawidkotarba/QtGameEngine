#include "window.h"

Window::Window(QObject* parent){
    splash = new Splash();
    splash->show();
    qDebug() << "Loading main window.";

    // main window props
    if (USE_OPENGL)
        setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    else
        setViewport(new QWidget);

    if (USE_ANTYALIASING)
        setRenderHint(QPainter::Antialiasing);

    setBackgroundBrush(QBrush(BG_COLOR, Qt::CrossPattern));
    setCacheMode(QGraphicsView::CacheBackground);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setDragMode(QGraphicsView::NoDrag);

    // scene and actors
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    SceneUtils::getInstance().attachToScene(&scene);
    scene.setSceneRect(0, 0, SceneUtils::getInstance().getScreenWidth(), SceneUtils::getInstance().getScreenHeight());
    setScene(&scene);
    centerOn(0.0,0.0);
    monitorItem = new MonitorItem();

    initBackgroundEnvironment();
    initActors();
    initForegroundEnvironment();

    // timer props
    timer.start(WINDOW_TIMER_MSEC);
    connect(&timer, SIGNAL(timeout()), this, SLOT(MainClockTick()));
    qDebug() <<  "Main window loaded.";

    // show window
    showFullScreen();
    show();
    splash->close();
}

Window::~Window(){
    clear_qptr(player);
    deleteActors();

    qDebug() << "Deleting monitoring item";
    clear_qptr(monitorItem);

    MemoryManager::getInstance().clearMemory();
}

void Window::MainClockTick(){
    scene.advance();
}

void Window::keyPressEvent(QKeyEvent* event){
    inputController.controlKeyPress(event);
}

void Window::keyReleaseEvent(QKeyEvent* event){
    inputController.controlKeyRelease(event);
}

void Window::initActors(){

    fighter = new Fighter();
    inputController.setControlableItem(fighter);
    fighter->start();

    enemiesAsteroid = new ItemSpawner<Asteroid>(30,500,SceneUtils::getInstance().getTranslatedWidth(25), QPoint(SceneUtils::getInstance().getTranslatedWidth(50),SceneUtils::getInstance().getTranslatedHeight(50)));
    enemiesAsteroid->start();

    enemiesUfo = new ItemSpawner<Ufo>(30,500,SceneUtils::getInstance().getTranslatedWidth(25), QPoint(SceneUtils::getInstance().getTranslatedWidth(50),SceneUtils::getInstance().getTranslatedHeight(50)));
    enemiesUfo->start();

    enemiesUfo2 = new ItemSpawner<Ufo2>(30,700,SceneUtils::getInstance().getTranslatedWidth(25), QPoint(SceneUtils::getInstance().getTranslatedWidth(50),SceneUtils::getInstance().getTranslatedHeight(50)));
    enemiesUfo2->start();

    enemiesUfo3 = new ItemSpawner<Ufo3>(30,900,SceneUtils::getInstance().getTranslatedWidth(25), QPoint(SceneUtils::getInstance().getTranslatedWidth(50),SceneUtils::getInstance().getTranslatedHeight(50)));
    enemiesUfo3->start();

    enemiesShip = new ItemSpawner<Ship>(30,1200,SceneUtils::getInstance().getTranslatedWidth(25), QPoint(SceneUtils::getInstance().getTranslatedWidth(50),SceneUtils::getInstance().getTranslatedHeight(50)));
    enemiesShip->start();
}

void Window::deleteActors(){
    qDebug() <<  "Deleting actors:";
    clear_qptr(fighter);
    clear_qptr(enemiesUfo);
    clear_qptr(enemiesUfo2);
    clear_qptr(enemiesUfo3);
    clear_qptr(enemiesShip);
    clear_qptr(enemiesAsteroid);
    qDebug() <<  "Actors deleted";
}

void Window::initBackgroundEnvironment(){

    // stars
    envStar16 = new ItemSpawner<Star16>(10, 100, 150, QPoint(SceneUtils::getInstance().getTranslatedWidth(0),SceneUtils::getInstance().getTranslatedHeight(30)));
    envStar16->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_02));
    envStar16->getItemsModifier()->setRepeatable(true);
    envStar16->getItemsModifier()->shallBlink(true, 10, 20);
    envStar16->start();

    envStar32 = new ItemSpawner<Star32>(10, 300, 150, QPoint(SceneUtils::getInstance().getTranslatedWidth(0),SceneUtils::getInstance().getTranslatedHeight(30)));
    envStar32->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_02));
    envStar32->getItemsModifier()->setRepeatable(true);
    envStar32->getItemsModifier()->shallBlink(true, 10, 20);
    envStar32->start();

    // moon
    envMoon = new ItemSpawner<Moon>(2, 1200, 0, QPoint(SceneUtils::getInstance().getTranslatedWidth(80),SceneUtils::getInstance().getTranslatedHeight(10)));
    envMoon->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_02));
    envMoon->getItemsModifier()->setRepeatable(true);
    envMoon->start();

    // clouds
    envCloud3 = new ItemSpawner<Cloud3>(10, 400, 200, QPoint(SceneUtils::getInstance().getTranslatedWidth(0),SceneUtils::getInstance().getTranslatedHeight(50)));
    envCloud3->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_03));
    envCloud3->getItemsModifier()->setRepeatable(true);
    envCloud3->start();

    envCloud2 = new ItemSpawner<Cloud2>(10, 400, 150, QPoint(SceneUtils::getInstance().getTranslatedWidth(0),SceneUtils::getInstance().getTranslatedHeight(60)));
    envCloud2->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_05));
    envCloud2->getItemsModifier()->setRepeatable(true);
    envCloud2->start();

    envCloud4 = new ItemSpawner<Cloud4>(10, 400, 150, QPoint(SceneUtils::getInstance().getTranslatedWidth(0),SceneUtils::getInstance().getTranslatedHeight(60)));
    envCloud4->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_1));
    envCloud4->getItemsModifier()->setRepeatable(true);
    envCloud4->start();

    envCloud = new ItemSpawner<Cloud>(10, 400, 150, QPoint(SceneUtils::getInstance().getTranslatedWidth(0),SceneUtils::getInstance().getTranslatedHeight(60)));
    envCloud->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_07));
    envCloud->getItemsModifier()->setRepeatable(true);
    envCloud->start();

    envCloud6 = new ItemSpawner<Cloud6>(10, 800, 200, QPoint(SceneUtils::getInstance().getTranslatedWidth(0),SceneUtils::getInstance().getTranslatedHeight(60)));
    envCloud6->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_2));
    envCloud6->getItemsModifier()->setRepeatable(true);
    envCloud6->start();
}

void Window::initForegroundEnvironment(){

    envCloud5 = new ItemSpawner<Cloud5>(10, 400, 200, QPoint(SceneUtils::getInstance().getTranslatedWidth(0),SceneUtils::getInstance().getTranslatedHeight(50)));
    envCloud5->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_3));
    envCloud5->getItemsModifier()->setRepeatable(true);
    envCloud5->start();
}

void Window::deleteEnvironment(){
    clear_qptr(envStar16);
    clear_qptr(envStar32);
    clear_qptr(envCloud);
    clear_qptr(envCloud2);
    clear_qptr(envCloud3);
    clear_qptr(envCloud4);
    clear_qptr(envCloud5);
    clear_qptr(envCloud6);
}
