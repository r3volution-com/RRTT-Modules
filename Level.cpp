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
        
        Gun *gunArm = new Gun(Coordinate(0, 0), Coordinate(128, 128), 3);
        gunArm->setAnimation(Game::Instance()->rM->getTexture("player"), Rect<float> (0, 640, 128, 128));
        gunArm->getAnimation()->addAnimation("armaIdle", Coordinate(0, 512), 1, 2.0f);
        gunArm->getAnimation()->initAnimator();    
        gunArm->getAnimation()->changeAnimation("armaIdle", false);
        gunArm->getAnimation()->setOrigin(Coordinate(56,34));
        gunArm->setDamage(10);

        Bullet *bull = new Bullet(Coordinate(0,0), Coordinate(128, 128), 2);
        bull->setAnimation(Game::Instance()->rM->getTexture("fire"), Rect<float>(0,0, 128, 128));
        bull->getAnimation()->addAnimation("fireIdle", Coordinate(0, 0), 2, 0.5f);
        bull->getAnimation()->setOrigin(Coordinate(184,98));
        bull->getAnimation()->initAnimator();
        bull->getAnimation()->changeAnimation("fireIdle", false);

        gunArm->setAttack(bull);
        
        boss = new Boss(Coordinate(2400,4000), Coordinate(128, 128), 10, 1);
        boss->setSprite(Game::Instance()->rM->getTexture("boss"), Rect<float>(0,0, 128, 128));
        boss->getAnimation()->addAnimation("idle", Coordinate(0, 0), 1, 0.5f);
        boss->getAnimation()->initAnimator();
        boss->getAnimation()->changeAnimation("idle", false);
        boss->setMaxHP(50);
        boss->setDistanceEnemyHome(1500);
        boss->setDistancePlayerEnemy(1000);
        boss->setDmgHit(10);
        boss->setHitCooldown(new Time(1));
        boss->SetFlashRange(15);
        boss->setFlashCooldown(new Time(0.5));
        boss->setDefensive(new Time(20));
        
        boss->addGun(gunArm);
        
        enemys->push_back(enemy);
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
   if (boss->getCurrentGun()->getBullet()->getHitbox()->checkCollision(rath->getHitbox()) && boss->isAttacking()){
       std::cout<<boss->getCurrentGun()->getBullet()->getHitbox()->hitbox->left<<"\n";
       std::cout<<"Rath: "<<rath->getHitbox()->hitbox->left<<"\n";
        rath->damage(boss->getCurrentGun()->getDamage());
        hud->changeLifePlayer(rath->getHP());
        /*if(rath->getHP() <= 0){
            delete boss;
        }*/
   }
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

void Level::setRespawn(int resp){
    respawn->at(resp);
}
