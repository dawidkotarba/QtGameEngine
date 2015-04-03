#ifndef CLOUD_H
#define CLOUD_H
#include "engine/items/item.h"
#include "game/resources.h"

class Cloud : public Item {

public:
    Cloud():
        Item(Asset(PATH_CLOUD)){}

};

class Cloud2 : public Item {

public:
    Cloud2():
        Item(Asset(PATH_CLOUD2)){}

};

class Cloud3 : public Item {

public:
    Cloud3():
        Item(Asset(PATH_CLOUD3)){}

};

class Cloud4 : public Item {

public:
    Cloud4():
        Item(Asset(PATH_CLOUD4)){}

};

class Cloud5 : public Item {

public:
    Cloud5():
        Item(Asset(PATH_CLOUD5)){}

};

class Cloud6 : public Item {

public:
    Cloud6():
        Item(Asset(PATH_CLOUD6)){}

};

#endif // CLOUD_H
