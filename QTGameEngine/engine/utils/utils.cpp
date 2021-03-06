#include "utils.h"

Utils::Utils():
    application(NULL){}

Utils::~Utils(){}

int Utils::randInt(int min, int max){
    return qrand() % ((max + 1) - min) + min;
}

float Utils::randFloat(float min, float max){

    if (max-min == 0)
        return max;

    return min + static_cast <float> (qrand()) /( static_cast <float> (RAND_MAX /(max-min)));
}

void Utils::setApplicationReference(QApplication* application){
    this->application = application;
}

void Utils::closeApplication(){
    application->exit();
}
