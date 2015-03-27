#ifndef MOON_H
#define MOON_H
#include "engine/items/item.h"
#include "game/resources.h"

class Moon : public Item {

public:
    Moon():
        Item(Asset(PATH_MOON)){}

};


#endif // MOON_H
