#include "timerutils.h"

long TimerUtils::getFrameCount(){
    return frameCount;
}

bool TimerUtils::countEachFrame(int frames){
    return frameCount % frames == 0;
}

bool TimerUtils::countEachSecs(int secs){
    return countEachFrame(convertSecsToFrames(secs));
}

void TimerUtils::incrementStepCount(){
    if (frameCount >= THOUSAND*THOUSAND)
        frameCount = 0;

    frameCount++;
}

int TimerUtils::convertSecToFrames(){
    return THOUSAND / WINDOW_TIMER_MSEC;
}

int TimerUtils::convertSecsToFrames(int secs){
    return convertSecToFrames() * secs;
}
