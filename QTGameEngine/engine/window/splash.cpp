#include "splash.h"

Splash::Splash(){
    QPixmap pixmap (PATH_SPLASH);
    splash = new QSplashScreen(pixmap);
    QFont font("FreeSans", 20, QFont::Bold);
    splash->setFont(font);
    splash->show();
    splash->showMessage(QObject::tr("Loading..."), Qt::AlignBottom | Qt::AlignHCenter);
}

void Splash::show(){
    if(splash)
        splash->show();
}

void Splash::close(){
    if(splash)
        splash->close();
}
