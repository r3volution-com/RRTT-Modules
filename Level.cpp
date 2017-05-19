#include "Level.h"
#include "Game.h"

Level::Level(Player* r, HUD* h) {
    //Copiamos player y hud para usarlos despues
    rath = r;
    hud = h;
    
    //Inicializamos vectores
    enemys = new std::vector<Enemy*>();
    respawn = new std::vector<Coordinate*>();
    npcs = new std::vector<NPC*>();
    notes = new std::vector<Note*>();
    crystals = new std::vector<Crystal*>();
    preObstacles = new std::vector<Obstacle*>();
    postObstacles = new std::vector<Obstacle*>();
    tri = new Trigonometry();
    
    //Inicializamos variables
    enemigosCaidos = 0;
    actualRespawn = 0;
    npcMoving = -1;
    paused = false;
    showNPCText = false;
    showNoteText = false;
    bossZone = false;
}

Level::~Level(){
    //ToDo: Borrar tri y los vectores
}

void Level::Init(int numLevel){
    Game *game = Game::Instance();
    
    //Guardamos el nivel cargado
    level = numLevel;
    
    //Cargamos el JSON del nivel correspondiente
    std::ostringstream path;
    path << "resources/lvl" << numLevel << ".json";
    std::ifstream i(path.str());
    std::ostringstream text;
    text << i.rdbuf();
    j = json::parse(text.str());
    
    //Cargamos los recursos
    for (int i=0; i<j["resources"].size(); i++){
        game->rM->loadTexture(j["resources"].at(i)["name"].get<std::string>(), j["resources"].at(i)["path"].get<std::string>().c_str());
    }
    
    //Cargamos el mapa
    map = new Map(j["map"].get<std::string>().c_str(), j["tileset"].get<std::string>().c_str());
    
    //Cargamos los spawns
    if (j.find("spawn_points") != j.end()) {
        for (int i=0; i<j["spawn_points"].size(); i++){
            respawn->push_back(new Coordinate(j["spawn_points"].at(i)["x"], j["spawn_points"].at(i)["y"]));
        }
        rath->setPosition(*getRespawn()); 
    }
    
    //Cargamos los enemigos
    if (j.find("enemys") != j.end()) {
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
    }
    
    //Cargamos el jefe
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
        for (int i=j["boss"]["states"]["to"].get<int>(); i<=j["boss"]["states"]["from"].get<int>(); i++){
            boss->addState(i);
        }
        int fixedStates = j["boss"]["states"]["to"].get<int>()-j["boss"]["states"]["from"].get<int>();
        for (int i=fixedStates; i<j["boss"]["nStates"];i++){
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
                    Rect<float>(j["boss"]["guns"].at(i)["bullet"]["sprite"]["rect"]["x"], j["boss"]["guns"].at(i)["bullet"]["sprite"]["rect"]["y"], j["boss"]["guns"].at(i)["bullet"]["sprite"]["rect"]["w"], j["boss"]["guns"].at(i)["bullet"]["sprite"]["rect"]["h"]));
            for (int k=0; k<j["boss"]["guns"].at(i)["bullet"]["animations"].size(); k++){
                bull->getAnimation()->addAnimation(j["boss"]["guns"].at(i)["bullet"]["animations"].at(k)["name"].get<std::string>(), 
                        Coordinate(j["boss"]["guns"].at(i)["bullet"]["animations"].at(k)["position"]["x"], j["boss"]["guns"].at(i)["bullet"]["animations"].at(k)["position"]["y"]), 
                        j["boss"]["guns"].at(i)["bullet"]["animations"].at(k)["nSprites"], j["boss"]["guns"].at(i)["bullet"]["animations"].at(k)["duration"]);
            }
            bull->getAnimation()->initAnimator();
            bull->getAnimation()->changeAnimation(j["boss"]["guns"].at(i)["bullet"]["animations"].at(0)["name"].get<std::string>(), false);
            bull->setDamage(j["boss"]["guns"].at(i)["bullet"]["damage"]);
            bull->getAnimation()->setOrigin(Coordinate(300,64));//ToDo: campo en json?

            gunArm->setAttack(bull);
            
            boss->addGun(gunArm);
        }
    }
    
    //Cargamos las notas
    if (j.find("notes") != j.end()) {
        for (int i=0; i<j["notes"].size(); i++){
            Note *note = new Note(game->rM->getTexture(j["notes"].at(i)["noteSprite"]["texture"].get<std::string>()), 
                    Rect<float>(j["notes"].at(i)["noteSprite"]["rect"]["x"], j["notes"].at(i)["noteSprite"]["rect"]["y"], j["notes"].at(i)["noteSprite"]["rect"]["w"], j["notes"].at(i)["noteSprite"]["rect"]["h"]), 
                    game->rM->getTexture(j["notes"].at(i)["paperSprite"]["texture"].get<std::string>()), 
                    Rect<float>(j["notes"].at(i)["paperSprite"]["rect"]["x"], j["notes"].at(i)["paperSprite"]["rect"]["y"], j["notes"].at(i)["paperSprite"]["rect"]["w"], j["notes"].at(i)["paperSprite"]["rect"]["h"]), 
                    game->rM->getFont(j["notes"].at(i)["font"].get<std::string>()));
            note->setPosition(Coordinate(j["notes"].at(i)["notePosition"]["x"], j["notes"].at(i)["notePosition"]["y"]));
            note->setBackgroundPosition(Coordinate(j["notes"].at(i)["paperPosition"]["x"], j["notes"].at(i)["paperPosition"]["y"]));
            note->setText(j["notes"].at(i)["text"].get<std::string>(), sf::Color::Black, sf::Color::White, 1, 25);
            
            notes->push_back(note);
        }
    }
    
    //Cargamos los cristales
    if (j.find("crystals") != j.end()) {
        for (int i=0; i<j["crystals"].size(); i++){
            Crystal *crystal = new Crystal(game->rM->getTexture(j["crystals"].at(i)["sprite"]["texture"].get<std::string>()),
                    Rect<float>(j["crystals"].at(i)["sprite"]["rect"]["x"], j["crystals"].at(i)["sprite"]["rect"]["y"], j["crystals"].at(i)["sprite"]["rect"]["w"], j["crystals"].at(i)["sprite"]["rect"]["h"]));
            crystal->setPosition(Coordinate(j["crystals"].at(i)["position"]["x"], j["crystals"].at(i)["position"]["y"]));
            crystals->push_back(crystal);
        }
    }
    
    //Cargamos los NPC
    if (j.find("npcs") != j.end()) {
        for (int i=0; i<j["npcs"].size(); i++){
            NPC *npc = new NPC(Coordinate(j["npcs"].at(i)["position"]["x"],j["npcs"].at(i)["position"]["y"]),
                    Coordinate(j["npcs"].at(i)["size"]["w"], j["npcs"].at(i)["size"]["h"]),
                    j["npcs"].at(i)["speed"],
                    j["npcs"].at(i)["name"].get<std::string>());
            npc->setSprite(game->rM->getTexture(j["npcs"].at(i)["sprite"]["texture"].get<std::string>()),
                    Rect<float>(j["npcs"].at(i)["sprite"]["rect"]["x"],j["npcs"].at(i)["sprite"]["rect"]["y"],j["npcs"].at(i)["sprite"]["rect"]["w"],j["npcs"].at(i)["sprite"]["rect"]["h"]));
            for (int x=0; x<j["npcs"].at(i)["animations"].size(); x++){
                npc->getAnimation()->addAnimation(j["npcs"].at(i)["animations"].at(x)["name"].get<std::string>(),
                        Coordinate(j["npcs"].at(i)["animations"].at(x)["position"]["x"], j["npcs"].at(i)["animations"].at(x)["position"]["y"]),
                        j["npcs"].at(i)["animations"].at(x)["nSprites"],
                        j["npcs"].at(i)["animations"].at(x)["duration"]);
            }
            npc->getAnimation()->initAnimator();
            npc->getAnimation()->changeAnimation(j["npcs"].at(i)["animations"].at(0)["name"].get<std::string>(), false);
            for (int x=0; x<j["npcs"].at(i)["phrase"].size(); x++){
                npc->addSentence(j["npcs"].at(i)["phrase"].at(x)["text"].get<std::string>(), 
                        new Coordinate(j["npcs"].at(i)["phrase"].at(x)["position"]["x"], j["npcs"].at(i)["phrase"].at(x)["position"]["y"]));
            }
            npcs->push_back(npc);
        }
        //Creamos la caja que va a contener el texto
        hud->setTextLayer(Coordinate(0,420), Rect <float> (0, 222, 1280, 300),Game::Instance()->rM->getTexture("gui-tileset"));
        //Le damos estilo a lo que va a decir el npc
        hud->setTLayerTextParams(20, sf::Color::White, sf::Color::Red);
        //Key
        keyIterationNpc = new Text("Pulsa la tecla \"E\" para interacctuar con el NPC", Coordinate(310,600), game->rM->getFont("font"), false);
        keyIterationNpc->setTextStyle(sf::Color::Black, 25);
        keyIterationNpc->setOutlineStyle(sf::Color::White, 1);
    }
    
    //Cargamos obstaculos anteriores a la zona del jefe
    if (j.find("preBossObstacles") != j.end()) {
        for (int i=0; i<j["preBossObstacles"].size(); i++){
            Obstacle *o = new Obstacle(
                    Coordinate(j["preBossObstacles"].at(i)["position"]["x"],j["preBossObstacles"].at(i)["position"]["y"]), 
                    Coordinate(j["preBossObstacles"].at(i)["size"]["w"], j["preBossObstacles"].at(i)["size"]["h"]),
                    game->rM->getTexture(j["preBossObstacles"].at(i)["sprite"]["texture"]), 
                    Rect<float>(j["preBossObstacles"].at(i)["sprite"]["rect"]["x"],j["preBossObstacles"].at(i)["sprite"]["rect"]["y"],j["preBossObstacles"].at(i)["sprite"]["rect"]["w"],j["preBossObstacles"].at(i)["sprite"]["rect"]["h"]));
            o->setActive(true);
            
            preObstacles->push_back(o);
        }
    }
    
    //Cargamos obstaculos posteriores a la zona del jefe
    if (j.find("postBossObstacles") != j.end()) {
        for (int i=0; i<j["postBossObstacles"].size(); i++){
            Obstacle *o = new Obstacle(
                    Coordinate(j["postBossObstacles"].at(i)["position"]["x"],j["postBossObstacles"].at(i)["position"]["y"]), 
                    Coordinate(j["postBossObstacles"].at(i)["size"]["w"], j["postBossObstacles"].at(i)["size"]["h"]),
                    game->rM->getTexture(j["postBossObstacles"].at(i)["sprite"]["texture"]), 
                    Rect<float>(j["postBossObstacles"].at(i)["sprite"]["rect"]["x"],j["postBossObstacles"].at(i)["sprite"]["rect"]["y"],j["postBossObstacles"].at(i)["sprite"]["rect"]["w"],j["postBossObstacles"].at(i)["sprite"]["rect"]["h"]));
            o->setActive(true);
            
            postObstacles->push_back(o);
        }
    }
}

