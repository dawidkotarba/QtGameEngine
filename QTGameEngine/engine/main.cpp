#include <QtWidgets>
#include <math.h>
#include "engine/window/window.h"
#include "engine/controls/inputcontroller.h"
#include "utils/utils.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    Window view;
    Utils::getInstance().setApplicationReference(&app);    
    app.setOverrideCursor(QCursor( Qt::BlankCursor ));
    return app.exec();
}
