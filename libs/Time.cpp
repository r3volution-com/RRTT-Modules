#include "Time.h"

Time::Time() {
    clock = new thor::StopWatch();
    type = 0;
}

Time::Time(float time){
    timer = new thor::Timer();
    timer->reset(sf::seconds(time));
    timerTime = time;
    type = 1;
}

Time::Time(float time, std::function<void(thor::CallbackTimer&)> listener){
    cTimer = new thor::CallbackTimer();
    cTimer->reset(sf::seconds(time));
    cTimer->connect(listener);
    timerTime = time;
    type = 2;
}

Time::~Time() {
    delete clock;
    delete timer;
    delete cTimer;
    clock = NULL;
    timer = NULL;
    cTimer = NULL;
}

void Time::start(){
    switch(type){
        case 0:
            clock->start();
        break;
        case 1:
            if (!timer->isExpired()) timer->start();
        break;
        case 2:
            if (!cTimer->isExpired()) timer->start();
        break;
        default: break;
    }
}
void Time::resume(){
    switch(type){
        case 0:
            clock->start();
        break;
        case 1:
            if (!timer->isExpired()) timer->start();
        break;
        case 2:
            if (!cTimer->isExpired()) timer->start();
        break;
        default: break;
    }
}
void Time::pause(){
    switch(type){
        case 0:
            clock->stop();
        break;
        case 1:
            if (!timer->isExpired()) timer->stop();
        break;
        case 2:
            if (!cTimer->isExpired()) timer->stop();
        break;
        default: break;
    }
}
void Time::reset(){
    switch(type){
        case 0:
            clock->reset();
        break;
        case 1:
            timer->reset(sf::seconds(timerTime));
        break;
        case 2:
            cTimer->reset(sf::seconds(timerTime));
        break;
        default: break;
    }
}
void Time::restart(){
    switch(type){
        case 0:
            clock->restart();
        break;
        case 1:
            timer->restart(sf::seconds(timerTime));
        break;
        case 2:
            cTimer->restart(sf::seconds(timerTime));
        break;
        default: break;
    }
}

float Time::getTime(){
    switch(type){
        case 0:
            clock->getElapsedTime().asSeconds();
        break;
        case 1:
            timer->getRemainingTime().asSeconds();
        break;
        case 2:
            cTimer->getRemainingTime().asSeconds();
        break;
        default: break;
    }
}

bool Time::isRunning(){
    switch(type){
        case 0:
            return clock->isRunning();
        break;
        case 1:
            return timer->isRunning();
        break;
        case 2:
            return cTimer->isRunning();
        break;
        default: 
            return false; 
        break;
    }
}

bool Time::isExpired(){
    switch(type){
        case 0:
            return false;
        break;
        case 1:
            return timer->isExpired();
        break;
        case 2:
            return cTimer->isExpired();
        break;
        default: 
            return true; 
        break;
    }
}