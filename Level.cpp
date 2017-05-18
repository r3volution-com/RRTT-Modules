#include "Level.h"
#include "Game.h"

Level::Level(int numLevel) {
    //Guardamos el nivel a cargar
    level = numLevel;
    enemigosCaidos = 0;
    
    std::ostringstream path;
    path << "resources/lvl" << numLevel << ".json";
    
    std::ifstream i(path.str());
    std::ostringstream text;
    text << i.rdbuf();
    //std::cout << text.str() << "\n";
    //i >> j;
    j = json::parse(text.str());
    
    enemys = new std::vector<Enemy*>();
    respawn = new std::vector<Coordinate*>();

    showIterationNpc = false;
    
    actualRespawn = 0;
    
    Init();
}

Level::~Level(){
    delete map;
    delete note;
    delete crystal;
    //delete level;
    
    map = NULL;
    note = NULL;
    crystal = NULL;
    boss = NULL;
    //level = NULL;
}

void Level::Init(){
    Game *game = Game::Instance();
    
    //Cargamos los recursos
    for (int i=0; i<j["resources"].size(); i++){
        game->rM->loadTexture(j["resources"].at(i)["name"].get<std::string>(), j["resources"].at(i)["path"].get<std::string>().c_str());
    }
    
    //Cargamos los spawns
    for (int i=0; i<j["spawn_points"].size(); i++){
        respawn->push_back(new Coordinate(j["spawn_points"].at(i)["x"], j["spawn_points"].at(i)["y"]));
    }
    
    //Cargamos el mapa
    map = new Map(j["map"].get<std::string>().c_str());
    
    //Cargamos los enemigos
    for (int i=0; i<j["enemys"].size(); i++){
        Enemy *enemy = new Enemy(Coordinate(j["enemys"].at(i)["position"]["x"],j["enemys"].at(i)["position"]["y"]), 
                Coordinate(j["enemys"].at(i)["size"]["w"], j["enemys"].at(i)["size"]["h"]), j["enemys"].at(i)["speed"]);
        enemy->setType(j["enemys"].at(i)["type"]);
        enemy->setAnimations(game->rM->getTexture(j["enemys"].at(i)["sprite"]["texture"].get<std::string>()), 
                Rect<float>(j["enemys"].at(i)["sprite"]["rect"]["x"],j["enemys"].at(i)["sprite"]["rect"]["y"], j["enemys"].at(i)["sprite"]["rect"]["w"], j["enemys"].at(i)["sprite"]["rect"]["h"]));
        enemy->setMaxHP(j["enemys"].at(i)["hp"]);
        enemy->setDistanceEnemyHome(j["enemys"].at(i)["distanceToHome"]);
        enemy->setDistancePlayerEnemy(j["enemys"].at(i)["distanceToPlayer"]);
        enemy->setInitialDmg(j["enemys"].at(i)["damage"]);
        enemy->setHitCooldown(new Time(j["enemys"].at(i)["hitCooldown"].get<float>()));
        if (j["enemys"].at(i)["bleed"] == true) enemy->setBlood(game->rM->getTexture("sangre"));
        
        if (j["enemys"].at(i)["type"] == 2){
            enemy->SetFlashRange(j["enemys"].at(i)["extra"]["flashRange"]);
            enemy->setFlashCooldown(new Time(j["enemys"].at(i)["extra"]["flashCooldown"].get<float>()));
        } else if (j["enemys"].at(i)["type"] == 3){
            enemy->setFreeze(j["enemys"].at(i)["extra"]["freeze"]);
        }
        
        enemys->push_back(enemy);
    }
    
    if (j.find("boss") != j.end()) {
        boss = new Boss(Coordinate(j["boss"]["position"]["x"],j["boss"]["position"]["y"]), 
                Coordinate(j["boss"]["size"]["w"], j["boss"]["size"]["h"]), j["boss"]["speed"]);
        boss->setAnimations(game->rM->getTexture(j["boss"]["sprite"]["texture"]), 
                Rect<float>(j["boss"]["sprite"]["rect"]["x"], j["boss"]["sprite"]["rect"]["y"], j["boss"]["sprite"]["rect"]["w"], j["boss"]["sprite"]["rect"]["h"]));
        boss->setMaxHP(j["boss"]["hp"]);
        boss->setDistanceEnemyHome(j["boss"]["distanceToHome"]);
        boss->setDistancePlayerEnemy(j["boss"]["distanceToPlayer"]);
        boss->setInitialDmg(j["boss"]["damage"]);
        boss->setHitCooldown(new Time(j["boss"]["hitCooldown"].get<float>()));
        boss->SetFlashRange(j["boss"]["flashRange"]);
        boss->setFlashCooldown(new Time(j["boss"]["flashCooldown"].get<float>()));
        boss->setStateClock(new Time(j["boss"]["changeStateTimer"].get<float>()));
        srand (time(NULL));
        for (int i=0; i<j["boss"]["nStates"];i++){
            if (i >= j["boss"]["states"]["from"] && i <= j["boss"]["states"]["to"])
                boss->addState(i);
            else
                boss->addRandomState(j["boss"]["states"]["from"], j["boss"]["states"]["to"]);
        }
        for (int i=0; i<j["boss"]["guns"].size(); i++){
            Gun *gunArm = new Gun(j["boss"]["guns"].at(i)["cooldown"].get<float>());
            gunArm->setAnimation(game->rM->getTexture(j["boss"]["guns"].at(i)["sprite"]["texture"]), 
                    Rect<float> (j["boss"]["guns"].at(i)["sprite"]["rect"]["x"], j["boss"]["guns"].at(i)["sprite"]["rect"]["y"], j["boss"]["guns"].at(i)["sprite"]["rect"]["w"], j["boss"]["guns"].at(i)["sprite"]["rect"]["h"]));
            gunArm->getAnimation()->setOrigin(Coordinate(56,34)); //ToDo: campo en json?

            Bullet *bull = new Bullet(Coordinate(j["boss"]["guns"].at(i)["bullet"]["size"]["w"], j["boss"]["guns"].at(i)["bullet"]["size"]["h"]), 
                    j["boss"]["guns"].at(i)["bullet"]["duration"], j["boss"]["guns"].at(i)["bullet"]["type"]);
            bull->setAnimation(game->rM->getTexture(j["boss"]["guns"].at(i)["bullet"]["sprite"]["texture"]), 
                    Rect<float>(j["boss"]["guns"].at(i)["bullet"]["sprite"]["rect"]["x"], j["boss"]["guns"].at(i)["bullet"]["sprite"]["rect"]["x"], j["boss"]["guns"].at(i)["bullet"]["sprite"]["rect"]["x"], j["boss"]["guns"].at(i)["bullet"]["sprite"]["rect"]["x"]));
            for (int k=0; k<j["boss"]["guns"].at(i)["bullet"]["animations"].size(); k++){
                bull->getAnimation()->addAnimation(j["boss"]["guns"].at(i)["bullet"]["animations"].at(k)["name"].get<std::string>(), 
                        Coordinate(j["boss"]["guns"].at(i)["bullet"]["animations"].at(k)["position"]["x"], j["boss"]["guns"].at(i)["bullet"]["animations"].at(k)["position"]["y"]), 
                        j["boss"]["guns"].at(i)["bullet"]["animations"].at(k)["nSprites"], j["boss"]["guns"].at(i)["bullet"]["animations"].at(k)["duration"]);
            }
            bull->getAnimation()->initAnimator();
            bull->getAnimation()->changeAnimation(j["boss"]["guns"].at(i)["bullet"]["animations"].at(0)["name"], false);
            bull->setDamage(j["boss"]["guns"].at(i)["bullet"]["damage"]);
            bull->getAnimation()->setOrigin(Coordinate(184,98));//ToDo: campo en json?

            gunArm->setAttack(bull);
            
            boss->addGun(gunArm);
        }
    }
    
    //Cargamos las notas
    if (j.find("notes") != j.end()) {
        for (int i=0; i<j["boss"]["guns"].size(); i++){
            note = new Note(game->rM->getTexture("gui-tileset"), Rect<float>(325, 920, 128, 128), game->rM->getTexture("pergamino"), Rect<float>(0, 0, 608, 488), game->rM->getFont("font"));
            note->setPosition(Coordinate(1950, 13850));
            note->setBackgroundPosition(Coordinate(350, 125));
            note->setText("El", sf::Color::Black, sf::Color::White, 1, 25);
        }
    }
    
    if (j.find("crystals") != j.end()) {
        //Cargamos los cristales
        crystal = new Crystals(game->rM->getTexture("gui-tileset"), Rect<float>(300, 920, 174, 290));
        crystal->setPosition(Coordinate(3000, 3000));
    }
    
    if (j.find("npcs") != j.end()) {
        
        
    }
    //Si estamos en el primer nivel
    if(level==1){
        /* NPC */
        npc = new NPC(Coordinate(4500,13300), Coordinate(128, 128), 2, "Jose");
        npc->setSprite(game->rM->getTexture("gui-tileset"), Rect<float>(0,920,128,128));
        npc->getAnimation()->addAnimation("idle", Coordinate(0,0), 4, 1.0f);
        npc->getAnimation()->initAnimator();
        npc->getAnimation()->changeAnimation("idle", false);
        //aldeano->loadAnimation(tex, Coordinate(0, 128), 3, 0.1f);
        npc->addSentence("El bosque esta en llamas!!\n\nPulsa E para continuar", new Coordinate(2300, 3800));
        npc->addSentence("Sera mejor que huyas muchacho no te aguarda nada bueno ahi.\n\nPulsa E para continuar", new Coordinate(20, 520));
        npc->addSentence("Un momento, creo que tu cara me suena...\n\nPulsa E para continuar", new Coordinate(20, 520));
        
        keyIterationNpc = new Text("Pulsa la tecla \"E\" para interacctuar con el NPC cuando estes cerca", Coordinate(310,600), game->rM->getFont("font"), false);
        keyIterationNpc->setTextStyle(sf::Color::Black, 25);
        keyIterationNpc->setOutlineStyle(sf::Color::White, 1);
        
        /* MURO */
        fuego = new Entity(Coordinate(2500,5800), Coordinate(1280, 384), 0);
        fuego->setSprite(game->rM->getTexture("gui-tileset"), Rect<float>(0,525,1280,384));
        fuego->getAnimation()->addAnimation("idle", Coordinate(0,0), 4, 1.0f);
        fuego->getAnimation()->initAnimator();
        fuego->getAnimation()->changeAnimation("idle", false);
        
        fuego2 = new Entity(Coordinate(3425,2000), Coordinate(1280, 384), 0);
        fuego2->setSprite(game->rM->getTexture("gui-tileset"), Rect<float>(0,525,1280,384));
        fuego2->getAnimation()->addAnimation("idle", Coordinate(0,0), 4, 1.0f);
        fuego2->getAnimation()->initAnimator();
        fuego2->getAnimation()->changeAnimation("idle", false);
        
        //Anyadimos la accion de hablar cuando pulsemos la E
        game->iM->addAction("interactuar", thor::Action(sf::Keyboard::Key::E, thor::Action::PressOnce));
        
        tri = new Trigonometry();
        
    }  
}