void Level::Update(){
    if (!paused){
        /*EJECUTA LAS IAs*/
        for (int i = 0; i<enemys->size(); i++){
            if(enemys->at(i)->getHP() > 0){
                enemys->at(i)->AI(rath, hud);
            }
        }
        if(boss->getHP() > 0){
            boss->AI(rath, hud);
        }
        /*Actualiza la posicion del jefe*/
        if(boss->getCurrentGun()->getBullet()->getType() != 2){
            float angleBoss = tri->angle(*boss->getCoordinate(),*rath->getCoordinate());
            Coordinate newBoss = Coordinate(boss->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().left, 
                    boss->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().top);
            boss->getCurrentGun()->update(newBoss, angleBoss);
        }else{
            Coordinate newBoss = Coordinate(
                    boss->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().left+boss->getCurrentGun()->getBullet()->getHitbox()->hitbox->width/2, 
                    boss->getCurrentGun()->getBullet()->getAnimation()->getSprite()->getGlobalBounds().top+boss->getCurrentGun()->getBullet()->getHitbox()->hitbox->height/2);
            boss->getCurrentGun()->update(newBoss,boss->getAngle());
        }
        /*Comprueba colisiones*/
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
        
        if(boss->getOnRange() && !seeBoss){
            actualRespawn++;
            seeBoss = true;
        }
        
        //NPC ToDo: hitbox entre pj y npc
        /*NPC Distance Check*/
        if (j.find("npcs") != j.end()) {
            for (int i=0; i<npcs->size(); i++){
                int disNpcPlayer = tri->distance(*rath->getCoordinate(), *npcs->at(i)->getCoordinate());
                if(disNpcPlayer < 300) npcs->at(i)->setInRange(true);
                else npcs->at(i)->setInRange(false);
            }
        }
        //PreBossObstacles
        if (j.find("preBossObstacles") != j.end()) {
            if(rath->getCoordinate()->y < 5700){
                bossZone = true;
                play = true;
            } else {
                bossZone = false;
                play = false;
            }
            if (enemigosCaidos == enemys->size()){
                if (bossZone) {
                    for (int i=0; i<preObstacles->size(); i++){
                        preObstacles->at(i)->setActive(true);
                    }
                } else {
                    for (int i=0; i<preObstacles->size(); i++){
                        preObstacles->at(i)->setActive(false);
                    }
                }
            }
        }
        /*Musica del boss*/
        if(play==true){
           Game::Instance()->rM->getMusic("boss")->getMusic()->play();
           play=false;
        }
    } else {
        if (j.find("npcs") != j.end()) {
            if (npcMoving != -1){
                if(npcs->at(npcMoving)->getCoordinate()->y < 20000){
                    npcs->at(npcMoving)->move(0,20);
                }
                int disNpcPlayer = tri->distance(*rath->getCoordinate(), *npcs->at(npcMoving)->getCoordinate());
                if (disNpcPlayer > 1000){
                    paused = false;
                    Game::Instance()->getLevelState()->setPaused(false);
                }
            }
        }
    }
    
}

