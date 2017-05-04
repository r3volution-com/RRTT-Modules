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
    
    std::map<std::string, std::function<void(std::string)>> commands;
    
    bool active;
public:
    Console(Coordinate coor, Texture *bg, Rect<float> rect, Font *f);
    virtual ~Console();
    
    void addCommand(std::string command, std::function<void(std::string)> function);
    
    void writeCommand(std::string text);
    void sendCommand(std::string command);
    
    void drawConsole();
    
    void toggleActive();
    
    bool isActive() { return active; }
    
    std::vector<std::string> splitString(std::string text, std::string delimiter);
};

#endif /* CONSOLE_H */