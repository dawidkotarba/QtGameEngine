#ifndef UTILS_H
#define UTILS_H
#include <QList>
#include <QtWidgets>
#include <QtOpenGL>
#include <QObject>
#include <QPointer>
#include <QMediaPlayer>
#include <QGraphicsItem>
#include "engine/constants.h"

class Utils {

public:

    static Utils& getInstance() {
        static Utils instance;
        return instance;
    }

    int randInt(int min, int max);
    float randFloat(float min, float max);
    void setApplicationReference(QApplication* application);
    void closeApplication();

private:
    QApplication* application;

    Utils();
    Utils(const Utils &);
    Utils& operator=(const Utils&);
    ~Utils();
};

#endif // UTILS_H
