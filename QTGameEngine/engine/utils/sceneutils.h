#ifndef SCENEUTILS_H
#define SCENEUTILS_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPoint>
#include "utils.h"

class SceneUtils {
public:
    static SceneUtils& getInstance() {
        static SceneUtils instance;
        return instance;
    }

    bool attachToScene(QGraphicsScene* scene);    
    int getScreenWidth();
    int getScreenHeight();
    int getSceneWidth();
    int getSceneHeight();
    qreal getTranslatedWidth(qreal widthPercent);
    qreal getTranslatedHeight(qreal heightPercent);
    int getPercentWidth(int width);
    int getPercentHeight(int height);
    QPoint getPercentPosition(QPoint position);
    QPoint getTranslatedPosition(QPoint percentPos);
    bool addToScene(QGraphicsItem* item);
    bool removeFromScene(QGraphicsItem* item);
    QPixmap getPixMap(QSize size, QColor color);
    bool isOutOfScene(QGraphicsItem* item);

private:
    QPointer <QGraphicsScene> scene;
    int sceneWidth;
    int sceneHeight;
    qreal percentFactor;

    SceneUtils();
    SceneUtils(const SceneUtils &);
    SceneUtils& operator=(const SceneUtils&);
    ~SceneUtils(){}
};

#endif // SCENEUTILS_H
