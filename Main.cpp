#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <iostream>

int main()
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

    return 0;
}