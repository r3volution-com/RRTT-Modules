#include "Game.h"

Game* Game::pinstance = 0;

Game* Game::Instance(){
    
    if(pinstance == 0){
        pinstance = new Game();
    }
    
    return pinstance;
}

Game::Game(){
    screenSize = new Coordinate(1280, 720);
    window = new sf::RenderWindow(sf::VideoMode(screenSize->x, screenSize->y), "Rath's Revenge: The Twisted Timeline");
    cameraView = sf::View(sf::FloatRect(0,0,2048,2048));
    screenView = sf::View(sf::FloatRect(0,0,1280,720)); //ToDo: inutil
    
    intro = new IntroState();
    menu = new MenuState();
    level = new LevelState();
    game = intro; //ToDo: Cambiar
    
    fpsTimer = new Time(1);
    fps = 60;
    fpsCounter = 0;
    
    iaPS = 15;
    maxTime = 1.0f/iaPS;
    iaTimer = new Time(maxTime);
    deltaTime = 0;
    currentTime = 1.0f/iaPS;
    interpolation = 0;
    
    rM = new ResourceManager();
    mouse = new Hitbox(0, 0, 1, 1);
    iM = new Event();
}

void texto(std::string texto){
    std::cout << "Has escrito: " << texto << "\n";
}

void Game::Init(){
    iM->addAction("close", thor::Action(sf::Keyboard::Escape, thor::Action::ReleaseOnce) || thor::Action(sf::Event::Closed));
    game->Init();
    fpsTimer->start();
    iaTimer->start();
    rM->loadTexture("console-bg", "resources/console-bg.png");
    rM->loadFont("console", "resources/font.ttf");
    console = new Console(Coordinate(0,500), rM->getTexture("console-bg"), Rect<float>(0,0,1280,220), rM->getFont("console"));
    console->addCommand("texto", &texto);
}

void Game::Input(){
    if (iM->isActive("close")) Game::Instance()->window->close();
    mouse->setPosition(Coordinate(sf::Mouse::getPosition(*Game::Instance()->window)));
    game->Input();
}

void Game::Update(){
    iM->update();
    game->Update();
}

void Game::Render(){
    deltaTime = currentTime-iaTimer->getTime();
    currentTime = maxTime-iaTimer->getTime();
    interpolation = currentTime / maxTime;
    
    fpsCounter++;
    if (fpsTimer->isExpired()){
        fps = fpsCounter;
        fpsCounter = 0;
        fpsTimer->restart();
    }
    
    //cout << "RenderTime: " << currentTime << endl;
    //cout << "DeltaTime: " << deltaTime << endl;
    
    window->clear();
    
    game->Render();
    
    window->display();
}

void Game::ChangeCurrentState(const std::string &state){
    
    game->CleanUp();
    
    if(state == "level"){
        game = level;
    }else if(state == "menu"){
        game = menu;
    }else if(state == "intro"){
        game = intro;
    }
    game->Init();
}
