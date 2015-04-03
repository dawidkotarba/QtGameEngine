#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H
#include <QList>
#include <QtWidgets>
#include <QtOpenGL>
#include <QObject>
#include <QPointer>
#include <QMediaPlayer>
#include <QGraphicsItem>
#include "engine/items/cacheobject.h"
#include "engine/items/image.h"
#include "engine/utils/memorytemplates.h"

class CacheManager : public QObject {
public:

    static CacheManager& getInstance()
    {
        static CacheManager instance;
        return instance;
    }

    void addToCache(QPointer<CacheObject<Image> > item){        
        imageCache.insert(item->getName(), item);
    }

    QPointer<CacheObject<Image> > getFromCache(QString itemPath){
        return imageCache.value(itemPath);
    }

private:
    QHash<QString, QPointer<CacheObject<Image> > > imageCache;
    CacheManager(){}
    CacheManager(const CacheManager&){}
    CacheManager& operator=(const CacheManager&){}
    virtual ~CacheManager(){

        QList<QPointer<CacheObject<Image> > > values = imageCache.values();
        clear_qptr_list(values);
    }
};
#endif // CACHEMANAGER_H
