#include "soundutils.h"

bool SoundUtils::playSound(QString fileName, int volume){

    foreach(QPointer<QMediaPlayer> player, soundPlayers){
        if (player->state()!= QMediaPlayer::PlayingState){
            play(player, fileName, volume);
            return true;
        }
    };

    QPointer<QMediaPlayer> newPlayer = new QMediaPlayer();
    play(newPlayer, fileName, volume);
    soundPlayers.append(newPlayer);
    qDebug() << "SoundPlayers increased to " << soundPlayers.size();
}

bool SoundUtils::play(QPointer<QMediaPlayer> player, const QString& fileName, int volume){
    if (player){
        player->setMedia(QUrl(PATH_SOUNDS + fileName + STRING_EXT_MP3));
        player->setVolume(volume);
        player->play();
        return true;
    }
    return false;
}

SoundUtils::~SoundUtils(){
    foreach(QPointer<QMediaPlayer> player, soundPlayers)
        if(player)
            player->stop();

    clear_qptr_list(soundPlayers);
}
