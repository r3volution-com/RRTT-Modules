#include "Console.h"
#include "libs/Sprite.h"
#include "libs/Text.h"
#include "Game.h"

Console::Console(Coordinate coor, Texture *bg, Rect<float> rect, Font *f) {
    background = new Sprite(bg, rect);
    background->setPosition(coor);
    
    backlog = new Text("---", (coor+10), f, false);
    actual = new Text("", Coordinate(coor.x+5, coor.y+175), f, false);
    
    backlog->setTextStyle(sf::Color::Black, 20);
    backlog->setOutlineStyle(sf::Color::White, 1);
    actual->setTextStyle(sf::Color::Black, 20);
    actual->setOutlineStyle(sf::Color::White, 1);
    
    commands = std::map<std::string, std::function<void(std::string)>>();
    
    active = false;
    historyLength = 7;
}

Console::~Console() {
    delete background;
    delete backlog;
    delete actual;
    history.clear();
    commands.clear();
    background = NULL;
    backlog = NULL;
    actual = NULL;
}

void Console::addCommand(std::string command, std::function<void(std::string)> function){
    commands.insert(std::pair<std::string, std::function<void(std::string)>>(command, function));
}
    
void Console::writeCommand(std::string text){
    actual->setText(text);
}

void Console::writeInBacklog(std::string command){
    history.push_back(command);
    std::string text = "";
    int start = 0;
    if (((int)history.size()-historyLength) > 0) start = ((int)history.size()-historyLength);
    for (int i = start; i < history.size(); i++){
        text = text + history.at(i) + "\n";
    }
    backlog->setText(text);
}

void Console::sendCommand(std::string command){ //ToDo: posible funcion para navegar por el historial con la flechas
    actual->setText("");
    writeInBacklog(command);
    std::vector<std::string> strParts = splitString(command, " ");
    if (strParts.size() == 2){
        std::function<void(std::string)> f;
        try{
            f = commands[(std::string)strParts[0]];
            f(strParts[1]);
        } catch (const std::out_of_range& oor) {
            std::ostringstream err;
            err << "El comando " << strParts[0] << " es incorrecto.";
            writeInBacklog(err.str());
        } catch (const std::bad_function_call& c){
            std::ostringstream err;
            err << "El comando " << strParts[0] << " es incorrecto.";
            writeInBacklog(err.str());
        }
    } else {
        std::ostringstream err;
        err << "El numero de argumentos (" << strParts.size() << ") es incorrecto." << command;
        writeInBacklog(err.str());
    }
}

void Console::toggleActive(){
    if (!active) active = true;
    else active = false;
}

void Console::drawConsole(){
    if (active){
        Game::Instance()->window->draw(*background->getSprite());
        Game::Instance()->window->draw(*backlog->getText());
        Game::Instance()->window->draw(*actual->getText());
    }
}

std::string erasePart(std::string text, std::string delimiter){
    size_t pos = 0;
    if ((pos = text.find(delimiter)) != std::string::npos) {
        text.erase(0, pos + delimiter.length());
    }
    return text;
}

std::vector<std::string> Console::splitString(std::string text, std::string delimiter){
    size_t pos = 0;
    std::string token;
    std::vector<std::string> result;
    text = text + " ";
    while ((pos = text.find(delimiter)) != std::string::npos) {
        token = text.substr(0, pos);
        result.push_back(token);
        text.erase(0, pos + delimiter.length());
    }
    return result;
}
