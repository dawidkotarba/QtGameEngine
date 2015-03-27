#ifndef CACHEOBJECT_H
#define CACHEOBJECT_H
#include <QObject>
#include <QPointer>
#include <QList>
#include "engine/utils/memorytemplates.h"

template <class T>
class CacheObject: public QObject
{
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

    bool operator==(const CacheObject &other){
        return path == other.path && items.size() == other.items.size();
    }

    uint qHash(const CacheObject &key){
        return qHash(key.path) ^ key.items.size();
    }

private:
    QList<QPointer<T> > items;
    QString path;
};

#endif // CACHEOBJECT_H
