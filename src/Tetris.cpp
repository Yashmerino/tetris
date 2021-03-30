#include "../headers/Tetris.h"
#include <SFML/Graphics.hpp>
#include <ctime>

Tetris::Tetris()
{
    tiles.loadFromFile("img/tiles.png"); //Loading and setting tiles
    figure.setTexture(tiles);
    figure.setTextureRect(sf::IntRect(60, 0, 30, 30));

    backgroundTexture.loadFromFile("img/main.png");
    background.setTexture(backgroundTexture);
}

Tetris::~Tetris()
{

}

bool Tetris::checkBounds() //Checks if the figure is not out of bounds
{
    for (int i = 0; i < 4; i++)
        if (a[i].x >= WIDTH || a[i].x < 0 || a[i].y >= HEIGHT)
            return false;
        else if (field[a[i].y][a[i].x])
            return false;

    return true;
}

void Tetris::run()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(480, 640), "Tetris"); //Creatting window

    int dx = 0; //Horizontal movement
    bool rotate = false; //Rotation

    bool beginGame = true; //Start of the game

    int colorNum = 1 + rand() % 3;

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
                else if (event.key.code == sf::Keyboard::Down) //Increase the fall speed
                    delay = 0.02f;
        }

        if (beginGame) //If it's the first figure spawned
        {
            beginGame = false; //After game starts changing beginGame variable's value

            int n = rand() % 7;

            for (int i = 0; i < 4; i++) //Constructing the chosen figure and choosing it's position (n variable)
            {
                a[i].x = figures[n][i] % 2;
                a[i].y = figures[n][i] / 2;
            }
        }

        for (int i = 0; i < 4; i++) //Horizontal movement
        {
            b[i] = a[i];

            a[i].x += dx;
        }

        if (!checkBounds()) //Checking if figure isn't out of bounds on X coordinate
            for (int i = 0; i < 4; i++)
                a[i] = b[i];

        if (timer > delay) //Vertical movement
        {
            for (int i = 0; i < 4; i++)
            {
                b[i] = a[i];

                a[i].y += 1;
            }


            if (!checkBounds()) //Checking if figure isn't out of bounds on Y coordinate
            {
                for (int i = 0; i < 4; i++)
                    field[b[i].y][b[i].x] = colorNum;

                colorNum = 1 + rand() % 3;
                int n = rand() % 7;

                for (int i = 0; i < 4; i++)
                {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }

            timer = 0; //Resetting timer value
        }

        if (rotate)
        {
            Point temp = a[1];

            for (int i = 0; i < 4; i++)
            {
                b[i] = a[i];

                int x = a[i].y - temp.y;
                int y = a[i].x - temp.x;
                a[i].x = temp.x - x;
                a[i].y = temp.y + y;
            }

            if (!checkBounds()) //Checking if figure isn't out of bounds after rotating it
                for (int i = 0; i < 4; i++)
                    a[i] = b[i];
        }

        int k = HEIGHT - 1; //Checks if the line is full and removing it if it's true
        for (int i = HEIGHT - 1; i > 0; i--)
        {
            int count = 0;
            for (int j = 0; j < WIDTH; j++)
            {
                if (field[i][j]) count++;
                field[k][j] = field[i][j];
            }
            if (count < WIDTH) k--;
        }

        dx = 0; //Resetting horizontal movement variable
        rotate = false; //Resetting rotation variable
        delay = 0.6f; //Resetting fall speed

        window.clear(sf::Color::White);
        window.draw(background);

        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
            {
                if (field[i][j] == 0)
                    continue;

                figure.setTextureRect(sf::IntRect(field[i][j] * 30, 0, 30, 30));
                figure.setPosition(j * 30, i * 30);
                figure.move(21.f, 20.f);
                window.draw(figure);
            }

        for (int i = 0; i < 4; i++) //Drawing the figure
        {
            figure.setTextureRect(sf::IntRect(colorNum * 30, 0, 30, 30));
            figure.setPosition(a[i].x * 30, a[i].y * 30);
            figure.move(21.f, 20.f);
            window.draw(figure);
        }
     
        window.display();
    }
}