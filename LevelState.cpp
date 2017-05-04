#include "LevelState.h"
#include "Game.h"
#include "Crystals.h"
#include "Level.h"
#include "Console.h"

#define PI 3,14159265;

void onTextEntered(thor::ActionContext<std::string> context) {
    if (Game::Instance()->console->isActive()){
        if (context.event->text.unicode < 128 && (context.event->text.unicode != 13 && context.event->text.unicode != 9 && context.event->text.unicode != 8)) {
            sf::Uint32 character = context.event->text.unicode;
            std::ostringstream ch;
            ch << static_cast<char>(character);
            Game::Instance()->temp += ch.str();
            //Game::Instance()->temp << (std::string)ch.str();
            Game::Instance()->console->writeCommand(Game::Instance()->temp);
        } else if (context.event->text.unicode == 8 && Game::Instance()->temp.length() > 0){
            Game::Instance()->temp.resize(Game::Instance()->temp.length()-1);
            Game::Instance()->console->writeCommand(Game::Instance()->temp);
        } else if (context.event->text.unicode == 13){
            Game::Instance()->console->sendCommand(Game::Instance()->temp);
            Game::Instance()->temp = "";
        }
    }
}

LevelState::LevelState() : GameState(){
    
}

LevelState::~LevelState(){
    
    delete rath;
    delete tri;
    delete gunArm;
    delete rM;
    
    /*Faltaria:
        - playerTexture
     *  - level
     *  - enemy2
     *  - hud 
     */  

    rath = NULL;
    tri = NULL;
    gunArm = NULL;
    rM = NULL;
    
}

