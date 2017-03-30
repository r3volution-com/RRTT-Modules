#ifndef TIME_H
#define TIME_H

#include <Thor/Time.hpp>

class Time {
    private:
        thor::StopWatch *clock;
        thor::Timer *timer;
        thor::CallbackTimer *cTimer;
        
        float timerTime;
        int type;
    public:
        Time();
        Time(float time);
        Time(float time, std::function< void(thor::CallbackTimer&)> listener);
        virtual ~Time();
        
        void start();
        void resume();
        void pause();
        void reset();
        void restart();
        
        float getTime();
        bool isRunning();
        bool isExpired();
};

#endif /* TIME_H */