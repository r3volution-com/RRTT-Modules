#include "Level.h"
#include "Game.h"

Level::Level(int numLevel) {
    //Guardamos el nivel a cargar
    level = numLevel;
    enemys = new std::vector<Enemy*>();
    respawn = new std::vector<Coordinate*>();
    Coordinate* coord = new Coordinate(0,300);
    respawn->push_back(coord);
    //respawn[0]=(0,300);
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
    Texture *tex = new Texture("resources/Paper-Sprite.png");
    Texture *tex2 = new Texture("resources/pergamino.png");
    Texture *tex3 = new Texture("resources/npc.png");
     
    Font *font = new Font("resources/font.ttf");
    
    //Si estamos en el primer nivel
    if(level==1){
        //Cargamos el mapa
        map = new Map("resources/bosque_definitivo6.tmx");
        
        //Cargamos las notas
        note = new Note(tex, Rect<float>(0, 0, 64, 60), tex2, Rect<float>(0, 0, 608, 488), font);
        note->setPosition(Coordinate(150, 3550));
        note->setBackgroundPosition(Coordinate(100, 100));
        note->setText("Hola mundo!", sf::Color::Black, sf::Color::White, 1, 25);
    
        //Cargamos los cristales
        Game::Instance()->rM->loadTexture("crystal", "resources/Crystal.png");
        
        crystal = new Crystals(Game::Instance()->rM->getTexture("crystal"), Rect<float>(0, 0, 174, 290));
        crystal->setPosition(Coordinate(3000, 3000));
        
        //Cargamos los enemigos
        Game::Instance()->rM->loadTexture("enemy", "resources/enemy.png");
        Game::Instance()->rM->loadTexture("boss", "resources/boss.png");
        Game::Instance()->rM->loadTexture("Bloque", "resources/Bloque.jpg");
        Game::Instance()->rM->loadTexture("arma", "resources/sprites.png");

        Enemy *enemy = new Enemy(Coordinate(140,1200), Coordinate(128, 128), 10);
        enemy->setSprite(Game::Instance()->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128));
        enemy->getAnimation()->addAnimation("idle", Coordinate(0, 0), 1, 0.5f);
        enemy->getAnimation()->initAnimator();
        enemy->getAnimation()->changeAnimation("idle", false);
        enemy->setMaxHP(100);
        enemy->setDistanceEnemyHome(1000);
        enemy->setDistancePlayerEnemy(500);
        enemy->setDmgHit(1);
        enemy->setHitCooldown(new Time(0.5));
        enemy->setType(3);
        enemy->setFreeze(7);
        
        enemys->push_back(enemy);
        
        Gun *gunArm = new Gun(Coordinate(0, 0), Coordinate(128, 128), 5);
        gunArm->setAnimation(Game::Instance()->rM->getTexture("player"), Rect<float> (0, 640, 128, 128));
        gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
        gunArm->getAnimation()->initAnimator();    
        gunArm->getAnimation()->changeAnimation("armaIdle", false);
        gunArm->getAnimation()->setOrigin(Coordinate(56,34));
        gunArm->setDamage(30);

        Bullet *bull = new Bullet(Coordinate(0,0), Coordinate(128, 128), 2);
        bull->setAnimation(Game::Instance()->rM->getTexture("fire"), Rect<float>(0,0, 128, 128));
        bull->getAnimation()->addAnimation("fireIdle", Coordinate(0, 0), 2, 0.5f);
        bull->getAnimation()->setOrigin(Coordinate(184,98));
        bull->getAnimation()->initAnimator();
        bull->getAnimation()->changeAnimation("fireIdle", false);

        gunArm->setAttack(bull);
        
        boss = new Boss(Coordinate(140,500), Coordinate(128, 128), 10, 1);
        boss->setSprite(Game::Instance()->rM->getTexture("boss"), Rect<float>(0,0, 128, 128));
        boss->getAnimation()->addAnimation("idle", Coordinate(0, 0), 1, 0.5f);
        boss->getAnimation()->initAnimator();
        boss->getAnimation()->changeAnimation("idle", false);
        boss->setMaxHP(50);
        boss->setDistanceEnemyHome(1000);
        boss->setDistancePlayerEnemy(500);
        boss->setDmgHit(1);
        boss->setHitCooldown(new Time(0.5));
        
        boss->addGun(gunArm);
        
        enemys->push_back(enemy);
        
        /* NPC */
        npc = new NPC(Coordinate(2500,4000), Coordinate(128, 128), 2, "Jose");
        npc->setSprite(tex3, Rect<float>(0,0,128,128));
        npc->getAnimation()->addAnimation("idle", Coordinate(0,0), 4, 1.0f);
        npc->getAnimation()->initAnimator();
        npc->getAnimation()->changeAnimation("idle", false);
        //aldeano->loadAnimation(tex, Coordinate(0, 128), 3, 0.1f);
        npc->addSentence("probamos con esto\n\nPulsa E para continuar", new Coordinate(2300, 3800));
        npc->addSentence("probamos por segunda vez\n\nPulsa E para continuar", new Coordinate(20, 520));
        npc->addSentence("probamos por ultima vez\n\nPulsa E para continuar", new Coordinate(20, 520));
        
        //Anyadimos la accion de hablar cuando pulsemos la E
        Game::Instance()->iM->addAction("hablar", thor::Action(sf::Keyboard::Key::E, thor::Action::PressOnce));
    }  
}

