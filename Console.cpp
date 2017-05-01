#include "Console.h"
#include "libs/Sprite.h"
#include "libs/Text.h"
#include "Game.h"

Console::Console(Coordinate coor, Texture *bg, Rect<float> rect, Font *f) {
    cout << coor << " in " << rect;
    background = new Sprite(bg, rect);
    background->setPosition(coor);
    
    backlog = new Text("", (coor+10), f, false);
    actual = new Text("", (coor+(rect.h-25)), f, false);
    
    backlog->setStyles(sf::Color::Black, sf::Color::White, 1, 20);
    actual->setStyles(sf::Color::Black, sf::Color::White, 1, 20);
    
    commands = new std::map<std::string, std::function<void()>>();
    
    active = false;
}

Console::~Console() {
}

void Console::addCommand(std::string command, std::function<void()> function){
    commands->insert(std::pair<std::string, std::function<void()>>(command, function));
}
    
void Console::writeCommand(std::string text){
    actual->setText(text);
}

void Console::sendCommand(std::string command){
    std::ostringstream os;
    os << (std::string)backlog->getText()->getString() << "\n" << command;
    backlog->setText(os.str());
    //TODO: Parsear, buscar en map y llamar a function
}

void Console::toggleActive(){
    if (!active) active = true;
    else active = false;
}

void Console::drawConsole(){
    if (active){
        cout << "esto es mierda";
        Game::Instance()->window->draw(*background->getSprite());
        Game::Instance()->window->draw(*backlog->getText());
        Game::Instance()->window->draw(*actual->getText());
    }
}