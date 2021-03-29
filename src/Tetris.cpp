#include "../headers/Tetris.h"
#include <SFML/Graphics.hpp>

Tetris::Tetris()
{
    tiles.loadFromFile("img/tiles.png"); //Loading and setting tiles
    figure.setTexture(tiles);
    figure.setTextureRect(sf::IntRect(60, 0, 30, 30));
}

Tetris::~Tetris()
{

}

void Tetris::run()
{
    sf::RenderWindow window(sf::VideoMode(480, 640), "Tetris"); //Creatting window

    int dx = 0; //Horizontal movement
    bool rotate = false; //Rotation

    bool beginGame = true; //Start of the game

    float timer = 0.0f;
    float delay = 0.6f;
    sf::Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Up) //If "up" pressed then rotate the figure
                    rotate = true;
                else if (event.key.code == sf::Keyboard::Left) //Move to the left
                    dx -= 1;
                else if (event.key.code == sf::Keyboard::Right) //Move to the right
                    dx += 1;
        }

        int n = 4;

        if (beginGame) //If it's the first figure spawned
        {
            beginGame = false; //After game starts changing beginGame variable's value

            for (int i = 0; i < 4; i++) //Constructing the chosen figure and choosing it's position (n variable)
            {
                a[i].x = figures[n][i] % 2;
                a[i].y = figures[n][i] / 2;
            }
        }

        for (int i = 0; i < 4; i++) //Horizontal movement
            a[i].x += dx;

        if (timer > delay) //Vertical movement
        {
            timer = 0;

            for (int i = 0; i < 4; i++)
                a[i].y += 1;
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < 4; i++) //Drawing the figure
        {
            figure.setPosition(a[i].x * 30, a[i].y * 30);
            window.draw(figure);
        }
        
        dx = 0; //Resetting horizontal movement variable
        rotate = false; //Resetting rotation variable

        window.display();
    }
}