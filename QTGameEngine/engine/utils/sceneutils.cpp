#include "sceneutils.h"

SceneUtils::SceneUtils():
    scene(NULL),
    sceneWidth(0),
    sceneHeight(0),
    percentFactor(0.47){}

bool SceneUtils::attachToScene(QGraphicsScene* scene){

    if ((this->scene = scene) == NULL){
        qDebug() << "Cannot attach SceneUtils to scene";
        return false;
    }

    return true;
}

int SceneUtils::getScreenWidth(){
    if (!sceneWidth){
        QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
        sceneWidth = primaryScreenGeometry.width();
    }
    qDebug() << "sceneWidth: " << sceneWidth;
    return sceneWidth;
}

int SceneUtils::getScreenHeight(){
    if (!sceneHeight){
        QRect primaryScreenGeometry(QApplication::desktop()->screenGeometry());
        sceneHeight = primaryScreenGeometry.height();
    }
    qDebug() << "sceneHeight: " << sceneHeight;
    return sceneHeight;
}

bool SceneUtils::addToScene(QGraphicsItem* item){
    if (scene != NULL){
        scene->addItem(item);        
        return true;
    }
    return false;
}

bool SceneUtils::removeFromScene(QGraphicsItem* item){
    if (scene != NULL && item != NULL && item->scene() != NULL && item->scene() == scene){
        scene->removeItem(item);
        return true;
    }
    return false;
}

qreal SceneUtils::getTranslatedWidth(qreal widthPercent){
    qreal translatedWidth = getScreenWidth() * (widthPercent/100) * percentFactor;
    qDebug() << "Translated width: " << translatedWidth;
    return translatedWidth;
}

qreal SceneUtils::getTranslatedHeight(qreal heightPercent){
    qreal translatedHeight = getScreenHeight() * (heightPercent/100) * percentFactor;
    qDebug() << "Translated height: " << translatedHeight;
    return translatedHeight;
}

QPoint SceneUtils::getTranslatedPosition(QPoint percentPos){    
    QPoint translatedPos(getTranslatedWidth(percentPos.x()), getTranslatedHeight(percentPos.y()));
    qDebug() << "Translated position: " << translatedPos.x() << ", " << translatedPos.y();
    return translatedPos;
}

int SceneUtils::getPercentWidth(int width){
    return static_cast<int>(width / getScreenWidth());
}

int SceneUtils::getPercentHeight(int height){
    return static_cast<int>(height / getScreenHeight());
}

QPoint SceneUtils::getPercentPosition(QPoint position){
    return QPoint(getPercentWidth(position.x()), getPercentHeight(position.y()));
}

QPixmap SceneUtils::getPixMap(QSize size, QColor color){
    QPixmap pxr(size);
    pxr.fill(color);

    return pxr;
}

int SceneUtils::getSceneWidth(){
    int width = scene->width();
    qDebug() << "Scene width:" << width;
    return width;
}

int SceneUtils::getSceneHeight(){
    int height = scene->height();
    qDebug() << "Scene height:" << height;
    return height;
}

bool SceneUtils::isOutOfScene(QGraphicsItem *item){
    if (item){

        int safeArea = 500;

        qreal itemWidth = item->boundingRect().width();
        qreal itemHeight = item->boundingRect().height();
        qreal itemX = item->x();
        qreal itemY = item->y();

        if ((itemX + itemWidth > getSceneWidth() + safeArea)
                || (itemX + itemWidth < 0 - safeArea)
                || (itemY + itemHeight > getSceneHeight() + safeArea)
                || (itemY + itemHeight < 0 - safeArea))
            return true;

        return false;
    }
}