void Level::Input(){
    if (!paused){
        if(Game::Instance()->iM->isActive("interact")){
            //NPCs
            if (j.find("npcs") != j.end()) {
                for (int i=0; i<npcs->size(); i++){
                    if (npcs->at(i)->getRange()){
                        if(npcs->at(i)->nextSentence()){
                            showNPCText = true;
                            //Posicionamos el nombre del npc
                            hud->setTLayerTalker(npcs->at(i)->getName(), 1125, 435); 
                            //Posicionamos lo que va a decir el npc
                            hud->setTLayerText(npcs->at(i)->getCurrentSentenceText(), npcs->at(i)->getCurrentSentencePosition()->x, npcs->at(i)->getCurrentSentencePosition()->y); 
                        }else{
                            showNPCText = false;
                            npcMoving = i;
                            paused = true;
                            Game::Instance()->getLevelState()->setPaused(true);
                        }
                    }
                }
            }
            //NOTAS
            if (j.find("notes") != j.end()) {
                for (int i=0; i<notes->size(); i++){
                    if(rath->collision(notes->at(i)->getHitbox())){
                        if (!showNoteText && !notes->at(i)->getTaken()){
                            showNoteText = true;
                            notes->at(i)->setTaken();
                        } else {
                            showNoteText = false;
                        }
                    }
                }
            }
        }
    } else {
        //Si no esta pausado
    }
}

