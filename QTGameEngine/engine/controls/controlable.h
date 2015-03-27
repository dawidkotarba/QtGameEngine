#ifndef CONTROLABLE_H
#define CONTROLABLE_H
#include <QObject>
#include <QKeyEvent>

class Controlable {

public:
    virtual void controlKeyPress(QKeyEvent* event){}
    virtual void controlKeyRelease(QKeyEvent* event){}

};


#endif // CONTROLABLE_H