void Level::Update(Player* rath, HUD* hud){
    
    if(disNpcPlayer < 500){
        showIterationNpc = true;
    }else{
        showIterationNpc = false;
    }
    
    for (int i = 0; i<enemys->size(); i++){
        if(enemys->at(i)->getHP() > 0){
            enemys->at(i)->AI(rath, hud);
        }
    }
    if(boss->getHP() > 0){
        boss->AI(rath, hud);
    }
    
    for(int i = 0; i < enemys->size(); i++){
        if (enemys->at(i)->getHitbox()->checkCollision(rath->getCurrentGun()->getBullet()->getHitbox()) && rath->isAttacking()){
            enemys->at(i)->damage(rath->getCurrentGun()->getBullet()->getDamage());
            if(enemys->at(i)->getHP() <= 0 && enemys->at(i)->isDead() == false){
                enemys->at(i)->setPosition(100000,100000);
                enemigosCaidos++;
                enemys->at(i)->setDead(true);
            }
        }
        
        if(rath->getWeapon()->detectCollisions(enemys->at(i)->getHitbox())){
            enemys->at(i)->damage(rath->getWeapon()->getDamage());//ToDo: Meter daño a la guadaña, esta el arma ahora
            if(enemys->at(i)->getHP() <= 0 && enemys->at(i)->isDead() == false){
                enemys->at(i)->startBlood(2);
                enemigosCaidos++;
                enemys->at(i)->setDead(true);
            }
        }
        if(enemys->at(i)->getHP() <= 0 && enemys->at(i)->isDead()){
            if(enemys->at(i)->getTimeDead()->getTime() == 0){
                enemys->at(i)->setPosition(100000,100000);
            }
        }
        
    }
    if (boss->getHitbox()->checkCollision(rath->getCurrentGun()->getBullet()->getHitbox()) && rath->isAttacking()){
        boss->damage(rath->getCurrentGun()->getBullet()->getDamage());
        hud->changeLifeBoss(boss->getHP());
        if(boss->getHP() <= 0){
            boss->setPosition(100000,100000); //ToDo PabloL: Poner un setActive para bloquear la ia cuando muera en Enemy
        }
   }
    if(rath->getWeapon()->detectCollisions(boss->getHitbox())){
        boss->damage(rath->getWeapon()->getDamage());
        hud->changeLifeBoss(boss->getHP());
        if(boss->getHP() <= 0){
            boss->setPosition(10000,10000); //ToDo PabloL: Poner un setActive para bloquear la ia cuando muera en Enemy
        }
    }
   if (boss->getCurrentGun()->getBullet()->getHitbox()->checkCollision(rath->getHitbox()) && boss->isAttacking()){
        rath->damage(boss->getCurrentGun()->getBullet()->getDamage());
        hud->changeLifePlayer(rath->getHP());
   }
    
    /* COLISION MUROS*/
    if(rath->collision(fuego->getHitbox()) && enemigosCaidos < enemys->size()){
        rath->move(0,1);
    }else if(rath->collision(fuego->getHitbox()) && enemigosCaidos >= enemys->size() && sinSalida==false){
        rath->move(0,-1);
    }
    
    if(rath->collision(fuego2->getHitbox())){
        rath->move(0,1);
    }  
    
    if(play==true){
       Game::Instance()->rM->getMusic("boss")->getMusic()->play();
       play=false;
    }
}

