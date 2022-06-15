#include <iostream>
#include <vector>
#include <ncurses.h>
#include <unistd.h>
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

struct position
{
	int x, y;
	position(int col, int row);
	position();
};

class snakeGame
{
private:
	int nowsize = 3, bestsize = 3, wall = 21, fruitcnt = 0, poisoncnt = 0;
	char direction, head = 'o', body = 'x', fruitshape = '*', poisonshape = '#';
	bool eatFruit = false;
	bool eatPoison = false;
  bool dirFail = false;
	position fruit;
	position poison;
	std::vector<position> snake;

	void InitGameWindow();
	void DrawWindow();
	void DrawSnake();
	void PrintScore();
	void PrintMission();
	void PositionFruit();
	void PositionPoison();
	bool fail();
	void MoveSnake();
	bool GetsFruit();
	bool GetsPoison();

public:
	snakeGame();
	~snakeGame();
	void playGame();
};

#endif
