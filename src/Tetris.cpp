#include "../headers/Tetris.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>

Tetris::Tetris()
{
    tiles.loadFromFile("img/tiles.png"); //Loading and setting tiles
    figure.setTexture(tiles);
    figure.setTextureRect(sf::IntRect(60, 0, 30, 30));

    backgroundTexture.loadFromFile("img/main.png"); //Loading and setting background
    background.setTexture(backgroundTexture);

    buttonsTextures[0].loadFromFile("img/new.png"); //Loading and setting buttons
    buttonsTextures[1].loadFromFile("img/newHover.png");
    buttonsTextures[2].loadFromFile("img/exit.png");
    buttonsTextures[3].loadFromFile("img/exitHover.png");

    buttons[0].setTexture(buttonsTextures[0]);
    buttons[1].setTexture(buttonsTextures[2]);

    buttons[0].setPosition(360.f, 525.f); //Setting buttons' positions
    buttons[1].setPosition(410.f, 495.f);

    font.loadFromFile("fonts/ac.ttf"); //Loading the font

    scoreText.setFont(font); //Setting score text
    scoreText.setString("0");
    scoreText.setColor(sf::Color::Black);
    scoreText.setCharacterSize(42.f);
    scoreText.setOrigin(sf::Vector2f(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2));
    scoreText.setPosition(400.f, 77.f);

    music.openFromFile("audio/music.wav"); //Setting music
    music.setLoop(true);
    
    sounds[0].loadFromFile("audio/fall.wav"); //Setting sound effects
    sounds[1].loadFromFile("audio/rotate.wav");
    sounds[2].loadFromFile("audio/line.wav");
    sounds[3].loadFromFile("audio/finish.wav");
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

bool Tetris::checkHover(sf::Sprite& sprite, sf::RenderWindow& window) //Checks if the mouse is hovering a sprite
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::FloatRect bounds = sprite.getGlobalBounds();

    return bounds.contains(mousePos);
}

void Tetris::resetGame(bool& beginGame, bool& gameOver, int& score, int& colorNum)
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            field[i][j] = 0;

    beginGame = true;
    gameOver = false;
    colorNum = 1 + rand() % 3;

    score = 0;
    scoreText.setString(std::to_string(score));
    scoreText.setOrigin(sf::Vector2f(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2));
    scoreText.setPosition(400.f, 77.f);

    music.openFromFile("audio/music.wav");
    music.play();
}

void Tetris::checkifGameOver(bool& gameOver)
{
    for (int i = 0; i < WIDTH; i++)
        if (field[0][i])
        {
            gameOver = true;
            music.pause();
            audio.setBuffer(sounds[3]);
            audio.play();
            break;
        }
        else
        {
            gameOver = false;
            break;
        }
}