void Level::Input(Player* rath, HUD* hud){
    int salir = 0;
    
    //NPC
    if(Game::Instance()->iM->isActive("interactuar") && rath->collision(npc->getHitbox())){
        salir = npc->nextSentence();
   
        if(salir==1){
            setMuestra(true);
            //Creamos la caja que va a contener el texto
            hud->setTextLayer(Coordinate(0,420), Rect <float> (0, 222, 1280, 300),Game::Instance()->rM->getTexture("gui-tileset"));
            //Posicionamos lo que va a decir el npc
            hud->setTLayerText(npc->getCurrentSentenceText(), 25, 520);
            //Le damos estilo a lo que va a decir el npc
            hud->setTLayerTextParams(20, sf::Color::White, sf::Color::Red);

            //Posicionamos el nombre del npc
            hud->setTLayerTalker(npc->getName(), 1125, 435);
            
        }else{
            setMuestra(false);
            moverse = true;
            Game::Instance()->getLevelState()->setPaused(true);
        }  
    }
        //NOTA
        if(Game::Instance()->iM->isActive("interactuar") && rath->collision(note->getHitbox()) && showText==false){
            showText = true;
            note->setTaken();
        }else if(Game::Instance()->iM->isActive("interactuar") && rath->collision(note->getHitbox()) && showText==true){
            showText = false;
        }
        
        
        //Anyadir comprobacion de hitbox del personaje con el npc
        //if(rath->collision(npc->getHitbox())){
        //}
}

