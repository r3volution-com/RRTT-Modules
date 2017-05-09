#include "Level.h"
#include "Game.h"

Level::Level(int numLevel) {
    
    //Guardamos el nivel a cargar
    level = numLevel;
    enemys = new std::vector<Enemy*>();
    
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
    
    Font *font = new Font("resources/font.ttf");
    
    //Si estamos en el primer nivel
    if(level==1){
        //Cargamos el mapa
        map = new Map("resources/bosque_definitivo.tmx");
        
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
        
        
        boss = new Boss(Coordinate(140,500), Coordinate(128, 128), 10);
        boss->setSprite(Game::Instance()->rM->getTexture("boss"), Rect<float>(0,0, 128, 128));
        boss->getAnimation()->addAnimation("idle", Coordinate(0, 0), 1, 0.5f);
        boss->getAnimation()->initAnimator();
        boss->getAnimation()->changeAnimation("idle", false);
        
        boss->addGun(gunArm);
        
        enemys->push_back(enemy);
    }  
}

void Level::AI(Player *rath, HUD* hud) {
    for (int i = 0; i<enemys->size(); i++){
        enemys->at(i)->AI(rath, hud);
    }
    boss->AI(rath, hud);
}

void Level::Update(){
    
    //enemyAI deberia ir aqui?
    
}

void Level::Input(){
    
    //Por ahora vacio
    
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
    Game::Instance()->window->draw(*boss->getAnimation()->getSprite());
    
}