void Tetris::run()
{
    srand(time(NULL));

    music.play();

    sf::RenderWindow window(sf::VideoMode(480, 640), "Tetris", sf::Style::Close); //Creatting window

    int dx = 0; //Horizontal movement
    bool rotate = false; //Rotation

    bool beginGame = true; //Start of the game
    bool gameOver = false;

    int colorNum = 1 + rand() % 3;
    int score = 0;
    int currentFigure = 0;
    int nextFigure = 0;
    int nextColorNum = 0;

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

            if (event.type == sf::Event::MouseMoved && checkHover(buttons[0], window)) //If new button hovered
                buttons[0].setTexture(buttonsTextures[1]);
            else
                buttons[0].setTexture(buttonsTextures[0]);
            if (event.type == sf::Event::MouseMoved && checkHover(buttons[1], window)) //If exit button hovered
                buttons[1].setTexture(buttonsTextures[3]);
            else
                buttons[1].setTexture(buttonsTextures[2]);

            if (event.type == sf::Event::MouseButtonPressed && checkHover(buttons[0], window)) //Reset game if reset button pressed
                resetGame(beginGame, gameOver, score, colorNum);
            else if (event.type == sf::Event::MouseButtonPressed && checkHover(buttons[1], window))  //Exit if exit button pressed
                window.close();
        }

        if (beginGame) //If it's the first figure spawned
        {
            beginGame = false; //After game starts changing beginGame variable's value

            currentFigure = rand() % 7;
            nextFigure = rand() % 7;
            nextColorNum = 1 + rand() % 3;

            for (int i = 0; i < 4; i++) //Constructing the chosen figure and choosing it's position
            {
                a[i].x = figures[currentFigure][i] % 2;
                a[i].y = figures[currentFigure][i] / 2;

                next[i].x = figures[nextFigure][i] % 2;
                next[i].y = figures[nextFigure][i] / 2;
            }
        }

        if(!gameOver)
        for (int i = 0; i < 4; i++) //Horizontal movement
        {
            b[i] = a[i];

            a[i].x += dx;
        }

        if (!checkBounds() && !gameOver) //Checking if figure isn't out of bounds on X coordinate
            for (int i = 0; i < 4; i++)
                a[i] = b[i];

        if (timer > delay && !gameOver) //Vertical movement
        {
            for (int i = 0; i < 4; i++)
            {
                b[i] = a[i];

                a[i].y += 1;
            }

            if (!checkBounds()) //Checking if figure isn't out of bounds on Y coordinate
            {
                audio.setBuffer(sounds[0]);
                audio.play();

                for (int i = 0; i < 4; i++)
                    field[b[i].y][b[i].x] = colorNum;

                checkifGameOver(gameOver);

                if (!gameOver)
                {
                    colorNum = nextColorNum;
                    nextColorNum = 1 + rand() % 3;
                    currentFigure = nextFigure;
                    nextFigure = rand() % 7;

                    for (int i = 0; i < 4; i++)
                    {  
                        a[i].x = figures[currentFigure][i] % 2;
                        a[i].y = figures[currentFigure][i] / 2;

                        next[i].x = figures[nextFigure][i] % 2;
                        next[i].y = figures[nextFigure][i] / 2;
                    }
                }

                for (int i = 0; i < 4; i++)
                    if (field[a[i].y][a[i].x] != 0)
                    {
                        music.pause();
                        audio.setBuffer(sounds[3]);
                        audio.play();
                        gameOver = true;
                    }
            }

            timer = 0; //Resetting timer value
        }

        if (rotate && !gameOver && currentFigure != 3) //Rotation
        {
            audio.setBuffer(sounds[1]);
            audio.play();

            Point temp = a[1];

            for (int i = 0; i < 4; i++) //Some very hard math formula
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
            else
            {
                audio.setBuffer(sounds[2]);
                audio.play();

                score += 100;
                scoreText.setString(std::to_string(score));
                scoreText.setOrigin(sf::Vector2f(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2));
                scoreText.setPosition(400.f, 77.f);
            }
        }

        dx = 0; //Resetting horizontal movement variable
        rotate = false; //Resetting rotation variable
        delay = 0.6f; //Resetting fall speed

        window.clear(sf::Color::White);
        window.draw(background);
        window.draw(scoreText);
        for (int i = 0; i < 2; i++)
            window.draw(buttons[i]);

        for (int i = 0; i < HEIGHT; i++) //Drawing the figures that are already setted
            for (int j = 0; j < WIDTH; j++)
            {
                if (field[i][j] == 0)
                    continue;

                figure.setTextureRect(sf::IntRect(field[i][j] * 30, 0, 30, 30));
                figure.setPosition(j * 30, i * 30);
                figure.move(21.f, 20.f);
                window.draw(figure);
            }

        for (int i = 0; i < 4; i++) //Drawing the next figure
        {
            figure.setTextureRect(sf::IntRect(nextColorNum * 30, 0, 30, 30));
            figure.setPosition(next[i].x * 30, next[i].y * 30);
            figure.move(374.f, 182.f);
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
