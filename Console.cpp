#include "Console.h"
#include "libs/Sprite.h"
#include "libs/Text.h"
#include "Game.h"

Console::Console(Coordinate coor, Texture *bg, Rect<float> rect, Font *f) {
    cout << coor << " in " << rect;
    background = new Sprite(bg, rect);
    background->setPosition(coor);
    
    backlog = new Text("---", (coor+10), f, false);
    actual = new Text(">", Coordinate(coor.x+5, coor.y+175), f, false);
    
    backlog->setStyles(sf::Color::Black, sf::Color::White, 1, 20);
    actual->setStyles(sf::Color::Black, sf::Color::White, 1, 20);
    
    commands = std::map<std::string, std::function<void(std::string)>>();
    
    active = false;
}

Console::~Console() {
}

void Console::addCommand(std::string command, std::function<void(std::string)> function){
    commands.insert(std::pair<std::string, std::function<void(std::string)>>(command, function));
}
    
void Console::writeCommand(std::string text){
    actual->setText(text);
}

void Console::sendCommand(std::string command){
    actual->setText("");
    std::ostringstream os;
    os << (std::string)backlog->getText()->getString() << "\n" << command;
    backlog->setText(os.str()); //ToDo: Cambiar por otra funcion que desplace el texto
    std::vector<std::string> strParts = splitString(os.str(), " ");
    if (strParts.size() == 2){
        try{
            std::function<void(std::string)> f = commands[(std::string)strParts[0]];
            f(strParts[1]);
        } catch (const std::out_of_range& oor) {
            std::ostringstream err;
            err << "El comando " << strParts[0] << " es incorrecto.";
            backlog->setText(err.str()); //ToDo: Cambiar por otra funcion que desplace el texto
        }
    } else {
        std::ostringstream err;
        err << "El numero de argumentos (" << strParts.size() << ") es incorrecto." << command;
        backlog->setText(err.str()); //ToDo: Cambiar por otra funcion que desplace el texto
    }
    //TODO: Parsear, buscar en map y llamar a function
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

std::vector<std::string> Console::splitString(std::string text, std::string delimiter){
    size_t pos = 0;
    std::string token;
    std::vector<std::string> result;
    while ((pos = text.find(delimiter)) != std::string::npos) {
        std::cout << pos << std::string::npos << "\n";
        token = text.substr(0, pos);
        result.push_back(token);
        text.erase(0, pos + delimiter.length());
    }
    return result;
}