#include "Level.h"
#include "Game.h"

Level::Level(Player* r, HUD* h) {
    //Copiamos player y hud para usarlos despues
    rath = r;
    hud = h;
    
    //Inicializamos objetos
    tri = new Trigonometry();
    
    //Inicializamos variables
    level = 0;
    enemigosCaidos = 0;
    actualRespawn = 0;
    npcMoving = -1;
    distanceToLock = 0;
    seeBoss = false;
    paused = false;
    showNPCText = false;
    showNoteText = false;
    bossZone = false;
    keyIterationNpc = NULL;
    activeIA = true;
    
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
    i.close();
    
    //Cargamos los recursos
    for (int i=0; i<j["resources"].size(); i++){
        game->rM->loadTexture(j["resources"].at(i)["name"].get<std::string>(), j["resources"].at(i)["path"].get<std::string>().c_str());
    }
    
    //Cargamos el mapa
    map = new Map(j["map"].get<std::string>().c_str(), j["tileset"].get<std::string>().c_str());
    
    //Cargamos los spawns
    if (j.find("spawn_points") != j.end()) {
        for (int i=0; i<j["spawn_points"].size(); i++){
            respawn.push_back(new Coordinate(j["spawn_points"].at(i)["x"], j["spawn_points"].at(i)["y"]));
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
            enemy->setHitCooldown(j["enemys"].at(i)["hitCooldown"].get<float>());
            if (j["enemys"].at(i)["bleed"] == true) enemy->setBlood(game->rM->getTexture("sangre"));

            if (j["enemys"].at(i)["type"] == 2){
                enemy->SetFlashRange(j["enemys"].at(i)["extra"]["flashRange"]);
                enemy->setFlashCooldown(j["enemys"].at(i)["extra"]["flashCooldown"].get<float>());
            } else if (j["enemys"].at(i)["type"] == 3){
                enemy->setFreeze(j["enemys"].at(i)["extra"]["freeze"]);
            }

            enemys.push_back(enemy);
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
        boss->setHitCooldown(j["boss"]["hitCooldown"].get<float>());
        boss->SetFlashRange(j["boss"]["flashRange"]);
        boss->setFlashCooldown(j["boss"]["flashCooldown"].get<float>());
        boss->setStateClock(j["boss"]["changeStateTimer"].get<float>());
        distanceToLock = j["boss"]["distanceToLock"];
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
            gunArm->getAnimation()->setOrigin(Coordinate(j["boss"]["guns"].at(i)["origin"]["x"],j["boss"]["guns"].at(i)["origin"]["y"])); //ToDo: campo en json?

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
            bull->getAnimation()->setOrigin(Coordinate(j["boss"]["guns"].at(i)["bullet"]["origin"]["x"],j["boss"]["guns"].at(i)["bullet"]["origin"]["y"]));//ToDo: campo en json?

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
            
            notes.push_back(note);
        }
    }
    
    //Cargamos los cristales
    if (j.find("crystals") != j.end()) {
        for (int i=0; i<j["crystals"].size(); i++){
            Crystal *crystal = new Crystal(game->rM->getTexture(j["crystals"].at(i)["sprite"]["texture"].get<std::string>()),
                    Rect<float>(j["crystals"].at(i)["sprite"]["rect"]["x"], j["crystals"].at(i)["sprite"]["rect"]["y"], j["crystals"].at(i)["sprite"]["rect"]["w"], j["crystals"].at(i)["sprite"]["rect"]["h"]),
                    game->rM->getTexture(j["crystals"].at(i)["sparks"]["texture"].get<std::string>()),
                    Rect<float>(j["crystals"].at(i)["sparks"]["rect"]["x"], j["crystals"].at(i)["sparks"]["rect"]["y"], j["crystals"].at(i)["sparks"]["rect"]["w"], j["crystals"].at(i)["sparks"]["rect"]["h"]));
            crystal->setPosition(Coordinate(j["crystals"].at(i)["position"]["x"], j["crystals"].at(i)["position"]["y"]));
            for (int x=0; x < j["crystals"].at(i)["animations"].size(); x++){
                crystal->getCrystalAnimation()->addAnimation(j["crystals"].at(i)["animations"].at(x)["name"].get<std::string>(),
                        Coordinate(j["crystals"].at(i)["animations"].at(x)["position"]["x"], j["crystals"].at(i)["animations"].at(x)["position"]["y"]),
                        j["crystals"].at(i)["animations"].at(x)["nSprites"],
                        j["crystals"].at(i)["animations"].at(x)["duration"]);
            }
            
            crystal->getCrystalAnimation()->initAnimator();
            crystal->getCrystalAnimation()->changeAnimation("idle", true);
            crystal->startSparks();
            crystals.push_back(crystal);
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
            npc->setRunawayDirection(j["npcs"].at(i)["runawayDirection"]["x"], j["npcs"].at(i)["runawayDirection"]["y"]);
            npc->getAnimation()->initAnimator();
            npc->getAnimation()->changeAnimation(j["npcs"].at(i)["animations"].at(0)["name"].get<std::string>(), false);
            for (int x=0; x<j["npcs"].at(i)["phrase"].size(); x++){
                npc->addSentence(j["npcs"].at(i)["phrase"].at(x)["text"].get<std::string>(), 
                        new Coordinate(j["npcs"].at(i)["phrase"].at(x)["position"]["x"], j["npcs"].at(i)["phrase"].at(x)["position"]["y"]));
            }
            npcs.push_back(npc);
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
            
            preObstacles.push_back(o);
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
            
            postObstacles.push_back(o);
        }
    }
    
    //Cargamos los endPoints
    if (j.find("endPoints") != j.end()) {
        for (int i=0; i<j["endPoints"].size(); i++){
            Hitbox *endpoint = new Hitbox(j["endPoints"].at(i)["position"]["x"],j["endPoints"].at(i)["position"]["y"],j["endPoints"].at(i)["size"]["w"],j["endPoints"].at(i)["size"]["h"]);
            
            endPoints.push_back(endpoint);
        }
    }
    
    //Añadimos arma a player si hay alguna
    if (j.find("addGun") != j.end()){
        Gun *gunArm = new Gun(j["addGun"]["cooldown"].get<float>());
        gunArm->setAnimation(game->rM->getTexture(j["addGun"]["sprite"]["texture"]), 
                Rect<float> (j["addGun"]["sprite"]["rect"]["x"], j["addGun"]["sprite"]["rect"]["y"], j["addGun"]["sprite"]["rect"]["w"], j["addGun"]["sprite"]["rect"]["h"]));
        gunArm->getAnimation()->setOrigin(Coordinate(j["addGun"]["origin"]["x"],j["addGun"]["origin"]["y"])); //ToDo: campo en json?

        Bullet *bull = new Bullet(Coordinate(j["addGun"]["bullet"]["size"]["w"], j["addGun"]["bullet"]["size"]["h"]), 
                j["addGun"]["bullet"]["duration"], j["addGun"]["bullet"]["type"]);
        bull->setAnimation(game->rM->getTexture(j["addGun"]["bullet"]["sprite"]["texture"]), 
                Rect<float>(j["addGun"]["bullet"]["sprite"]["rect"]["x"], j["addGun"]["bullet"]["sprite"]["rect"]["y"], j["addGun"]["bullet"]["sprite"]["rect"]["w"], j["addGun"]["bullet"]["sprite"]["rect"]["h"]));
        for (int k=0; k<j["addGun"]["bullet"]["animations"].size(); k++){
            bull->getAnimation()->addAnimation(j["addGun"]["bullet"]["animations"].at(k)["name"].get<std::string>(), 
                    Coordinate(j["addGun"]["bullet"]["animations"].at(k)["position"]["x"], j["addGun"]["bullet"]["animations"].at(k)["position"]["y"]), 
                    j["addGun"]["bullet"]["animations"].at(k)["nSprites"], j["addGun"]["bullet"]["animations"].at(k)["duration"]);
        }
        bull->getAnimation()->initAnimator();
        bull->getAnimation()->changeAnimation(j["addGun"]["bullet"]["animations"].at(0)["name"].get<std::string>(), j["addGun"]["bullet"]["loop"]);
        bull->setDamage(j["addGun"]["bullet"]["damage"]);
        bull->getAnimation()->setOrigin(Coordinate(j["addGun"]["bullet"]["origin"]["x"],j["addGun"]["bullet"]["origin"]["y"]));//ToDo: campo en json?

        gunArm->setAttack(bull);

        rath->addGun(gunArm);
        rath->changeGun(0);
        
        hud->addGun(
                Coordinate(j["addGun"]["hudSprite"]["position"]["x"], j["addGun"]["hudSprite"]["position"]["y"]), 
                Rect<float>(j["addGun"]["hudSprite"]["rectOn"]["x"],j["addGun"]["hudSprite"]["rectOn"]["y"],j["addGun"]["hudSprite"]["rectOn"]["w"],j["addGun"]["hudSprite"]["rectOn"]["h"]), 
                Rect<float>(j["addGun"]["hudSprite"]["rectOff"]["x"],j["addGun"]["hudSprite"]["rectOff"]["y"],j["addGun"]["hudSprite"]["rectOff"]["w"],j["addGun"]["hudSprite"]["rectOff"]["h"]), 
                gunArm->getGunCooldown());
        hud->changeActiveGun(0);
    }
    //PANTALLA DE CARGA
    if (j.find("loading") != j.end()) {
        loading = new Sprite(game->rM->getTexture(j["loading"]["texture"]["name"].get<std::string>()),
                Rect<float>(j["loading"]["position"]["x"],j["loading"]["position"]["y"],j["loading"]["size"]["w"],j["loading"]["size"]["h"]));
        loadTime = new Time(j["loading"]["duration"].get<float>());
    }
    
    rath->restoreHP();
    hud->changeLifePlayer(rath->getHP());
    hud->changeMaxLifeBoss(boss->getMaxHP());
    hud->changeLifeBoss(boss->getHP());
}

