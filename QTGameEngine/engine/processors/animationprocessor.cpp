#include "animationprocessor.h"

AnimationProcessor::AnimationProcessor(const QString& sourceFolder, const QString& imgPattern, int imgCount):
    size(ITEM_ZERO_SQUARE),
    animated(false),
    imgsLoaded(false),
    imgChangeIntervalFrames(2),
    lastUsedImageIndex(0),
    lastUsedImage(NULL),
    randomPictures(false),
    lastUsedFrame(CODE_NOT_INITIALIZED),
    shallLoop(false),
    loopFinished(false),
    imgExtension(STRING_EXT_PNG)
{

    if (sourceFolder != NULL && imgCount != NULL){

        if (imgPattern != "")
            imgPathPattern = sourceFolder + STRING_SLASH + imgPattern;
        else
            imgPathPattern = sourceFolder;

        imgsLoaded = loadImages(imgCount);
    }
}

bool AnimationProcessor::loadImages(int imgCount){

    if (!imgsLoaded){

        QPointer<CacheObject<Image> > cachedImages = CacheManager::getInstance().getFromCache(imgPathPattern);

        if (cachedImages)
            images = cachedImages->getItems();

        else{
            for (int imgNo=0; imgNo<imgCount; imgNo++){
                QPointer<Image> tmpImgRef = NULL;

                QString imgNumber(QString::number(imgNo));

                // load images with animation name pattern (img00, img01...)
                if (imgNo<10)
                    imgNumber = "0" +  QString::number(imgNo);

                QString imgPath = imgPathPattern + imgNumber + imgExtension;
                tmpImgRef = new Image(imgPath);

                // load images other than animations
                if (tmpImgRef->isNull()){
                    imgPath = imgPathPattern + imgExtension;
                    tmpImgRef = new Image(imgPath);
                }

                if (tmpImgRef)
                    images.append(tmpImgRef);
                else
                    qDebug() << "Cannot add img to container: " << imgPath;
            }

            CacheManager::getInstance().addToCache(new CacheObject<Image>(imgPathPattern, images));
        }

        if (images.size() == imgCount){

            if (imgCount > 1)
                animated = true;
            else
                shallLoop = true;

            lastUsedImage = images.at(0);

            return true;
        }
        return false;
    }
    return imgsLoaded;
}

QRectF AnimationProcessor::updateSize(QPointer<Image> image){
    if (image)
        size = QRectF(0,0,image->width(), image->height());
}

QRectF AnimationProcessor::getSize(){
    return size;
}

void AnimationProcessor::shallRandomPictures(bool condition){
    randomPictures = true;
}

void AnimationProcessor::setImgExtension(const QString& extension){
    imgExtension = STRING_DOT + extension;
}

void AnimationProcessor::setLooping(bool value){
    shallLoop = value;
}

bool AnimationProcessor::isAnimated(){
    return animated;
}

bool AnimationProcessor::imgsLoadedSuccessfully(){
    return imgsLoaded;
}

void AnimationProcessor::setImgChangeIntervalFrames(int interval){
    imgChangeIntervalFrames = interval;
}

QPointer<Image> AnimationProcessor::loopImages(){

    if (lastUsedFrame == TimerUtils::getInstance().getFrameCount())
        return lastUsedImage;
    else
        lastUsedFrame = TimerUtils::getInstance().getFrameCount();

    if (lastUsedImageIndex >= images.size()){

        if (!shallLoop){
            loopFinished = true;
            lastUsedImage = NULL;
            return NULL;
        }

        lastUsedImageIndex = 0;
    }

    if (randomPictures){
        lastUsedImage = images.at(Utils::getInstance().randInt(0, images.size()-1));
        return lastUsedImage;
    }

    lastUsedImage = images.at(lastUsedImageIndex);

    if (!lastUsedImage)
        qDebug() << "Cannot load image" << lastUsedImageIndex << "of " << imgPathPattern;
    else
        qDebug() << "Loaded animation: " << lastUsedImageIndex << " for frame "
                 << TimerUtils::getInstance().getFrameCount();

    lastUsedImageIndex++;

    return lastUsedImage;
}

bool AnimationProcessor::isLoopingEnabled(){
    return shallLoop;
}

bool AnimationProcessor::isLoopFinished(){
    return loopFinished;
}

QPointer<Image> AnimationProcessor::provideCurrentImage(){
    if (TimerUtils::getInstance().countEachFrame(imgChangeIntervalFrames))
        updateSize(loopImages());

    return lastUsedImage;
}
