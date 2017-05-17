#include "Level.h"
#include "Game.h"

Level::Level(int numLevel) {
    //Guardamos el nivel a cargar
    level = numLevel;
    enemigosCaidos = 0;
    enemys = new std::vector<Enemy*>();
    respawn = new std::vector<Coordinate*>();
    Coordinate* inicio = new Coordinate(5500,14250);
    Coordinate* beforeBoss = new Coordinate(3200,7000);
    respawn->push_back(inicio);
    respawn->push_back(beforeBoss);
    //respawn[1]=(500,300);
    //respawn[2]=(1000,300);
    //Cargamos todos los elementos del juego
    showIterationNpc = false;
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
    
    game->rM->loadTexture("sangre", "resources/rojo.png");
    game->rM->loadTexture("pergamino", "resources/pergamino.png");
    
    //Si estamos en el primer nivel
    if(level==1){
        //Cargamos el mapa
        map = new Map("resources/MAPAPABLO.tmx");
        
        
        //Cargamos las notas
        note = new Note(game->rM->getTexture("gui-tileset"), Rect<float>(325, 920, 128, 128), game->rM->getTexture("pergamino"), Rect<float>(0, 0, 608, 488), game->rM->getFont("font"));
        note->setPosition(Coordinate(1950, 13850));
        note->setBackgroundPosition(Coordinate(350, 125));
        note->setText("El amor y el odio no son ciegos, \nsino que estan cegados por \nel fuego que llevan dentro.\n\nPD: Saluda, que estas\n "
        "saliendo en multimedia!", sf::Color::Black, sf::Color::White, 1, 25);
    
        //Cargamos los cristales
        crystal = new Crystals(game->rM->getTexture("gui-tileset"), Rect<float>(300, 920, 174, 290));
        crystal->setPosition(Coordinate(3000, 3000));
        
        //Cargamos los enemigos
        game->rM->loadTexture("enemy", "resources/enemigosLVL1.png");
        

        //Enemigo izquierda
        Enemy *enemy = new Enemy(Coordinate(3200,9550), Coordinate(128, 128), 20);
        enemy->setType(3);
        enemy->setAnimations(game->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy->setMaxHP(40);
        enemy->setDistanceEnemyHome(1400);
        enemy->setDistancePlayerEnemy(700);
        enemy->setInitialDmg(6);
        enemy->setHitCooldown(new Time(2));
        enemy->setFreeze(22);
        enemy->setBlood(game->rM->getTexture("sangre"));
        
        enemys->push_back(enemy);
        
        //Enemigo abajo derecha
        Enemy *enemy2 = new Enemy(Coordinate(3500,8000), Coordinate(128, 128), 15);
        enemy2->setType(2);
        enemy2->setAnimations(game->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy2->setMaxHP(50);
        enemy2->setDistanceEnemyHome(1400);
        enemy2->setDistancePlayerEnemy(700);
        enemy2->setInitialDmg(5);
        enemy2->setHitCooldown(new Time(0.5));
        enemy2->SetFlashRange(10);
        enemy2->setFlashCooldown(new Time(2));
        enemy2->setBlood(game->rM->getTexture("sangre"));
        
        enemys->push_back(enemy2);
        
        //Enemigo arriba centro
        Enemy *enemy3 = new Enemy(Coordinate(3500,8700), Coordinate(128, 128), 20);
        enemy3->setType(1);
        enemy3->setAnimations(game->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy3->setMaxHP(60);
        enemy3->setDistanceEnemyHome(1300);
        enemy3->setDistancePlayerEnemy(650);
        enemy3->setInitialDmg(6);
        enemy3->setHitCooldown(new Time(0.5));
        enemy3->setBlood(game->rM->getTexture("sangre"));
        
        enemys->push_back(enemy3);
        
        //Enemigo abajo a la izquierda
        Enemy *enemy4 = new Enemy(Coordinate(3450,9750), Coordinate(128, 128), 15);
        enemy4->setType(2);
        enemy4->setAnimations(game->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy4->setMaxHP(40);
        enemy4->setDistanceEnemyHome(1430);
        enemy4->setDistancePlayerEnemy(715);
        enemy4->setInitialDmg(4);
        enemy4->setHitCooldown(new Time(0.5));
        enemy4->SetFlashRange(10);
        enemy4->setFlashCooldown(new Time(2));
        enemy4->setBlood(game->rM->getTexture("sangre"));
        
        enemys->push_back(enemy4);
        
        //Primer enemigo camino
        Enemy *enemy5 = new Enemy(Coordinate(3650,11500), Coordinate(128, 128), 15);
        enemy5->setType(1);
        enemy5->setAnimations(game->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy5->setMaxHP(50);
        enemy5->setDistanceEnemyHome(1400);
        enemy5->setDistancePlayerEnemy(700);
        enemy5->setDmgHit(5);
        enemy5->setHitCooldown(new Time(0.5));
        enemy5->setBlood(game->rM->getTexture("sangre"));
        
        enemys->push_back(enemy5);
        
        Enemy *enemy6 = new Enemy(Coordinate(3250,7700), Coordinate(128, 128), 20);
        enemy6->setType(3);
        enemy6->setAnimations(game->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy6->setMaxHP(40);
        enemy6->setDistanceEnemyHome(1400);
        enemy6->setDistancePlayerEnemy(700);
        enemy6->setInitialDmg(4);
        enemy6->setHitCooldown(new Time(2));
        enemy6->setFreeze(18);
        enemy6->setBlood(game->rM->getTexture("sangre"));
        
        enemys->push_back(enemy6);
        
        //Enemigo sorpresa
        Enemy *enemy7 = new Enemy(Coordinate(3200,6300), Coordinate(128, 128), 20);
        enemy7->setType(1);
        enemy7->setAnimations(game->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy7->setMaxHP(80);
        enemy7->setDistanceEnemyHome(1300);
        enemy7->setDistancePlayerEnemy(650);
        enemy7->setInitialDmg(7);
        enemy7->setHitCooldown(new Time(0.5));
        enemy7->setBlood(game->rM->getTexture("sangre"));
        
        enemys->push_back(enemy7);
        
        Gun *gunArm = new Gun(3);
        gunArm->setAnimation(game->rM->getTexture("enemy"), Rect<float> (0, 640, 128, 128));
        gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
        gunArm->getAnimation()->initAnimator();    
        gunArm->getAnimation()->changeAnimation("armaIdle", false);
        gunArm->getAnimation()->setOrigin(Coordinate(56,34));

        Bullet *bull = new Bullet(Coordinate(0,0), Coordinate(128, 128), 2, 't');
        bull->setAnimation(game->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        bull->getAnimation()->addAnimation("fireIdle", Coordinate(0, 512), 2, 0.5f);
        bull->getAnimation()->setOrigin(Coordinate(184,98));
        bull->getAnimation()->initAnimator();
        bull->getAnimation()->changeAnimation("fireIdle", false);
        bull->setDamage(2);

        gunArm->setAttack(bull);
        
        boss = new Boss(Coordinate(3500,3900), Coordinate(128, 128), 20);
        boss->setAnimations(game->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        boss->setMaxHP(470);
        boss->setDistanceEnemyHome(2000);
        boss->setDistancePlayerEnemy(1500);
        boss->setInitialDmg(15);
        boss->setHitCooldown(new Time(1));
        boss->SetFlashRange(8);
        boss->setFlashCooldown(new Time(0.5));
        boss->setStateClock(new Time(20));
        boss->addState(1);
        boss->addState(2);
        srand (time(NULL));
        for(int y = 0; y < 8; y++){
            boss->addRandomState();
        }
        
        boss->addGun(gunArm);
        
        boss->getState()->update();*/
        
        
        /*****BOSS LEVEL 2*****/
        Gun *gunArm = new Gun(Coordinate(0, 0), Coordinate(128, 128), 1.0f);
        gunArm->setAnimation(game->rM->getTexture("player"), Rect<float> (0, 640, 128, 128));
        gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
        gunArm->getAnimation()->addAnimation("armaIzq", Coordinate(128, 512), 1, 2.0f);
        gunArm->getAnimation()->initAnimator();    
        gunArm->getAnimation()->changeAnimation("armaIdle", false);
        gunArm->getAnimation()->setOrigin(Coordinate(56,34));
        gunArm->setDamage(15);

        Bullet *bull = new Bullet(Coordinate(0,0), Coordinate(256, 128), 0.5f, 'l');
        bull->setAnimation(game->rM->getTexture("laser"), Rect<float>(0,0, 256, 128));
        bull->getAnimation()->addAnimation("laseridle", Coordinate(0, 0), 3, 0.5f);
        bull->getAnimation()->setOrigin(Coordinate(300,64));
        bull->getAnimation()->initAnimator();
        bull->getAnimation()->changeAnimation("laseridle", true);

        gunArm->setAttack(bull);
        
        boss = new Boss(Coordinate(5000,14250), Coordinate(128, 128), 25, 2);
        boss->setAnimations(game->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        boss->setMaxHP(900);
        boss->setDistanceEnemyHome(2000);
        boss->setDistancePlayerEnemy(1500);
        boss->setInitialDmg(18);
        boss->setHitCooldown(new Time(1));
        boss->SetFlashRange(12);
        boss->setFlashCooldown(new Time(0.5));
        boss->setStateClock(new Time(20));
        boss->addState(3);
        boss->addState(4);
        boss->addState(2);
        srand (time(NULL));
        for(int y = 0; y < 7; y++){
            boss->addRandomState();
        }
        
        boss->addGun(gunArm);
        
        boss->getState()->update();
        
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
        
        keyIterationNpc = new Text("Pulsa la tecla ""E"" para interacctuar con el NPC cuando estes cerca", Coordinate(310,600), game->rM->getFont("font"), false);
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
        rath->damage(boss->getCurrentGun()->getDamage());
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
