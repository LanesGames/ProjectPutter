#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
    std::cout << "You should see a window that opens as well as this writing to console..."
        << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(60);

    Game game(window);

    //run the init function of the game class and check it all initialises ok
    if (!game.init())
    {
        return 0;
    }

    // A Clock starts counting as soon as it's created
    sf::Clock clock;

    while (window.isOpen())
    {
        //Check all window events
        sf::Event event;

        //calculate delta time
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        //'process inputs' element of the game loop
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
                game.keyPressed(event);

            if (event.type == sf::Event::KeyReleased)
                game.keyReleased(event);

            if (event.type == sf::Event::MouseButtonPressed)
            {
                game.mouseClicked(event);
            }
        }

        //'update' element of the game loop
        game.update(dt);
        window.clear(sf::Color::Black);

        //'render' element of the game loop
        game.render();
        window.display();
    }

    return 0;
}