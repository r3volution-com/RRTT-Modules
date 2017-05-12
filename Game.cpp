#include "Game.h"

void texto(std::string texto){ //ToDo: quitar, esto es de ejemplo para la consola
    std::cout << "Has escrito: " << texto << "\n";
}

Game* Game::pinstance = 0;

Game* Game::Instance(){
    
    if(pinstance == 0){
        pinstance = new Game();
    }
    
    return pinstance;
}

Game::~Game(){
    delete pinstance;
    delete level;
    delete menu;
    delete intro;
    delete fpsTimer;
    delete screenSize;
    delete window;
    delete rM;
    delete iM;
    delete mouse;
    delete console;
    delete iaTimer;
    
    pinstance = NULL;
    level = NULL;
    menu = NULL;
    intro = NULL;
    fpsTimer = NULL;
    screenSize = NULL;
    window = NULL;
    rM = NULL;
    iM = NULL;
    mouse = NULL;
    console = NULL;
    iaTimer = NULL;
}

Game::Game(){
    screenSize = new Coordinate(1280, 720);
    window = new sf::RenderWindow(sf::VideoMode(screenSize->x, screenSize->y), "Rath's Revenge: The Twisted Timeline");
    cameraView = sf::View(sf::FloatRect(0,0,2048,1080));
    
    intro = new IntroState();
    menu = new MenuState();
    level = new LevelState();
    game = intro;
    
    /*FPS*/
    fpsTimer = new Time(1);
    fps = 60;
    fpsCounter = 0;
    
    /*IA*/
    iaPS = 15;
    maxTime = 1.0f/iaPS;
    iaTimer = new Time(maxTime);
    deltaTime = 0;
    currentTime = 1.0f/iaPS;
    interpolation = 0;
    
    /*Managers*/
    rM = new ResourceManager();
    iM = new Event();
    mouse = new Hitbox(0, 0, 1, 1);
}

void Game::Init(){
    iM->addAction("close", thor::Action(sf::Keyboard::F11, thor::Action::ReleaseOnce) || thor::Action(sf::Event::Closed));
    iM->addAction("console", thor::Action(sf::Keyboard::F12, thor::Action::PressOnce));
    game->Init();
    fpsTimer->start();
    iaTimer->start();
    rM->loadTexture("console-bg", "resources/console-bg.png");
    rM->loadFont("console", "resources/font.ttf");
    
    console = new Console(Coordinate(0,500), rM->getTexture("console-bg"), Rect<float>(0,0,1280,220), rM->getFont("console"));
    console->addCommand("texto", &texto);
    //ToDo: anadir comandos a la consola
}

void Game::Input(){
    if (iM->isActive("close")) window->close();
    if (iM->isActive("console")) console->toggleActive();
    mouse->setPosition(Coordinate(sf::Mouse::getPosition(*window)));
    game->Input();
}

void Game::Update(){
    iM->update();
    game->Update();
    //ToDo mostrar los FPs si se inserta el comando
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
    
    window->clear();
    
    game->Render();
    
    console->drawConsole();
    
    window->display();
}

void Game::ChangeCurrentState(const std::string &state){
    game->CleanUp();
    
    if(state == "intro") game = intro;
    else if(state == "menu") game = menu;
    else if(state == "level") game = level;
    else window->close();
    
    game->Init();
}
