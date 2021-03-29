#include "../headers/Tetris.h"
#include <SFML/Graphics.hpp>

Tetris::Tetris()
{
    tiles.loadFromFile("img/tiles.png");
    figure.setTexture(tiles);
    figure.setTextureRect(sf::IntRect(60, 0, 30, 30));
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

        int n = 4;

        for (int i = 0; i < 4; i++)
        {
            a[i].x = figures[n][i] % 2;
            a[i].y = figures[n][i] / 2;
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < 4; i++)
        {
            figure.setPosition(a[i].x * 30, a[i].y * 30);
            window.draw(figure);
        }
        
        window.display();
    }
}