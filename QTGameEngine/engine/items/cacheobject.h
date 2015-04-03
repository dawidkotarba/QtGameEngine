#ifndef CACHEOBJECT_H
#define CACHEOBJECT_H
#include <QObject>
#include <QPointer>
#include <QList>
#include "engine/utils/memorytemplates.h"

template <class T>
class CacheObject: public QObject {
public:
    CacheObject(QString path, QList<QPointer<T> > items){
        this->path = path;
        this->items = items;
    }

    virtual ~CacheObject(){
        clear_qptr_list(items);
    }

    QString getName(){
        return path;
    }

    QList<QPointer<T> > getItems(){
        return items;
    }

private:
    QList<QPointer<T> > items;
    QString path;
};

#endif // CACHEOBJECT_H
