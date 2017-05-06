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
        /**
         * Crea el objeto tiempo
         */
        Time();
        /**
         * Crea el objeto tiempo
         * @param time: Tiempo
         */
        Time(float time);
        /**
         * Crea el objeto tiempo
         * @param time: Tiempo 
         * @param listener: Listenner
         */
        Time(float time, std::function< void(thor::CallbackTimer&)> listener);
        virtual ~Time();
        
        void start();
        void resume();
        void pause();
        void reset();
        void restart();
        
        /**
         * Reinicia el tiempo
         * @param newTime: Tiempo
         */
        void reset(float newTime);
        
        /**
         * Reinicia el tiempo
         * @param newTime: Tiempo
         */
        void restart(float newTime);
        
        float getTime();
        float getMaxTime(){ return timerTime; }
        
        /**
         * Comprueba si esta funcionando
         * @return 
         */
        bool isRunning();
        
        /**
         * Comprueba si ha expirado
         * @return 
         */
        bool isExpired();
};

#endif /* TIME_H */