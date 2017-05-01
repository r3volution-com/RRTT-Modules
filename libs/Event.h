#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>

class Event {
    private:
        thor::ActionMap<std::string> map;
        thor::ActionMap<std::string>::CallbackSystem system;
    public:
        Event();
        virtual ~Event();
        
        /**
         * Anade una accion
         * @param name: Nombre de la accion
         * @param act: Tecla a pulsar
         */
        void addAction(std::string name, thor::Action act);
        
        /**
         * Anadir una accion que ejecuta una funcion al cumplirse
         * @param name: Nombre de la accion
         * @param act: Tecla a pulsar
         * @param nullaryListener: Accion a realizar
         */
        void addActionCallback(std::string name, thor::Action act, std::function<void(thor::ActionContext<std::string>)> unaryListener);
        
        /**
         * Comprueba las acciones registradas
         * @param window: Ventana
         */
        void update();
        
        /**
         * Comprueba si se esta pulsando esa combinacion de teclas
         * @param name: Teclas
         * @return 
         */
        bool isActive(std::string name);
};

#endif /* INPUT_H */