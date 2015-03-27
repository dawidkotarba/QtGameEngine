#ifndef ITEMTIMESPAWNER_H
#define ITEMTIMESPAWNER_H
#include "engine/items/item.h"
#include "engine/utils/utils.h"
#include "engine/items/item.h"

template <class T>
class ItemTimeSpawner: public QObject, public Item
{
public:
    ItemTimeSpawner(int secondsDelay, int spreadY, QPoint initialPos = QPoint(0,0)){
        this->secondsDelay = secondsDelay;
        this->spreadY = spreadY;
        this->setInitPos(initialPos);
    }

    void action(){
        if (TimerUtils::getInstance().countEachSecs(secondsDelay)){
            QPointer<Item> item = new T();
            qreal posX = initialPos.x() + itemNo*spreadX;
            qreal posY = initialPos.y() + Utils::getInstance().randInt(-spreadY, spreadY);

            QPoint pos(posX, posY);
            item->setPos(pos);
            item->setInitPos(pos);

            items.append(item);
            item->start();
        }
    }

    virtual ~ItemTimeSpawner(){
        qDebug() << "Clearing ItemTimeSpawner items: " << items.size();
        clear_qptr_list(items);
    }

private:
    QList<QPointer<Item> > items;
    int spreadY;
    int secondsDelay;
};


#endif // ITEMTIMESPAWNER_H
