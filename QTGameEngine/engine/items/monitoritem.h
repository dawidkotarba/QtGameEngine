#ifndef MONITORITEM_H
#define MONITORITEM_H
#include "item.h"
#include "engine/utils/timerutils.h"

class MonitorItem : public Item
{
public:    
    MonitorItem():
        Item(){
        makeMonitor();
    }
     virtual ~MonitorItem(){
        qDebug() << "Deleting monitor item";
    }

    void advance(int frame){
        TimerUtils::getInstance().incrementStepCount();
        MemoryManager::getInstance().clearMarkedAsForDelete();
    }
};

#endif // MONITORITEM_H
