#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <functional>
#include "libs/Sprite.h"
#include "libs/Text.h"

class Console {
private:
    Sprite *background;
    Text *backlog;
    Text *actual;
    std::vector<std::string> history;
    
    std::map<std::string, std::function<void(std::string)>> commands;
    
    int historyLength;
    bool active;
public:
    /**
     * Crea un objeto consola
     * @param coor: Coordenada. Tipo Coordinate
     * @param bg: Textura de la consola
     * @param rect: Zona en la que se imprime la consola
     * @param f: Fuente del texto de la consola
     */
    Console(Coordinate coor, Texture *bg, Rect<float> rect, Font *f);
    virtual ~Console();
    
    /**
     * Anadir comando a la consola
     * @param command: Comando a anadir
     * @param function: Funcion a anadir
     */
    void addCommand(std::string command, std::function<void(std::string)> function);
    
    /**
     * Escribir un comando por la consola
     * @param text: Texto a introducir en la consola
     */
    void writeCommand(std::string text);

    /**
     * Envia un comando por consola
     * @param command: Comando a enviar por consola
     */
    void sendCommand(std::string command);
    
    /**
     * Escribe en el backlog
     * @param command: Comando a escribir
     */
    void writeInBacklog(std::string command);
    
    /**
     * Dibujar la consola
     */
    void drawConsole();
    
    /**
     * Muestra o no muestra la consola segun si esta activa
     */
    void toggleActive();
    
    /**
     * Comprueba si la consola esta activa
     * @return : Booleano
     */
    bool isActive() { return active; }
    
    std::vector<std::string> splitString(std::string text, std::string delimiter);
};

#endif /* CONSOLE_H */