void Level::Render(){
    //Dibujamos todos los elementos
    map->dibujarMapa(Game::Instance()->window);
    
    if(!note->getTaken()){
       Game::Instance()->window->draw(*note->getNoteSprite()->getSprite());
    }
      
    /*if(!crystal->getTouched()){
       Game::Instance()->window->draw(*crystal->getCrystalSprite()->getSprite());
    }*/
    for (int i = 0; i<enemys->size(); i++){
        Coordinate inc(enemys->at(i)->getState()->getIC());
        //cout << inc;
        enemys->at(i)->getAnimation()->updateAnimator();
        enemys->at(i)->updatePosition(inc.x, inc.y);
        Game::Instance()->window->draw(*enemys->at(i)->getAnimation()->getSprite());
        enemys->at(i)->drawBlood();
    }
    
    boss->getCurrentGun()->getBullet()->getAnimation()->updateAnimator();
    if (!boss->getCurrentGun()->getBulletLifetime()->isExpired()){
        Game::Instance()->window->draw(*boss->getCurrentGun()->getBullet()->getAnimation()->getSprite());
    } else if (boss->isAttacking()){
        boss->attackDone();
    }
    
    Coordinate inc2(boss->getState()->getIC());
    boss->getAnimation()->updateAnimator();
    Game::Instance()->window->draw(*boss->getCurrentGun()->getAnimation()->getSprite());
    boss->updatePosition(inc2.x, inc2.y);
    
    Coordinate inc3(npc->getState()->getIC());
    
    npc->updatePosition(inc3.x, inc3.y);
    
    Game::Instance()->window->draw(*npc->getAnimation()->getSprite());
    
    /* MURO FUEGO */
    if(enemigosCaidos < enemys->size()){
        Game::Instance()->window->draw(*fuego->getAnimation()->getSprite());
    }else if(sinSalida == false){
        Game::Instance()->rM->getMusic("Main")->getMusic()->stop();
        Game::Instance()->window->draw(*fuego->getAnimation()->getSprite());
    }else if(Game::Instance()->getLevelState()->getRath()->getCoordinate()->y < 5700){
        sinSalida = false;
        play = true;
    }
    
    Game::Instance()->window->draw(*fuego2->getAnimation()->getSprite());
    
    Game::Instance()->window->draw(*boss->getAnimation()->getSprite());
}

void Level::setRespawn(int resp){
    respawn->at(resp);
}
