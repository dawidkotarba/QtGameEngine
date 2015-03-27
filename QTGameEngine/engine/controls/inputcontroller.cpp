#include "engine/controls/inputcontroller.h"
#include "engine/utils/utils.h"

void InputController::controlKeyPress(QKeyEvent* event){
    if (controlableItem != NULL)
        controlableItem->controlKeyPress(event);

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

    if (controlableItem != NULL)
        controlableItem->controlKeyRelease(event);
    /*
    switch(event->key()){
    case Qt::Key_Up:
        break;
    case Qt::Key_Left:
        break;
    case Qt::Key_Right:
        break;
    case Qt::Key_Down:
        break;
    case Qt::Key_Space:
        break;
    }
*/
    event->accept();
}

void InputController::setControlableItem(Controlable* item){
    controlableItem = item;
}
