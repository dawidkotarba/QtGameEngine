#ifndef IO_H
#define IO_H
#include <QtWidgets>
#include "controlable.h"
#include "game/fighter.h"
#include "game/enums/dierctionsEnum.h"
#include "game/enums/weaponsEnum.h"

class InputController
{
    Controlable* controlableItem;

public:
    void controlKeyPress(QKeyEvent* event);
    void controlKeyRelease(QKeyEvent* event);
    void setControlableItem(Controlable* item);
};

#endif // IO_H
