#ifndef TIMERUTILS_H
#define TIMERUTILS_H
#include <iostream>
#include "../constants.h"

class TimerUtils {
public:

    static TimerUtils& getInstance() {
        static TimerUtils instance;
        return instance;
    }

private:

    long frameCount;

    TimerUtils():frameCount(0) {}
    TimerUtils(const TimerUtils &);
    TimerUtils& operator=(const TimerUtils&);
    ~TimerUtils() {}
    int convertSecToFrames();
public:
    long getFrameCount();
    bool countEachFrame(int frames);
    void incrementStepCount();
    bool countEachSecs(int secs);
    int convertSecsToFrames(int secs);
};

#endif // TIMERUTILS_H
