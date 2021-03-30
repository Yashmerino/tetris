#ifndef _TETRIS_H_
#define _TETRIS_H_
#include <SFML/Graphics.hpp>

class Tetris
{
public:
	Tetris();

	~Tetris();

	bool checkBounds();

	bool checkHover(sf::Sprite& sprite, sf::RenderWindow& window);

	void resetGame(bool& beginGame, bool& gameOver, int& score, int& colorNum);

	void checkifGameOver(bool& gameOver);

	void run();

private:
	sf::Texture tiles;
	sf::Sprite figure;

private:
	static const int HEIGHT = 20; //Height and width for the field
	static const int WIDTH = 10;

	int field[HEIGHT][WIDTH] = {0}; //Initializing field

private:
	int figures[7][4] //Initializing figures
	{
		{0, 2, 4, 6},
		{0, 2, 4, 5},
		{1, 3, 5, 4},
		{0, 1, 2, 3},
		{0, 2, 3, 5},
		{1, 2, 3, 4},
		{0, 2, 3, 4},
	};

	struct Point //Creatting figures
	{
		int x, y;
	} a[4], b[4], temp[4];

private:
	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Texture buttonsTextures[4];
	sf::Sprite buttons[2];

private:
	sf::Font font;
	sf::Text scoreText;
};

#endif