#include "fSnakeGame.h"
#include <unistd.h>

using namespace std;

CharPosition::CharPosition(int col, int row)
{
	x = col;
	y = row;
}

CharPosition::CharPosition()
{
	x = 0;
	y = 0;
}

fSnakeGame::fSnakeGame()
{
	// variables initialisation:
	partchar = 'x'; // character to represent the snake
	edgechar = (char)219; // full rectangle on the key table
	fruitchar = '*';
	poisonchar = '#';
	fruit.x = 0;
	fruit.y = 0;
	poison.x = 0;
	poison.y = 0;
	del = 110000;
	bool bEatsFruit = 0;
	bool bEatsPoison = 0;
	direction = 'l';
	srand(time(NULL));

	InitGameWindow();
	PositionFruit();
	PositionPoison();
	DrawWindow();
	DrawSnake();
	PrintScore();
	PrintMission();

	refresh();
}

fSnakeGame::~fSnakeGame()
{
	nodelay(stdscr, false);
	getch();
	endwin();
}

// initialise the game window
void fSnakeGame::InitGameWindow()
{
	initscr(); // initialise the screen
	nodelay(stdscr,TRUE);
	keypad(stdscr, true); // initialise the keyboard: we can use arrows for directions
	noecho(); // user input is not displayed on the screen
	curs_set(0); // cursor symbol is not not displayed on the screen (Linux)
	return;
}

// draw the game window
void fSnakeGame::DrawWindow()
{
	for (int i = 0; i < width; i++) // draws top
	{
		move(0, i);
		addch(edgechar);
	}

	for (int i = 0; i < width; i++) // draws bottom
	{
		move(width - 2, i);
		addch(edgechar);
	}

	for (int i = 0; i < height-1; i++) // draws left side
	{
		move(i, 0);
		addch(edgechar);
	}

	for (int i = 0; i < height-1; i++) // draws right side
	{
		move(i, height-1);
		addch(edgechar);
	}
	return;
}

// draw snake's body
void fSnakeGame::DrawSnake()
{
	for (int i = 0; i < 3; i++)
	{
		snake.push_back(CharPosition(10+i, 10));
	}

	for (int i = 0; i < snake.size(); i++)
	{
		move(snake[i].y, snake[i].x);
		addch(partchar);
	}
	return;
}

// print score at bottom of window
void fSnakeGame::PrintScore()
{
	move(0, 22);
	printw("Score Board");
	move(1, 22);
	printw("B : %d / %d", nowsize, maxsize);
	move(2, 22);
	printw("+ : %d", fruitcnt);
	move(3, 22);
	printw("- : %d", poisoncnt);
	move(4, 22);
	printw("G : ");
	return;
}

void fSnakeGame::PrintMission()
{
	move(7, 22);
	printw("Mission");
	move(8, 22);
	printw("B : 10");
	move(8, 29);
	if(maxsize >= 10)
		printw("(v)");
	else
		printw("( )");
	move(9, 22);
	printw("+ : 5");
	move(9, 28);
	if(fruitcnt >= 5)
		printw("(v)");
	else
		printw("( )");
	move(10, 22);
	printw("- : 2");
	move(10, 28);
	if(poisoncnt >= 2)
		printw("(v)");
	else
		printw("( )");
	move(11, 22);
	printw("G : 1");
	return;
}

// position a new fruit in the game window
void fSnakeGame::PositionFruit()
{
	while(1)
	{
		int tmpx = rand()%width+1; // +1 to avoid the 0
		int tmpy = rand()%height+1;

		// check that the fruit is not positioned on the snake
		for (int i = 0; i < snake.size(); i++)
		{
			if (snake[i].x == tmpx && snake[i].y == tmpy)
			{
				continue; // if true, ignore the following and go back to the beginning of function
			}
		}

		// check that the fruit is positioned within the game window
		if (tmpx >= width-2 || tmpy >= height-3)
		{
			continue; // if true, ignore the following and go back to the beginning of function
		}

		// if the coordinates are valid, add fruit in the window
		fruit.x = tmpx;
		fruit.y = tmpy;
		break;
	}

	move(fruit.y, fruit.x);
	addch(fruitchar);
	refresh();
}

