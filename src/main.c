#include <ncurses.h>
#include <stdint.h>

#define CEL_HEIGHT      3
#define CEL_WIDTH       (CEL_HEIGHT * 3)

#define BOARD_HEIGHT    (3 * CEL_HEIGHT + 1)
#define BOARD_WIDTH     (3 * CEL_WIDTH  + 1)

int startx = 0;
int starty = 0;

char *choices[] = {
    "Choice 1", "Choice 2", "Choice 3", "Choice 4", "Exit",
};
int n_choices = sizeof(choices) / sizeof(char *);

void init_screen(void) {
  initscr();
  clear();
  noecho();
  cbreak();

  curs_set(FALSE);
}

void create_board_pattern(WINDOW *board) {
  // Create top and bottom bar:
  for (int w = CEL_WIDTH; w < BOARD_WIDTH - 1; w += CEL_WIDTH) {
    wmove(board, 0, w);
    waddch(board, ACS_TTEE);
    wmove(board, BOARD_HEIGHT - 1, w);
    waddch(board, ACS_BTEE);
  }

  // Create left and right bar
  for (int h = CEL_HEIGHT; h < BOARD_HEIGHT - 1; h += CEL_HEIGHT) {
    wmove(board, h, 0);
    waddch(board, ACS_LTEE);
    wmove(board, h, BOARD_WIDTH - 1);
    waddch(board, ACS_RTEE);
  }
}

WINDOW *create_board(void) {
  // Horizontal scales about 1/3 less then vertical
  WINDOW *board = newwin(BOARD_HEIGHT, BOARD_WIDTH, 0, 0);
  keypad(board, TRUE);
  box(board, 0, 0);

  create_board_pattern(board);
  wrefresh(board);

  return board;
}

int main() {
  init_screen();

  WINDOW *board = create_board();
  wgetch(board);

  endwin();
}