void Level::Update(){
    if (!paused){
        /*EJECUTA LAS IAs*/
        if(activeIA==true){
            for (int i = 0; i<enemys.size(); i++){
                if(enemys.at(i)->getHP() > 0){
                    enemys.at(i)->AI(rath, hud);
                }
            }
            if(boss->getHP() > 0){
                boss->AI(rath, hud);
            }
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
        for(int i = 0; i < enemys.size(); i++){
            if (rath->getCurrentGunId() >= 0 && enemys.at(i)->getHitbox()->checkCollision(rath->getCurrentGun()->getBullet()->getHitbox()) && rath->isAttacking()){
                enemys.at(i)->damage(rath->getCurrentGun()->getBullet()->getDamage());
                if(enemys.at(i)->getHP() <= 0 && enemys.at(i)->isDead() == false){
                    enemys.at(i)->setPosition(100000,100000);
                    enemigosCaidos++;
                    enemys.at(i)->setDead(true);
                }
            }
            if(rath->getWeapon()->detectCollisions(enemys.at(i)->getHitbox())){
                enemys.at(i)->damage(rath->getWeapon()->getDamage());//ToDo: Meter daño a la guadaña, esta el arma ahora
                if(enemys.at(i)->getHP() <= 0 && enemys.at(i)->isDead() == false){
                    enemys.at(i)->startBlood(2);
                    enemigosCaidos++;
                    enemys.at(i)->setDead(true);
                }
            }
            if(enemys.at(i)->getHP() <= 0 && enemys.at(i)->isDead()){
                if(enemys.at(i)->getTimeDead()->getTime() == 0){
                    enemys.at(i)->setPosition(100000,100000);
                }
            }
        }
        
        
        if (j.find("crystals") != j.end()) {
            for (int i = 0; i<crystals.size(); i++){
                if(!crystals.at(i)->getTouched() && rath->getCurrentGunId() >= 0 && (crystals.at(i)->collision(rath->getWeapon()->getHitbox()) || crystals.at(i)->collision(rath->getCurrentGun()->getBullet()->getHitbox()))){
                    rath->damage(10);
                    hud->changeLifePlayer(rath->getHP());
                    //crystals.at(i)->setPosition(Coordinate(100000,100000));
                    crystals.at(i)->getCrystalAnimation()->changeAnimation("die", true);
                    crystals.at(i)->setTouched();
                }
            }
        }
        if (rath->getCurrentGunId() >= 0 && boss->getHitbox()->checkCollision(rath->getCurrentGun()->getBullet()->getHitbox()) && rath->isAttacking()){
            boss->damage(rath->getCurrentGun()->getBullet()->getDamage());
            hud->changeLifeBoss(boss->getHP());
            if(boss->getHP() <= 0){
                if (j.find("postBossObstacles") != j.end()) {
                    for (int i=0; i<postObstacles.size(); i++){
                        postObstacles.at(i)->setActive(false);
                    }
                }
                //Volvemos a la cancion normal
                Game::Instance()->rM->getMusic("boss")->getMusic()->stop();
                Game::Instance()->rM->getMusic("Main")->getMusic()->play();
                boss->setPosition(100000,100000); //ToDo PabloL: Poner un setActive para bloquear la ia cuando muera en Enemy
            }
        }
        if(rath->getWeapon()->detectCollisions(boss->getHitbox())){
            boss->damage(rath->getWeapon()->getDamage());
            hud->changeLifeBoss(boss->getHP());
            if(boss->getHP() <= 0){
                if (j.find("postBossObstacles") != j.end()) {
                    for (int i=0; i<postObstacles.size(); i++){
                        postObstacles.at(i)->setActive(false);
                    }
                }
                //Volvemos a la cancion normal
                Game::Instance()->rM->getMusic("boss")->getMusic()->stop();
                Game::Instance()->rM->getMusic("Main")->getMusic()->play();
                boss->setPosition(100000,100000); //ToDo PabloL: Poner un setActive para bloquear la ia cuando muera en Enemy
            }
        }
        if (rath->getCurrentGunId() >= 0 && boss->getCurrentGun()->getBullet()->getHitbox()->checkCollision(rath->getHitbox()) && boss->isAttacking()){
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
            for (int i=0; i<npcs.size(); i++){
                int disNpcPlayer = tri->distance(*rath->getCoordinate(), *npcs.at(i)->getCoordinate());
                if(disNpcPlayer < 300) npcs.at(i)->setInRange(true);
                else npcs.at(i)->setInRange(false);
            }
        }
        //PreBossObstacles
        if (j.find("preBossObstacles") != j.end()) {
            int disPlayerBoss = tri->distance(*rath->getCoordinate(), *boss->getCoordinate());
            if(disPlayerBoss < distanceToLock){
                bossZone = true;
                play = true;
            } else {
                bossZone = false;
                play = false;
            }
            if (enemigosCaidos == enemys.size()){
                if (bossZone) {
                    for (int i=0; i<preObstacles.size(); i++){
                        preObstacles.at(i)->setActive(true);
                    }
                } else {
                    for (int i=0; i<preObstacles.size(); i++){
                        preObstacles.at(i)->setActive(false);
                    }
                }
            }
        }
        /*Musica del boss*/
        if(play==true && isEnter==false){
           Game::Instance()->rM->getMusic("boss")->getMusic()->play();
           isEnter=true;
        }
        //Comprobamos los endPoints
        if (j.find("endPoints") != j.end()) {
            for (int i=0; i<endPoints.size();i++){
                if (endPoints.at(i)->checkCollision(rath->getHitbox())){
                    loadTime->start();
                    if(!loadTime->isExpired()){
                        loaded = true;
                    }else{
                        loaded = false;
                        return Game::Instance()->getLevelState()->changeLevel();
                    }
                }
            }
        }
    }
    
    if (j.find("npcs") != j.end()) {
        if (npcMoving != -1){
            int disNpcPlayer = tri->distance(*rath->getCoordinate(), *npcs.at(npcMoving)->getCoordinate());
            if (disNpcPlayer < 3000){
                npcs.at(npcMoving)->move(npcs.at(npcMoving)->getRunawayDirection()->x,npcs.at(npcMoving)->getRunawayDirection()->y);
            } else npcMoving = -1;
            if (disNpcPlayer > 1000){
                paused = false;
                Game::Instance()->getLevelState()->setPaused(false);
            }
        }
    }
}

void Level::Input(){
    if (!paused){
        if(Game::Instance()->iM->isActive("interact")){
            //NPCs
            if (j.find("npcs") != j.end()) {
                for (int i=0; i<npcs.size(); i++){
                    if (npcs.at(i)->getRange()){
                        if(npcs.at(i)->nextSentence()){
                            showNPCText = true;
                            //Posicionamos el nombre del npc
                            hud->setTLayerTalker(npcs.at(i)->getName(), 1125, 435); 
                            //Posicionamos lo que va a decir el npc
                            hud->setTLayerText(npcs.at(i)->getCurrentSentenceText(), npcs.at(i)->getCurrentSentencePosition()->x, npcs.at(i)->getCurrentSentencePosition()->y); 
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
                for (int i=0; i<notes.size(); i++){
                    if(rath->collision(notes.at(i)->getHitbox())){
                        if (!showNoteText && !notes.at(i)->getTaken()){
                            showNoteText = true;
                            notes.at(i)->setTaken();
                            paused = true;
                            Game::Instance()->getLevelState()->setPaused(true);
                        }
                    }
                }
            }
        }
    } else {
        if(Game::Instance()->iM->isActive("interact")){
            if (j.find("notes") != j.end()) {
                if (showNoteText) {
                    showNoteText = false;
                    paused = false;
                    Game::Instance()->getLevelState()->setPaused(false);
                }
            }
        }
    }
}

void Level::RenderLevel(){
    //ToDo: Para subir los FPS quizas podriamos hacer que solo se muestren las cosas que esten a menos de X distancia de nosotros
    //Dibujamos todos los elementos
    map->dibujarMapa(Game::Instance()->window);
    //Notas de texto
    if (j.find("notes") != j.end()) {
        for (int i=0; i<notes.size(); i++){
            if(!notes.at(i)->getTaken()){
               Game::Instance()->window->draw(*notes.at(i)->getNoteSprite()->getSprite());
            }
        }
    }
    
    //Cristales de rayos
    if (j.find("crystals") != j.end()) {
        for (int i=0; i<crystals.size(); i++){
            crystals.at(i)->getCrystalAnimation()->updateAnimator();
            Game::Instance()->window->draw(*crystals.at(i)->getCrystalAnimation()->getSprite());
            if(!crystals.at(i)->getTouched()){
                crystals.at(i)->drawSparks();
            }
        }
    }
    
    /*NPC*/
    if (j.find("npcs") != j.end()) {
        for (int i=0; i<npcs.size(); i++){
            Coordinate inc3(npcs.at(i)->getState()->getIC());
            npcs.at(i)->updatePosition(inc3.x, inc3.y);
            Game::Instance()->window->draw(*npcs.at(i)->getAnimation()->getSprite());
            if (npcs.at(i)->getRange()){
                Game::Instance()->window->setView(Game::Instance()->window->getDefaultView());
                if (npcMoving == -1) Game::Instance()->window->draw(*keyIterationNpc->getText());
                if(showNPCText){
                    hud->drawTextLayer();
                }
                Game::Instance()->window->setView(Game::Instance()->cameraView);
            }
        }
    }
    
    /*Enemigos*/
    for (int i = 0; i<enemys.size(); i++){
        Coordinate inc(enemys.at(i)->getState()->getIC());
        enemys.at(i)->updatePosition(inc.x, inc.y);
        enemys.at(i)->getAnimation()->updateAnimator();
        Game::Instance()->window->draw(*enemys.at(i)->getAnimation()->getSprite());
        enemys.at(i)->drawBlood();
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
    for (int i=0; i<preObstacles.size(); i++){
        if (preObstacles.at(i)->getActive()) Game::Instance()->window->draw(*preObstacles.at(i)->getAnimation()->getSprite());
    }
    for (int i=0; i<postObstacles.size(); i++){
        if (postObstacles.at(i)->getActive()) Game::Instance()->window->draw(*postObstacles.at(i)->getAnimation()->getSprite());
    }
}

void Level::RenderView(){
    if(loaded){
        Game::Instance()->window->draw(*loading->getSprite());
    }
    if (j.find("notes") != j.end()) {
        for (int i=0; i<notes.size(); i++){
            /*Texto notas */
            if(showNoteText){
                Game::Instance()->window->setView(Game::Instance()->window->getDefaultView());
                Game::Instance()->window->draw(*notes.at(i)->getBackgroundSprite()->getSprite());
                Game::Instance()->window->draw(*notes.at(i)->getText()->getText());
                Game::Instance()->window->setView(Game::Instance()->cameraView);
            }
        }
    }
}

Hitbox *Level::colision(Hitbox *hitbox){
    for(int i = 0; i < map->getMuros()->size(); i++){
        if(hitbox->checkCollision(map->getMuros()->at(i))){
            return map->getMuros()->at(i);
        }
    }
    for(int i=0; i<preObstacles.size(); i++){
        if(preObstacles.at(i)->getActive() && hitbox->checkCollision(preObstacles.at(i)->getHitbox())){
            return preObstacles.at(i)->getHitbox();
        }
    }
    for (int i=0; i<postObstacles.size(); i++){
        if(postObstacles.at(i)->getActive() && hitbox->checkCollision(postObstacles.at(i)->getHitbox())){
            return postObstacles.at(i)->getHitbox();
        }
    }
    for (int i=0; i<npcs.size(); i++){
        if(hitbox->checkCollision(npcs.at(i)->getHitbox())){
            return npcs.at(i)->getHitbox();
        }
    }
    for (int i=0; i<crystals.size(); i++){
        if(hitbox->checkCollision(crystals.at(i)->getHitbox())){
            return crystals.at(i)->getHitbox();
        }
    }
    return NULL;
}

void Level::CleanUp(){
    
    //Recorremos los resources del JSON
    for (int i=0; i<j["resources"].size(); i++){
        Game::Instance()->rM->releaseTexture(j["resources"].at(i)["name"].get<std::string>());
    }
    
    //Vaciar los vectores
    //ToDo: da segmentation fault aqui
    for(int i=0; i < enemys.size(); i++){
        delete enemys.at(i);
        enemys.at(i) = NULL;
    }
    
    enemys.clear();
    
    for(int i=0; i < respawn.size(); i++){
        delete respawn.at(i);
        respawn.at(i) = NULL;
    }
    
    respawn.clear();
    
    for(int i=0; i < npcs.size(); i++){
        delete npcs.at(i);
        npcs.at(i) = NULL;
    }
    
    npcs.clear();
    
    for(int i=0; i < notes.size(); i++){
        delete notes.at(i);
        notes.at(i) = NULL;
    }
    
    notes.clear();
    
    for(int i=0; i < crystals.size(); i++){
        delete crystals.at(i);
        crystals.at(i) = NULL;
    }
    
    crystals.clear();
    
    for(int i=0; i < preObstacles.size(); i++){
        delete preObstacles.at(i);
        preObstacles.at(i) = NULL;
    }
    
    preObstacles.clear();
    
    for(int i=0; i < postObstacles.size(); i++){
        delete postObstacles.at(i);
        postObstacles.at(i) = NULL;
    }
    
    postObstacles.clear();
    
    for(int i=0; i < endPoints.size(); i++){
        delete endPoints.at(i);
        //endPoints->at(i) = NULL;
    }
    
    endPoints.clear();
    
    //Hacemos delete de los elementos de Level
    delete boss;
    if(keyIterationNpc != NULL)delete keyIterationNpc;
    
    delete loading;
    delete loadTime;
    
    delete map;
    
    
    map = NULL; 
    boss = NULL;
    keyIterationNpc = NULL;
    loading = NULL;
    loadTime = NULL;
    
    //Reinicializamos las variables
    level = 0;
    enemigosCaidos = 0;
    actualRespawn = 0;
    npcMoving = -1;
    distanceToLock = 0;
    seeBoss = false;
    showNPCText = false;
    showNoteText = false;
    paused = false;
    bossZone = false;
    //Iniciar musica jefe
    play = false;
    loaded = false;
    
    rath->getFlashCooldown()->restart(0);
    
    for (int i=0; i<rath->getGuns().size(); i++){
        rath->getGuns().at(i)->getGunCooldown()->restart(0);
    }
}
