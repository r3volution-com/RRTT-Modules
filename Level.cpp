#include "Level.h"
#include "Game.h"

Level::Level(int numLevel) {
    
    //Guardamos el nivel a cargar
    level = numLevel;
    
    //Cargamos todos los elementos del juego
    loadMap();
    loadNote();
    loadEnemy();
    loadCrystal();
    
}

void Level::loadMap(){
    
    //Cargamos bosque
    if(level==1){
        map = new Map("resources/bosque.tmx");
    }
    //Hacer coindiciones para el resto de mapas cuando esten creados
}

void Level::loadNote(){
    
    Texture *tex = new Texture("resources/Paper-Sprite.png");
    Texture *tex2 = new Texture("resources/pergamino.png");
    
    Font *font = new Font("resources/font.ttf");
    
    if(level==1){
        note = new Note(tex, Rect<float>(0, 0, 64, 60), tex2, Rect<float>(0, 0, 608, 488), font);
        note->setPosition(Coordinate(150, 3550));
        note->setBackgroundPosition(Coordinate(100, 100));
        note->setText("Hola mundo!", sf::Color::Black, sf::Color::White, 1, 25);
    }
    
}

void Level::loadCrystal(){
    
    if(level==1){
        Game::Instance()->rM->loadTexture("crystal", "resources/Crystal.png");
        
        crystal = new Crystals(Game::Instance()->rM->getTexture("crystal"), Rect<float>(0, 0, 64, 60));
        crystal->setPosition(Coordinate(350, 150));
    }
}

void Level::loadEnemy(){
    
    if(level==1){
        Game::Instance()->rM->loadTexture("enemy", "resources/enemy.png");
        Game::Instance()->rM->loadTexture("boss", "resources/boss.png");
        Game::Instance()->rM->loadTexture("Bloque", "resources/Bloque.jpg");
        Game::Instance()->rM->loadTexture("arma", "resources/sprites.png");
        //Game::Instance()->rM->loadTexture("bullet", "resources/Crystal.png");

        enemy = new Enemy(Coordinate(2900,1900), Game::Instance()->rM->getTexture("enemy"), Rect<float>(0,0, 128, 128), 10);
        enemy->getAnimation()->addAnimation("idle", Coordinate(0, 0), 1, 0.5f);
        enemy->getAnimation()->initAnimator();
        enemy->getAnimation()->changeAnimation("idle", false);
        enemy->setDistanceEnemyHome(1000);
        enemy->setDistancePlayerEnemy(500);
        enemy->setDmgHit(30);
        enemy->setHitCooldown(new Time(0.5));
        enemy->setType(3);
        enemy->setFreeze(7);
        
        boss = new Boss(Coordinate(3500,2500), Game::Instance()->rM->getTexture("boss"), Rect<float>(0,0, 128, 128), 10);
        boss->getAnimation()->addAnimation("idle", Coordinate(0, 0), 1, 0.5f);
        boss->getAnimation()->initAnimator();
        boss->getAnimation()->changeAnimation("idle", false);
    }
}

void Level::drawAll(){
    
    //Dibujamos todos los elementos
    map->dibujarMapa(Game::Instance()->window);
    
    if(!note->getTaken()){
       Game::Instance()->window->draw(*note->getNoteSprite()->getSprite());
    }
    
    if(!crystal->getTouched()){
       Game::Instance()->window->draw(*crystal->getCrystalSprite()->getSprite());
    }
    
    Coordinate inc(enemy->getState()->getIC());
    //cout << inc;
    enemy->getAnimation()->updateAnimator();
    enemy->setPosition(inc.x, inc.y);
    Game::Instance()->window->draw(*enemy->getAnimation()->getSprite());
    
    
    Coordinate inc2(boss->getState()->getIC());
    boss->getAnimation()->updateAnimator();
    //Game::Instance()->window->draw(*boss->getCurrentGun()->getAnimation()->getSprite());
    boss->setPosition(inc2.x, inc2.y);
    Game::Instance()->window->draw(*boss->getAnimation()->getSprite());
    
    
    

}