void fSnakeGame::PositionPoison()
{
	while(1)
	{
		int tmpx = rand()%width+1; // +1 to avoid the 0
		int tmpy = rand()%height+1;

		// check that the poison is not positioned on the snake
		for (int i = 0; i < snake.size(); i++)
		{
			if (snake[i].x == tmpx && snake[i].y == tmpy)
			{
				continue; // if true, ignore the following and go back to the beginning of function
			}
		}

		// check that the poison is positioned within the game window
		if (tmpx >= width-2 || tmpy >= height-3)
		{
			continue; // if true, ignore the following and go back to the beginning of function
		}

		// if the coordinates are valid, add fruit in the window
		poison.x = tmpx;
		poison.y = tmpy;
		break;
	}

	move(poison.y, poison.x);
	addch(poisonchar);
	refresh();
}


// set game over situations
bool fSnakeGame::FatalCollision()
{
	// if the snake hits the edge of the window
	if (snake[0].x == 0 || snake[0].x == width-1 || snake[0].y == 0 || snake[0].y == height-2)
	{
		return true;
	}

	// if the snake collides into himself
	for (int i = 2; i < snake.size(); i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			return true;
		}
	}

	if (snake.size() < 3)
	{
		return true;
	}

	return false;
}

// define behaviour when snake eats the fruit
bool fSnakeGame::GetsFruit()
{
	if (snake[0].x == fruit.x && snake[0].y == fruit.y)
	{
		PositionFruit();
		fruitcnt++;
		nowsize = snake.size() + 1;
		if(maxsize <= snake.size())
		{
			maxsize++;
		}
		PrintScore();
		PrintMission();

		return bEatsFruit = true;
	}
	else
	{
		return bEatsFruit = false;
	}
	return bEatsFruit;
}

// define behaviour when snake eats the poison
bool fSnakeGame::GetsPoison()
{
	if (snake[0].x == poison.x && snake[0].y == poison.y)
	{
		PositionPoison();
		poisoncnt++;
		nowsize = snake.size() - 1;
		PrintScore();
		PrintMission();

		return bEatsPoison = true;
	}
	else
	{
		return bEatsPoison = false;
	}
	return bEatsPoison;
}


// define snake's movements
void fSnakeGame::MoveSnake()
{
	int KeyPressed = getch();
	switch(KeyPressed)
	{
		case KEY_LEFT:
			if (direction != 'r')
			{ direction = 'l'; }
			break;
		case KEY_RIGHT:
			if (direction != 'l')
			{ direction = 'r'; }
			break;
		case KEY_UP:
			if (direction != 'd')
			{ direction = 'u'; }
			break;
		case KEY_DOWN:
			if (direction != 'u')
			{ direction = 'd'; }
			break;
		case KEY_BACKSPACE:
			direction = 'q'; // key to quit the game
			break;
	}

	// the snake doesn't eat fruit, remains same size
	if (!bEatsFruit)
	{
		move(snake[snake.size()-1].y, snake[snake.size()-1].x); // moves at the end of the tail
		printw(" "); // add empty ch to remove last character
		refresh();
		snake.pop_back(); // removes the last element in the vector, reducing the container size by one
	}

	if (bEatsPoison)
	{
		move(snake[snake.size()-1].y, snake[snake.size()-1].x); // moves at the end of the tail
		printw(" "); // add empty ch to remove last character
		refresh();
		snake.pop_back(); // removes the last element in the vector, reducing the container size by one
	}

	// the snake moves and we add an extra character at the beginning of the vector
	// add a head and initialise new coordinates for CharPosition according to the direction input
	if (direction == 'l')
	{ snake.insert(snake.begin(), CharPosition(snake[0].x-1, snake[0].y)); }
	else if (direction == 'r')
	{ snake.insert(snake.begin(), CharPosition(snake[0].x+1, snake[0].y)); }
	else if (direction == 'u')
	{ snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y-1)); }
	else if (direction == 'd')
	{ snake.insert(snake.begin(), CharPosition(snake[0].x, snake[0].y+1)); }

	// move to the new CharPosition coordinates
	move(snake[0].y, snake[0].x);
	addch(partchar); // add a new head
	refresh();
	return;
}

void fSnakeGame::PlayGame()
{
    while(1)
    {
        if (FatalCollision())
        {
            move(10, 6);
            printw("GAME OVER");
            break;
        }

        GetsFruit();
        GetsPoison();
        MoveSnake();

        if (direction=='q') //exit
        {
        	break;
        }

        usleep(del); // delay
    }
}
