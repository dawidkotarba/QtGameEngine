#ifndef ITEMSPAWNER_H
#define ITEMSPAWNER_H
#include "engine/items/item.h"
#include "engine/utils/utils.h"
#include "engine/items/itemsmodifier.h"

template <class T>
class ItemSpawner: public QObject
{
public:
    ItemSpawner(int count, int spreadX, int spreadY, QPoint initialPos = QPoint(0,0)):
        initialPos(QPoint(0,0)),
        itemsModifier(NULL){
        this->count = count;
        this->spreadX = spreadX;
        this->spreadY = spreadY;

        for (int itemNo=0; itemNo<count; itemNo++){
            QPointer<Item> item = new T();
            qreal posX = initialPos.x() + itemNo*spreadX;
            qreal posY = initialPos.y() + Utils::getInstance().randInt(-spreadY, spreadY);

            QPoint pos(posX, posY);
            item->setPos(pos);
            item->setInitPos(pos);

            items.append(item);
        }

        itemsModifier = new ItemsModifier(items);
    }

    virtual ~ItemSpawner(){
        qDebug() << "Clearing ItemSpawner items: " << items.size();
        clear_qptr_list(items);
        clear_qptr(itemsModifier);
    }

    void start(){
        ItemUtils::getInstance().start(items);
    }

    QPointer<ItemsModifier> getItemsModifier(){
        return itemsModifier;
    }

private:
    QPointer<ItemsModifier> itemsModifier;
    QList<QPointer<Item> > items;
    int count;
    int spreadX;
    int spreadY;
    QPoint initialPos;

};

#endif // ITEMSPAWNER_H
