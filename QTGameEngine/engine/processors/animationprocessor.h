#ifndef ANIMATIONPROCESSOR_H
#define ANIMATIONPROCESSOR_H
#include <QList>
#include <QImage>
#include "engine/constants.h"
#include "engine/utils/utils.h"
#include "engine/utils/timerutils.h"
#include "engine/enums/enums.h"
#include "engine/items/image.h"
#include "engine/utils/memorytemplates.h"
#include "engine/utils/cachemanager.h"
#include "engine/items/cacheobject.h"

class AnimationProcessor: public QObject {
public:
    AnimationProcessor(const QString& sourceFolder, const QString& imgPattern, int imgCount);
    QPointer<Image> provideCurrentImage();
    bool isAnimated();
    bool imgsLoadedSuccessfully();
    void setImgChangeIntervalFrames(int interval);
    void setImgChangeIntervalSecs(int interval);
    void setImgExtension(const QString& extension);
    void setLooping(bool value);
    bool isLoopFinished();
    bool isLoopingEnabled();
    void shallRandomPictures(bool condition);
    QRectF getSize();

private:
    QRectF updateSize(QPointer<Image> image);
    QList<QPointer<Image> > images;    
    QRectF size;
    bool loadImages(int imgCount);
    QPointer<Image> loopImages();
    bool animated;
    bool imgsLoaded;
    long lastUsedFrame;
    QString imgExtension;
    QString imgPathPattern;
    int lastUsedImageIndex;
    QPointer<Image> lastUsedImage;
    int imgChangeIntervalFrames;
    bool shallLoop;
    bool loopFinished;
    bool randomPictures;
};

#endif // ANIMATIONPROCESSOR_H
