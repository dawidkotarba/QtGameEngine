#include "engine/controls/inputcontroller.h"
#include "engine/utils/utils.h"

void InputController::controlKeyPress(QKeyEvent* event){
    if (!controlableItems.isEmpty())
        foreach (Controlable* item, controlableItems)
            item->controlKeyPress(event);

    switch(event->key()){
    case Qt::Key_Escape:
        Utils::getInstance().closeApplication();
        break;
    }
}

void InputController::controlKeyRelease(QKeyEvent* event){

    if (event->isAutoRepeat()){
        event->ignore();
        return;
    }

    if (!controlableItems.isEmpty())
        foreach (Controlable* item, controlableItems)
            item->controlKeyRelease(event);

    event->accept();
}

void InputController::addControlable(Controlable* controlable){
    controlableItems.append(controlable);
}
