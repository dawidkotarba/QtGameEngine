#ifndef SPLASH_H
#define SPLASH_H
#include <QPixmap>
#include <QSplashScreen>
#include <QPointer>
#include <QFont>
#include <QTimer>
#include "game/resources.h"

class Splash: public QObject
{
public:
    Splash();
    void show();
    void close();

private:
    QPointer<QSplashScreen> splash;
};

#endif // SPLASH_H