void LevelState::Init(){
    tri = new Trigonometry();
    level = new Level(1);
    
    Game *game = Game::Instance();
    
    game->rM->loadTexture("player", "resources/spritesRATH.png");
    game->rM->loadTexture("fire", "resources/fuego.png");
    
    rath = new Player(Coordinate(3900,2700), game->rM->getTexture("player"), Rect<float>(0,0, 128, 128), 15);
    rath->getAnimation()->addAnimation("idle", Coordinate(0, 0), 4, 0.5f);
    rath->getAnimation()->addAnimation("correrDerecha", Coordinate(0, 128), 4, 0.5f);
    rath->getAnimation()->addAnimation("correrArriba", Coordinate(0, 256), 4, 0.5f);
    rath->getAnimation()->addAnimation("correrIzquierda", Coordinate(0, 384), 4, 0.5f);
    rath->getAnimation()->addAnimation("ataqueDerecha", Coordinate(0, 768), 2, 0.5f);
    rath->getAnimation()->addAnimation("ataqueIzquierda", Coordinate(0, 896), 2, 0.5f);
    rath->getAnimation()->addAnimation("ataqueAbajo", Coordinate(0, 1024), 2, 0.5f);
    rath->getAnimation()->addAnimation("ataqueArriba", Coordinate(0, 1152), 2, 0.5f);
    rath->getAnimation()->initAnimator();
    rath->getAnimation()->changeAnimation("idle", false); 
    rath->setMaxHP(70);
    
    game->iM->addAction("player-up", thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-down", thor::Action(sf::Keyboard::Down));
    game->iM->addAction("player-right", thor::Action(sf::Keyboard::Right));
    game->iM->addAction("player-left", thor::Action(sf::Keyboard::Left));
    game->iM->addAction("player-Lclick", thor::Action(sf::Mouse::Left));
    
    game->iM->addAction("player-Rclick", thor::Action(sf::Mouse::Right));
    
    game->iM->addAction("player-up-left", thor::Action(sf::Keyboard::Left) && thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-up-right", thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::Up));
    game->iM->addAction("player-down-left", thor::Action(sf::Keyboard::Left) && thor::Action(sf::Keyboard::Down));
    game->iM->addAction("player-down-right", thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::Down));
    
    game->iM->addAction("console", thor::Action(sf::Keyboard::F12, thor::Action::PressOnce));
    game->iM->addActionCallback("text", thor::Action(sf::Event::TextEntered), &onTextEntered);

    gunArm = new Gun(Coordinate(0, 0), Rect<float> (0, 640, 128, 128), game->rM->getTexture("player"));
    gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
    gunArm->getAnimation()->initAnimator();    
    gunArm->getAnimation()->changeAnimation("armaIdle", false);
    gunArm->getAnimation()->setOrigin(Coordinate(56,34));
    gunArm->setDamage(30);
    
    bull = new Bullet(Coordinate(0,0), game->rM->getTexture("fire"), Rect<float>(0,0, 128, 128), 1);
    bull->getAnimation()->addAnimation("fireIdle", Coordinate(0, 0), 2, 0.5f);
    bull->getAnimation()->setOrigin(Coordinate(184,98));
    bull->getAnimation()->initAnimator();
    bull->getAnimation()->changeAnimation("fireIdle", false);
    
    gunArm->setAttack(bull);
    
    bullets = new std::vector<Bullet*>();
    
    rath->addGun(gunArm);
    rectangle.setSize(sf::Vector2f(128,128));
}

void LevelState::Update(){
    
    level->enemyAI(rath);
    if(level->getCrystal()->collision(rath->getHitbox())){
        level->getCrystal()->setTouched();
    }
}

void LevelState::Input(){
    rath->getState()->update();
    Coordinate coor = Coordinate(Game::Instance()->mouse->hitbox->left, Game::Instance()->mouse->hitbox->top);
    float mouseAng = tri->angleWindow(coor);
    rath->getCurrentGun()->getAnimation()->setRotation(mouseAng);
    rath->getCurrentGun()->getBullet()->getAnimation()->setRotation(mouseAng-90);
    
    Coordinate newPos = Coordinate(rath->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().left, rath->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().top);
    rath->getCurrentGun()->getBullet()->setPosition(newPos);
    rectangle.setPosition(rath->getCurrentGun()->getBullet()->getHitbox()->hitbox->left,rath->getCurrentGun()->getBullet()->getHitbox()->hitbox->top);
        
    if(Game::Instance()->iM->isActive("player-up-left")){ 
        if(level->map->putHitbox(rath)==true){
            colision='q'; 
            rath->move(1,1);
        }
        if(level->map->putHitbox(rath)==false && colision!='q'){
            rath->move(-1,-1);
            colision='z';
        } 
        if(direcNow!='l'){
            rath->getAnimation()->changeAnimation("correrIzquierda", false);
        }
        direcX='l';
        direcNow='l';
        mov=true;
    }else if(Game::Instance()->iM->isActive("player-up-right")){
        if(level->map->putHitbox(rath)==true){
            colision='w'; 
            rath->move(-1,1);
        }
        if(level->map->putHitbox(rath)==false && colision!='w'){
            rath->move(1,-1);
            colision='z';
        } 
        if(direcNow!='r'){
            rath->getAnimation()->changeAnimation("correrDerecha", false);
        }
        direcX='r';
        direcNow='r';
        mov=true;
    }else if(Game::Instance()->iM->isActive("player-down-left")){ 
        if(level->map->putHitbox(rath)==true){
            colision='r'; 
            rath->move(1,-1);
        }
        if(level->map->putHitbox(rath)==false && colision!='r'){
            rath->move(-1,1);
            colision='z';
        } 
        if(direcNow!='l'){
            rath->getAnimation()->changeAnimation("correrIzquierda", false);
        }
        direcX='l';
        direcNow='l';
        mov=true;
    }else if(Game::Instance()->iM->isActive("player-down-right")){
        if(level->map->putHitbox(rath)==true){
            colision='t'; 
            rath->move(-1,-1);
        }
        if(level->map->putHitbox(rath)==false && colision!='t'){
            rath->move(1,1);
            colision='z';
        } 
        if(direcNow!='r'){
            rath->getAnimation()->changeAnimation("correrDerecha", false);
        }
        direcX='r';
        direcNow='r';
        mov=true;
    }
    
    else if (Game::Instance()->iM->isActive("player-up")){
        if(level->map->putHitbox(rath)==true){
            colision='a'; 
            rath->move(0,1);
        }
        if(level->map->putHitbox(rath)==false && colision!='a'){
            rath->move(0,-1);
            colision='z';
        }
        if(direcNow!='u'){
            rath->getAnimation()->changeAnimation("correrArriba", false);
        }
        direcNow='u';
        mov=true;
    }else if (Game::Instance()->iM->isActive("player-down")){
        if(level->map->putHitbox(rath)==true){
            colision='b'; 
            rath->move(0,-1);
        }
        if(level->map->putHitbox(rath)==false && colision!='b'){
            rath->move(0,1);
            colision='z';
        }
        if(direcX=='r' && direcNow!='d'){
            rath->getAnimation()->changeAnimation("correrDerecha", false);  
            mov=true;
            direcNow='d';
        } else if(direcX=='l' && direcNow!='l'){
            rath->getAnimation()->changeAnimation("correrIzquierda", false);
            mov=true;
            direcNow='d';
        }
    }else if (Game::Instance()->iM->isActive("player-left")){
        if(level->map->putHitbox(rath)==true){
            colision='i'; 
            rath->move(1,0);
        }
        if(level->map->putHitbox(rath)==false && colision!='i'){
            rath->move(-1,0);
            colision='z';
        }
        if(direcNow!='l'){
            rath->getAnimation()->changeAnimation("correrIzquierda", false);
        }
        direcX='l';
        direcNow='l';
        mov=true;
    }else if (Game::Instance()->iM->isActive("player-right")){
        if(level->map->putHitbox(rath)==true){
            colision='d'; 
            rath->move(-1,0);
        }
        if(level->map->putHitbox(rath)==false && colision!='d'){
            rath->move(1,0);
            colision='z';
        }        
        if(direcNow!='r'){
            rath->getAnimation()->changeAnimation("correrDerecha", false);
        }
        direcX='r';
        direcNow='r';
        mov=true;
    }else if (Game::Instance()->iM->isActive("player-Lclick")){
        if(mouseAng<315 && mouseAng>225 && ata == false){
                //derecha BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueDerecha", true);
                ata=true;
            }
            if(mouseAng<225 && mouseAng>135 && ata == false){
                //arriba BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueArriba", true);
                ata=true;
            }
            if(mouseAng<135 && mouseAng>45 && ata == false){
                //izquierda BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueIzquierda", true);
                ata=true;
            }
            if(mouseAng<45 || mouseAng>315 && ata == false){
                //abajo BIEN
                rath->weaponAttack();
                rath->getAnimation()->changeAnimation("ataqueAbajo", true);
                ata=true;
            }
    } 
    if(!Game::Instance()->iM->isActive("player-up") && !Game::Instance()->iM->isActive("player-down") && 
        !Game::Instance()->iM->isActive("player-left") && !Game::Instance()->iM->isActive("player-right") && mov == true){
        rath->getAnimation()->changeAnimation("idle", false);
        mov=false;
        direcNow='i';
    }
    if(ata==true){
        rath->getAnimation()->queueAnimation("idle", false);
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        ata=false;
    }
    if(Game::Instance()->iM->isActive("player-Rclick")){
        instanceBullet(rath->getCurrentGun()->getBullet());
    }
    
    if (Game::Instance()->iM->isActive("console")) Game::Instance()->console->toggleActive();
    //if (Game::Instance()->iM->isActive("text")) 
}

void LevelState::Render(){
    
    rath->getAnimation()->updateAnimator();
    rath->getCurrentGun()->getBullet()->getAnimation()->updateAnimator();
    
    Coordinate inc(rath->getState()->getIC());
    
    rath->setPosition(Coordinate(inc.x, inc.y));
    
    /***RENDER***/
    Game::Instance()->cameraView.setCenter(rath->getCoordinate()->x, rath->getCoordinate()->y);
    Game::Instance()->window->setView(Game::Instance()->cameraView);
    
    level->drawAll();
    
    level->map->putHitbox(rath);
    
    Game::Instance()->screenView.setCenter(rath->getCoordinate()->x, rath->getCoordinate()->y);
    Game::Instance()->window->draw(*rath->getAnimation()->getSprite());
    Game::Instance()->window->draw(*rath->getCurrentGun()->getAnimation()->getSprite());
    
    if(bullets->size() > 0){
        for(int x = 0; x < bullets->size(); x++){
            Game::Instance()->window->draw(*bullets->at(x)->getAnimation()->getSprite());
            for(int y = 0;y < level->getEnemys()->size(); y++){
                std::cout<<bullets->at(x)->getHitbox()->hitbox->left<<"\n";

                if(bullets->at(x)->getHitbox()->checkCollision(level->getEnemys()->at(y)->getHitbox())){
                    level->getEnemys()->at(y)->damage(rath->getCurrentGun()->getDamage());
                }
            }
        }
    }
    Game::Instance()->window->draw(rectangle);
    Game::Instance()->screenView.setCenter(rath->getCoordinate()->x, rath->getCoordinate()->y); //ToDo: inutil
    Game::Instance()->window->setView(Game::Instance()->window->getDefaultView());
    
    
    
    
    Game::Instance()->console->drawConsole();
}

void LevelState::CleanUp(){
    
}

void LevelState::instanceBullet(Bullet *bul){
    bullets->push_back(bul);
}
