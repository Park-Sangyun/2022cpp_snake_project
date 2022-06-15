#include "snakeGame.h"

void playGame();
int ready();
int AskUserToPlayAgain();
void ClearCentre();
int UserInput();

int main ()
{
	if (ready() == 'y')
	do {
		{
			snakeGame NewSnake;
			NewSnake.playGame();
		}
	}
	while (AskUserToPlayAgain() == 'y');
	return 0;
}

void ClearCentre(float x, float y)
{
	clear();
	initscr();
	noecho();
	move(x, y);
}

int UserInput()
{
	int UserInput = getch();
	refresh();
	endwin();
	clear();

	return UserInput;
}

int ready()
{
	ClearCentre(10, 1);
	printw("Are you ready? (y/n)");
	return UserInput();
}

int AskUserToPlayAgain()
{
	move(10, 6);
	printw("try again?");
  move(11, 3);
  printw("     (y/n)     ");
	return UserInput();
}
