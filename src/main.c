#include <curses.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum state {
  GAME_BUSY,
  GAME_PLAYER_1,
  GAME_PLAYER_2,
  GAME_STALEMATE
} state;

typedef struct grid {
  state gamestate;
  const int rows;
  const int columns;
  char **field;
} grid;

const char *congratulations[] = {"Well done ",
                                 "Amazing game, ",
                                 "I could not have done it any better ",
                                 "Slick move at the start to claim the win ",
                                 "I should've put a fiver on ",
                                 "Stop it, he's already dead ",
                                 "I cannot believe you actually did it, ",
                                 "Mom would be proud of you ",
                                 "What a save, ",
                                 "FINISH HIM "};

static grid initialize_grid(const int rows, const int columns) {
  grid new_grid = {.gamestate = GAME_BUSY,
                   .rows = rows,
                   .columns = columns,
                   .field = calloc(rows, sizeof(char *))};

  for (int i = 0; i < rows; i++) {
    (new_grid.field)[i] = calloc(columns, sizeof(char));
    for (int j = 0; j < columns; j++) {
      (new_grid.field)[i][j] = '.';
    }
  }

  return new_grid;
}

static void print_endscreen(const int state) {
  int option = rand() % 10;
  switch (state) {
  case GAME_PLAYER_1:
    printf("%s Player 1!\n", congratulations[option]);
    break;
  case GAME_PLAYER_2:
    printf("%s Player 2!\n", congratulations[option]);
    break;
  case GAME_STALEMATE:
    printf("We can't settle for a draw, can we?\n");
    break;
  default:
    printf("%s\n", congratulations[option]);
    break;
  }
}

static void play_game() {
  grid board = initialize_grid(3, 3);
  while (board.gamestate == GAME_BUSY) {
    break;
  }
  print_endscreen(board.gamestate);
  return;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  char option[64];

  while (true) {
    printf("Do you want to [ play | quit ] ? ");
    scanf("%s", option);

    if (!strcmp(option, "play")) {
      printf("Let's play some tic-tac-toe!\n");
      play_game();
    } else if (!strcmp(option, "quit")) {
      printf("We should do this again some time\n");
      break;
    } else {
      printf("Invalid option, try again!\n");
    }

    printf("Press Any Key to Continue\n");
    while (getchar() != '\n')
      ;
    getchar();
  }
}