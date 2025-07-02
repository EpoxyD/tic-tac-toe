#include <ncurses.h>
#include <stdatomic.h>
#include <stdint.h>

#define CEL_HEIGHT 3
#define CEL_WIDTH (CEL_HEIGHT * 3)

#define BOARD_HEIGHT (3 * CEL_HEIGHT + 1)
#define BOARD_WIDTH (3 * CEL_WIDTH + 1)

int startx = 0;
int starty = 0;

char *choices[] = {
    "Choice 1", "Choice 2", "Choice 3", "Choice 4", "Exit",
};
int n_choices = sizeof(choices) / sizeof(char *);

void init_screen(void)
{
  initscr();
  clear();
  noecho();
  cbreak();

  curs_set(FALSE);
}

void create_board_pattern(WINDOW *board)
{
  for (int w = 1; w < BOARD_WIDTH - 1; w++)
  {
    // Create horizontal lines
    wmove(board, CEL_HEIGHT * 1, w);
    waddch(board, ACS_HLINE);
    wmove(board, CEL_HEIGHT * 2, w);
    waddch(board, ACS_HLINE);

    // Create top and bottom bar
    if ((w % CEL_WIDTH == 0))
    {
      wmove(board, 0, w);
      waddch(board, ACS_TTEE);
      wmove(board, BOARD_HEIGHT - 1, w);
      waddch(board, ACS_BTEE);
    }
  }

  for (int h = 1; h < BOARD_HEIGHT - 1; h++)
  {
    // Create vertical lines
    wmove(board, h, CEL_WIDTH * 1);
    waddch(board, ACS_VLINE);
    wmove(board, h, CEL_WIDTH * 2);
    waddch(board, ACS_VLINE);

    // Create left and right bar
    if ((h % CEL_HEIGHT == 0))
    {
      wmove(board, h, 0);
      waddch(board, ACS_LTEE);
      wmove(board, h, BOARD_WIDTH - 1);
      waddch(board, ACS_RTEE);
    }
  }

  // Create crossing lines
  for (int w = CEL_WIDTH; w < BOARD_WIDTH - 1; w += CEL_WIDTH)
  {
    for (int h = CEL_HEIGHT; h < BOARD_HEIGHT - 1; h += CEL_HEIGHT)
    {
      wmove(board, h, w);
      waddch(board, ACS_PLUS);
    }
  }
}

WINDOW *create_board(void)
{
  // Horizontal scales about 1/3 less then vertical
  WINDOW *board = newwin(BOARD_HEIGHT, BOARD_WIDTH, 0, 0);
  keypad(board, TRUE);
  box(board, 0, 0);

  create_board_pattern(board);
  wrefresh(board);

  return board;
}

int main()
{
  init_screen();

  WINDOW *board = create_board();
  wgetch(board);

  endwin();
}
