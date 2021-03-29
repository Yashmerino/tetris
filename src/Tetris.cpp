#include "../headers/Tetris.h"
#include <SFML/Graphics.hpp>

Tetris::Tetris()
{

}

Tetris::~Tetris()
{

}

void Tetris::run()
{
    sf::RenderWindow window(sf::VideoMode(480, 640), "Tetris");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
}