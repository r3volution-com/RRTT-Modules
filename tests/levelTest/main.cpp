#include <SFML/Graphics.hpp>
#include <vector>

#include "../../Level.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(480, 320), "view demo");
   
    // create player, at the screen center
    sf::RectangleShape player(sf::Vector2f(20, 20));
    player.setFillColor(sf::Color::Red);
    player.setOrigin(10, 10);
    player.setPosition(240, 160);
    const float player_speed = 100;

    // create a bunch of objects
    Level *level = new Level();
    std::vector<sf::RectangleShape*> *objects = new std::vector<sf::RectangleShape*>();
    
    level->populate(objects, 310, 50);
    level->populate(objects, 100, 200);
    level->populate(objects, 250, 160);
    level->populate(objects, 10, 280);
    level->populate(objects, 70, 30);
    level->populate(objects, 120, 50);

    // we create our custom view
    sf::View player_view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
   
    sf::Clock clock;
    bool running = true;
    sf::Event event;
    while (running)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                running = false;
        }

        // moving player
        float frametime = clock.getElapsedTime().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0, -player_speed * frametime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0, player_speed * frametime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-player_speed * frametime, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(player_speed * frametime, 0);
   
        clock.restart();

        // we keep our view centered on the player
        player_view.setCenter(player.getPosition());
        window.setView(player_view);

        // rendering entities
        window.draw(player);
        for (int i=0; i<objects->size();i++)
        {
            window.draw(*objects->at(i));
        }
        
        window.display();
        window.clear();
    }
    window.close();
    return 0;
}