void Level::Render(){
    //ToDo: Para subir los FPS quizas podriamos hacer que solo se muestren las cosas que esten a menos de X distancia de nosotros
    //Dibujamos todos los elementos
    map->dibujarMapa(Game::Instance()->window);
    
    //Notas de texto
    if (j.find("notes") != j.end()) {
        for (int i=0; i<notes->size(); i++){
            if(!notes->at(i)->getTaken()){
               Game::Instance()->window->draw(*notes->at(i)->getNoteSprite()->getSprite());
            }
            /*Texto notas */
            if(showNoteText){
                Game::Instance()->window->setView(Game::Instance()->window->getDefaultView());
                Game::Instance()->window->draw(*notes->at(i)->getBackgroundSprite()->getSprite());
                Game::Instance()->window->draw(*notes->at(i)->getText()->getText());
                Game::Instance()->window->setView(Game::Instance()->cameraView);
            }
        }
    }
    
    //Cristales de rayos
    if (j.find("crystals") != j.end()) {
        for (int i=0; i<crystals->size(); i++){
            if(!crystals->at(i)->getTouched()){
                Game::Instance()->window->draw(*crystals->at(i)->getCrystalSprite()->getSprite());
            }
        }
    }
    
    /*NPC*/
    if (j.find("npcs") != j.end()) {
        for (int i=0; i<npcs->size(); i++){
            Coordinate inc3(npcs->at(i)->getState()->getIC());
            npcs->at(i)->updatePosition(inc3.x, inc3.y);
            Game::Instance()->window->draw(*npcs->at(i)->getAnimation()->getSprite());
            if (npcs->at(i)->getRange()){
                Game::Instance()->window->setView(Game::Instance()->window->getDefaultView());
                Game::Instance()->window->draw(*keyIterationNpc->getText());
                if(showNPCText){
                    hud->drawTextLayer();
                }
                Game::Instance()->window->setView(Game::Instance()->cameraView);
            }
        }
    }
    
    /*Enemigos*/
    for (int i = 0; i<enemys->size(); i++){
        Coordinate inc(enemys->at(i)->getState()->getIC());
        enemys->at(i)->updatePosition(inc.x, inc.y);
        enemys->at(i)->getAnimation()->updateAnimator();
        Game::Instance()->window->draw(*enemys->at(i)->getAnimation()->getSprite());
        enemys->at(i)->drawBlood();
    }
    
    /*Jefe*/
    boss->getCurrentGun()->getBullet()->getAnimation()->updateAnimator();
    Game::Instance()->window->draw(*boss->getAnimation()->getSprite());
    if (!boss->getCurrentGun()->getBulletLifetime()->isExpired()){
        Game::Instance()->window->draw(*boss->getCurrentGun()->getBullet()->getAnimation()->getSprite());
    } else if (boss->isAttacking()){
        boss->attackDone();
    }
    Coordinate inc2(boss->getState()->getIC());
    boss->updatePosition(inc2.x, inc2.y);
    boss->getAnimation()->updateAnimator();
    Game::Instance()->window->draw(*boss->getCurrentGun()->getAnimation()->getSprite());
    
    /* MURO Jefe */
    for (int i=0; i<preObstacles->size(); i++){
        if (preObstacles->at(i)->getActive()) Game::Instance()->window->draw(*preObstacles->at(i)->getAnimation()->getSprite());
    }
    for (int i=0; i<postObstacles->size(); i++){
        if (postObstacles->at(i)->getActive()) Game::Instance()->window->draw(*postObstacles->at(i)->getAnimation()->getSprite());
    }
}

int Level::colision(Hitbox *hitbox){
    for(int i = 0; i < map->getMuros()->size(); i++){
        if(hitbox->checkCollision(map->getMuros()->at(i))){
            return i;
        }
    }
    return -1;
}
