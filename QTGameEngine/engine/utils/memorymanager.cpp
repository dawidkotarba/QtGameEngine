#include "memorymanager.h"

MemoryManager::MemoryManager(){
}

MemoryManager::~MemoryManager(){
    qDebug() << "Safe clearing of all items: " << allItems.size();
    clear_qptr_list(allItems);
    allItems.clear();
}

void MemoryManager::addToItemsList(QPointer<QObject> item){
    allItems.append(item);
}

void MemoryManager::clearMemory(){
    qDebug() << "Clearing memory manually: " << allItems.size();
    clear_qptr_list(allItems);
    allItems.clear();
}

void MemoryManager::clearMarkedAsForDelete(){

    int clearedCount = 0;

    for (int i=0; i<allItems.size(); i++){

        QPointer<Item> item = (Item*) allItems.at(i).data();

        if (!item.isNull() && item->isMarkedAsForDelete()){
            clear_qptr(item);
            allItems.removeAt(i);
            clearedCount++;
        }
    }

    qDebug() << "Cleared items: " << clearedCount << ". All items: " << allItems.size();
}