void Level::Update(Player* rath, HUD* hud){
    for (int i = 0; i<enemys->size(); i++){
        if(enemys->at(i)->getHP() > 0){
            enemys->at(i)->AI(rath, hud);
        }
    }
    boss->AI(rath, hud);
    
    for(int i = 0; i < enemys->size(); i++){
        if (enemys->at(i)->getHitbox()->checkCollision(rath->getCurrentGun()->getBullet()->getHitbox()) && rath->isAttacking()){
            enemys->at(i)->damage(rath->getCurrentGun()->getDamage());
            if(enemys->at(i)->getHP() <= 0){
                delete enemys->at(i);
            }
        }
    }
    if (boss->getHitbox()->checkCollision(rath->getCurrentGun()->getBullet()->getHitbox()) && rath->isAttacking()){
        boss->damage(rath->getCurrentGun()->getDamage());
        hud->changeLifeBoss(boss->getHP());
        if(boss->getHP() <= 0){
            delete boss;
        }
   }
}

void Level::Input(Player* rath, HUD* hud){

    Texture *tex = new Texture("resources/textbox.png");
    int salir = 0;
    
    if(Game::Instance()->iM->isActive("hablar")){
        salir = npc->nextSentence();
   
        if(salir==1){
            setMuestra(true);
            cout << npc->getCurrentSentenceText() << endl;
            //Creamos la caja que va a contener el texto
            hud->setTextLayer(Coordinate(0,420), Rect <float> (0, 0, 1280, 300) ,tex);
            //Posicionamos lo que va a decir el npc
            hud->setTLayerText(npc->getCurrentSentenceText(), 25, 520);
            //Le damos estilo a lo que va a decir el npc
            hud->setTLayerTextParams(20, sf::Color::White, sf::Color::Blue);

            //Posicionamos el nombre del npc
            hud->setTLayerTalker(npc->getName(), 1125, 435);
        }else{
            setMuestra(false);
        }

        //Anyadir comprobacion de hitbox del personaje con el npc
        //if(rath->collision(npc->getHitbox())){
        //}
    }
}

void Level::Render(){
    //Dibujamos todos los elementos
    map->dibujarMapa(Game::Instance()->window);
    
    if(!note->getTaken()){
       Game::Instance()->window->draw(*note->getNoteSprite()->getSprite());
    }
    
    if(!crystal->getTouched()){
       Game::Instance()->window->draw(*crystal->getCrystalSprite()->getSprite());
    }
    
    for (int i = 0; i<enemys->size(); i++){
        Coordinate inc(enemys->at(i)->getState()->getIC());
        //cout << inc;
        enemys->at(i)->getAnimation()->updateAnimator();
        enemys->at(i)->setPosition(inc.x, inc.y);
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
    //Game::Instance()->window->draw(*boss->getCurrentGun()->getAnimation()->getSprite());
    boss->setPosition(inc2.x, inc2.y);
    
    Game::Instance()->window->draw(*npc->getAnimation()->getSprite());
    
    //Game::Instance()->window->draw(*hud);
    
    Game::Instance()->window->draw(*boss->getAnimation()->getSprite());
}

void Level::setRespawn(int resp){
    respawn->at(resp);
}
