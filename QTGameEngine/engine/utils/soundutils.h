#ifndef SOUNDUTILS_H
#define SOUNDUTILS_H
#include <QList>
#include <QtWidgets>
#include <QtOpenGL>
#include <QObject>
#include <QPointer>
#include <QMediaPlayer>
#include <QGraphicsItem>
#include "engine/constants.h"
#include "engine/utils/memorytemplates.h"

class SoundUtils {

public:

    static SoundUtils& getInstance() {
        static SoundUtils instance;
        return instance;
    }

    bool playSound(QString fileName, int volume = 100);

private:
    SoundUtils(){}
    SoundUtils(const SoundUtils &){}
    SoundUtils& operator=(const SoundUtils&){}
    ~SoundUtils();

    QList<QPointer<QMediaPlayer> > soundPlayers;
    bool play(QPointer<QMediaPlayer> player, QString fileName, int volume = 100);
};

#endif // SOUNDUTILS_H
