#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>

class Input {
    private:
        thor::ActionMap<std::string> map;
        thor::ActionMap<std::string>::CallbackSystem system;
    public:
        Input();
        virtual ~Input();
        
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
        void addActionCallback(std::string name, thor::Action act, std::function< void()> nullaryListener);
        
        /**
         * Comprueba las acciones registradas
         * @param window: Ventana
         */
        void update(sf::Window window);
        
        /**
         * Invoca a todos los callbacks registrados
         * @param window: Ventana
         */
        void callbacks(sf::Window window);
        
        /**
         * Comprueba si se esta pulsando esa combinacion de teclas
         * @param name: Teclas
         * @return 
         */
        bool isActive(std::string name);
};

#endif /* INPUT_H */