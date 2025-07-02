#include <curses.h>
#include <ncurses.h>
#include <stdatomic.h>
#include <stdint.h>

#define BORDER_SIZE (1)

#define CEL_HEIGHT_INNER    (3)
#define CEL_WIDTH_INNER     (3 * CEL_HEIGHT_INNER)

#define CEL_HEIGHT_OUTER    (CEL_HEIGHT_INNER + BORDER_SIZE)
#define CEL_WIDTH_OUTER     (CEL_WIDTH_INNER  + BORDER_SIZE)

#define BOARD_HEIGHT        (3 * CEL_HEIGHT_OUTER)
#define BOARD_WIDTH         (3 * CEL_WIDTH_OUTER )

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
  for (int w = 1; w < BOARD_WIDTH; w++)
  {
    // Create horizontal lines
    wmove(board, 1 * CEL_HEIGHT_OUTER, w);
    waddch(board, ACS_HLINE);
    wmove(board, 2 * CEL_HEIGHT_OUTER, w);
    waddch(board, ACS_HLINE);
    wmove(board, 3 * CEL_HEIGHT_OUTER, w);
    waddch(board, ACS_HLINE);

    // Create top and bottom bar
    if (w % CEL_WIDTH_OUTER == 0)
    {
      wmove(board, 0, w);
      waddch(board, ACS_TTEE);
      wmove(board, BOARD_HEIGHT, w);
      waddch(board, ACS_BTEE);
    }
  }

  for (int h = 1; h < BOARD_HEIGHT; h++)
  {
    // Create vertical lines
    wmove(board, h, 1 * CEL_WIDTH_OUTER);
    waddch(board, ACS_VLINE);
    wmove(board, h, 2 * CEL_WIDTH_OUTER);
    waddch(board, ACS_VLINE);
    wmove(board, h, 3 * CEL_WIDTH_OUTER);
    waddch(board, ACS_VLINE);

    // Create left and right bar
    if (h % CEL_HEIGHT_OUTER == 0)
    {
      wmove(board, h, 0);
      waddch(board, ACS_LTEE);
      wmove(board, h, BOARD_WIDTH);
      waddch(board, ACS_RTEE);
    }
  }

  // Create crossing lines
  for (int w = CEL_WIDTH_OUTER; w < BOARD_WIDTH; w += CEL_WIDTH_OUTER)
  {
    for (int h = CEL_HEIGHT_OUTER; h < BOARD_HEIGHT;
         h += CEL_HEIGHT_OUTER)
    {
      wmove(board, h, w);
      waddch(board, ACS_PLUS);
    }
  }
}

void create_board_start(WINDOW *board)
{
  for (int w = CEL_WIDTH_OUTER / 2; w < BOARD_WIDTH; w += CEL_WIDTH_OUTER)
  {
    for (int h = CEL_HEIGHT_OUTER / 2; h < BOARD_HEIGHT; h += CEL_HEIGHT_OUTER)
    {
      wmove(board, h, w);
      waddch(board, '0');
    }
  }
}

WINDOW *create_board(void)
{
  // Horizontal scales about 1/3 less then vertical
  WINDOW *board = newwin(BOARD_HEIGHT + BORDER_SIZE, BOARD_WIDTH + BORDER_SIZE, 0, 0);
  keypad(board, TRUE);
  box(board, 0, 0);

  create_board_pattern(board);
  create_board_start(board);
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
