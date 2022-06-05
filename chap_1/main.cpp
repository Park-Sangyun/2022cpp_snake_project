#include <iostream>
#include <ncurses.h>

using namespace std;

int main()
{
  WINDOW *board;

  initscr();
  resize_term(25, 40);

  border('*', '*', '*', '*', '*', '*', '*', '*');
  refresh();
  getch();

  board = newwin(21, 21, 2, 2);
  wborder(board, '1', '1', '1', '1', '2', '2', '2', '2');
  wrefresh(board);

  getch();
  delwin(board);
  endwin();

  return 0;
}
