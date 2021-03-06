#ifndef STARS_H
#define STARS_H
#include "engine/items/item.h"
#include "game/resources.h"
#include "game/constants.h"

class Star16 : public Item {

public:
    Star16():
        Item(Asset(PATH_STAR16)){
        ItemEffect effect(this, ItemEffectType(ROTATE), Utils::getInstance().randInt(-5, 5));
        addEffect(effect);
    }
};

class Star32 : public Item {

public:
    Star32():
        Item(Asset(PATH_STAR32)){
        ItemEffect effect(this, ItemEffectType(ROTATE), Utils::getInstance().randInt(-5, 5));
        addEffect(effect);
    }
};

#endif // STARS_H
