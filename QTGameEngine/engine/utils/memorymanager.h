#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include <QList>
#include <QtWidgets>
#include <QtOpenGL>
#include <QObject>
#include <QPointer>
#include <QMediaPlayer>
#include <QGraphicsItem>
#include "engine/items/item.h"
#include "engine/utils/memorytemplates.h"

class MemoryManager {
public:

    static MemoryManager& getInstance()
    {
        static MemoryManager instance;
        return instance;
    }
    void addToItemsList(QPointer<QObject> item);
    void clearMemory();
    void clearMarkedAsForDelete();

private:
    QList<QPointer<QObject> > allItems;
    MemoryManager();
    MemoryManager(const MemoryManager&);
    MemoryManager& operator=(const MemoryManager&);
    ~MemoryManager();
};

#endif // MEMORYMANAGER_H
