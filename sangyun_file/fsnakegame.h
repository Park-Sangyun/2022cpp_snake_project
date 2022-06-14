#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#ifndef FSNAKEGAME_H
#define FSNAKEGAME_H

struct CharPosition
{
	int x, y;
	CharPosition(int col, int row);
	CharPosition();
};

class fSnakeGame
{
private:
	int nowsize = 3, maxsize = 3, del, width = 21, height = 21, fruitcnt = 0, poisoncnt = 0;
	char direction, partchar, edgechar, fruitchar, poisonchar;
	// partchar is the character representing the snake's body
	// edgechar is the character representing the edge of the game window
	// fruitchar is the character representing the fruit
	// del stands for delay
	bool bEatsFruit;
	bool bEatsPoison;
	CharPosition fruit; // need to clarify this combination
	CharPosition poison;
	std::vector<CharPosition> snake; // represent the snake's body

	void InitGameWindow();
	void DrawWindow();
	void DrawSnake();
	void PrintScore();
	void PositionFruit();
	void PositionPoison();
	bool FatalCollision();
	void MoveSnake();
	bool GetsFruit();
	bool GetsPoison();

public:
	fSnakeGame();
	~fSnakeGame(); // destructor for cleanup and memory deallocation
	void PlayGame();
};

#endif
