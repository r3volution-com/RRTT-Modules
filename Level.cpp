#include "Level.h"
#include "Game.h"

Level::Level(int numLevel) {
    //Guardamos el nivel a cargar
    level = numLevel;
    enemigosCaidos = 0;
    enemys = new std::vector<Enemy*>();
    respawn = new std::vector<Coordinate*>();
    Coordinate* coord = new Coordinate(5500,14250);
    respawn->push_back(coord);
    //respawn[1]=(500,300);
    //respawn[2]=(1000,300);
    //Cargamos todos los elementos del juego
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
    Texture *tex = new Texture("resources/note.png");
    Texture *tex2 = new Texture("resources/pergamino.png");
    Texture *tex3 = new Texture("resources/npc.png");
    Texture *tex4 = new Texture("resources/muro.png");
     
    Font *font = new Font("resources/font.ttf");
    
    //Si estamos en el primer nivel
    if(level==1){
        //Cargamos el mapa
        map = new Map("resources/MAPAPABLO.tmx");
        
        //Cargamos las notas
        note = new Note(tex, Rect<float>(0, 0, 128, 128), tex2, Rect<float>(0, 0, 608, 488), font);
        note->setPosition(Coordinate(1950, 13850));
        note->setBackgroundPosition(Coordinate(350, 125));
        note->setText("El amor y el odio no son ciegos, \nsino que estan cegados por \nel fuego que llevan dentro.\n\nPD: Saluda, que estas\n "
        "saliendo en multimedia!", sf::Color::Black, sf::Color::White, 1, 25);
    
        //Cargamos los cristales
        Game::Instance()->rM->loadTexture("crystal", "resources/Crystal.png");
        
        crystal = new Crystals(Game::Instance()->rM->getTexture("crystal"), Rect<float>(0, 0, 174, 290));
        crystal->setPosition(Coordinate(3000, 3000));
        
        //Cargamos los enemigos
        Game::Instance()->rM->loadTexture("enemy", "resources/ENEMIGOS.png");
        

        //Enemigo izquierda
        Enemy *enemy = new Enemy(Coordinate(3000,9000), Coordinate(128, 128), 20);
        enemy->setType(3);
        enemy->setAnimations(Game::Instance()->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy->setMaxHP(40);
        enemy->setDistanceEnemyHome(2000);
        enemy->setDistancePlayerEnemy(1500);
        enemy->setDmgHit(3);
        enemy->setHitCooldown(new Time(2));
        enemy->setFreeze(22);
        
        enemys->push_back(enemy);
        
        //Enemigo abajo derecha
        Enemy *enemy2 = new Enemy(Coordinate(4000,9350), Coordinate(128, 128), 15);
        enemy2->setType(2);
        enemy2->setAnimations(Game::Instance()->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy2->setMaxHP(30);
        enemy2->setDistanceEnemyHome(1300);
        enemy2->setDistancePlayerEnemy(800);
        enemy2->setDmgHit(2);
        enemy2->setHitCooldown(new Time(0.5));
        enemy2->SetFlashRange(10);
        enemy2->setFlashCooldown(new Time(2));
        
        enemys->push_back(enemy2);
        
        //Enemigo arriba centro
        Enemy *enemy3 = new Enemy(Coordinate(3000,8550), Coordinate(128, 128), 20);
        enemy3->setType(1);
        enemy3->setAnimations(Game::Instance()->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy3->setMaxHP(40);
        enemy3->setDistanceEnemyHome(1000);
        enemy3->setDistancePlayerEnemy(500);
        enemy3->setDmgHit(3);
        enemy3->setHitCooldown(new Time(0.5));
        
        enemys->push_back(enemy3);
        
        //Enemigo abajo a la izquierda
        Enemy *enemy4 = new Enemy(Coordinate(3500,9550), Coordinate(128, 128), 15);
        enemy4->setType(2);
        enemy4->setAnimations(Game::Instance()->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy4->setMaxHP(30);
        enemy4->setDistanceEnemyHome(1300);
        enemy4->setDistancePlayerEnemy(800);
        enemy4->setDmgHit(2);
        enemy4->setHitCooldown(new Time(0.5));
        enemy4->SetFlashRange(10);
        enemy4->setFlashCooldown(new Time(2));
        
        enemys->push_back(enemy4);
        
        //Primer enemigo camino
        Enemy *enemy5 = new Enemy(Coordinate(3650,11000), Coordinate(128, 128), 15);
        enemy5->setType(1);
        enemy5->setAnimations(Game::Instance()->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy5->setMaxHP(30);
        enemy5->setDistanceEnemyHome(1200);
        enemy5->setDistancePlayerEnemy(500);
        enemy5->setDmgHit(2);
        enemy5->setHitCooldown(new Time(0.5));
        
        enemys->push_back(enemy5);
        
        Gun *gunArm = new Gun(Coordinate(0, 0), Coordinate(128, 128), 3);
        gunArm->setAnimation(Game::Instance()->rM->getTexture("enemy"), Rect<float> (0, 640, 128, 128));
        gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
        gunArm->getAnimation()->initAnimator();    
        gunArm->getAnimation()->changeAnimation("armaIdle", false);
        gunArm->getAnimation()->setOrigin(Coordinate(56,34));
        gunArm->setDamage(1);

        Bullet *bull = new Bullet(Coordinate(0,0), Coordinate(128, 128), 2);
        bull->setAnimation(Game::Instance()->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        bull->getAnimation()->addAnimation("fireIdle", Coordinate(0, 512), 2, 0.5f);
        bull->getAnimation()->setOrigin(Coordinate(184,98));
        bull->getAnimation()->initAnimator();
        bull->getAnimation()->changeAnimation("fireIdle", false);

        gunArm->setAttack(bull);
        
        boss = new Boss(Coordinate(3500,4200), Coordinate(128, 128), 20, 1);
        boss->setAnimations(Game::Instance()->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        boss->setMaxHP(200);
        boss->setDistanceEnemyHome(1500);
        boss->setDistancePlayerEnemy(1000);
        boss->setDmgHit(5);
        boss->setHitCooldown(new Time(1));
        boss->SetFlashRange(8);
        boss->setFlashCooldown(new Time(0.5));
        boss->setDefensive(new Time(20));
        
        boss->addGun(gunArm);
        
        boss->getState()->update();
        
        /* NPC */
        npc = new NPC(Coordinate(4500,13300), Coordinate(128, 128), 2, "Jose");
        npc->setSprite(tex3, Rect<float>(0,0,128,128));
        npc->getAnimation()->addAnimation("idle", Coordinate(0,0), 4, 1.0f);
        npc->getAnimation()->initAnimator();
        npc->getAnimation()->changeAnimation("idle", false);
        //aldeano->loadAnimation(tex, Coordinate(0, 128), 3, 0.1f);
        npc->addSentence("El bosque esta en llamas!!\n\nPulsa E para continuar", new Coordinate(2300, 3800));
        npc->addSentence("Sera mejor que huyas muchacho no te aguarda nada bueno ahi.\n\nPulsa E para continuar", new Coordinate(20, 520));
        npc->addSentence("Un momento, creo que tu cara me suena...\n\nPulsa E para continuar", new Coordinate(20, 520));
        
        /* MURO */
        npc2 = new NPC(Coordinate(2500,5800), Coordinate(1280, 384), 2, "Jose");
        npc2->setSprite(tex4, Rect<float>(0,0,1280,384));
        npc2->getAnimation()->addAnimation("idle", Coordinate(0,0), 4, 1.0f);
        npc2->getAnimation()->initAnimator();
        npc2->getAnimation()->changeAnimation("idle", false);
        
        //Anyadimos la accion de hablar cuando pulsemos la E
        Game::Instance()->iM->addAction("interactuar", thor::Action(sf::Keyboard::Key::E, thor::Action::PressOnce));
    }  
}

void Level::Update(Player* rath, HUD* hud){
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
            enemys->at(i)->damage(rath->getCurrentGun()->getDamage());
            if(enemys->at(i)->getHP() <= 0){
                enemys->at(i)->setPosition(100000,100000);
                enemigosCaidos++;
                cout << enemigosCaidos << endl;
            }
        }
        if(rath->getWeapon()->detectCollisions(enemys->at(i)->getHitbox())){
            enemys->at(i)->damage(rath->getWeapon()->getDamage());//ToDo: Meter daño a la guadaña, esta el arma ahora
            if(enemys->at(i)->getHP() <= 0){
                enemys->at(i)->setPosition(100000,100000);
                enemigosCaidos++;
                cout << enemigosCaidos << endl;
            }
        }
        
    }
    if (boss->getHitbox()->checkCollision(rath->getCurrentGun()->getBullet()->getHitbox()) && rath->isAttacking()){
        boss->damage(rath->getCurrentGun()->getDamage());
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
        /*if(rath->getHP() <= 0){
            delete boss;
        }*/
   }
    
    if(rath->collision(npc2->getHitbox()) && enemigosCaidos < 5){
        rath->move(0,1);
    }
}

void Level::Input(Player* rath, HUD* hud){

    Texture *tex = new Texture("resources/textbox.png");
    int salir = 0;
    
    //NPC
    if(Game::Instance()->iM->isActive("interactuar") && rath->collision(npc->getHitbox())){
        salir = npc->nextSentence();
   
        if(salir==1){
            setMuestra(true);
            cout << npc->getCurrentSentenceText() << endl;
            //Creamos la caja que va a contener el texto
            hud->setTextLayer(Coordinate(0,420), Rect <float> (0, 0, 1280, 300) ,tex);
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
    
    if(enemigosCaidos < 5){
        Game::Instance()->window->draw(*npc2->getAnimation()->getSprite());
    }
    
    Game::Instance()->window->draw(*boss->getAnimation()->getSprite());
}

void Level::setRespawn(int resp){
    respawn->at(resp);
}
