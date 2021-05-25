#include <curses.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
  char ** field;
} grid;

static grid initialize_grid(const int rows, const int columns) {
  grid new_grid = {
    .gamestate = GAME_BUSY,
    .rows = rows,
    .columns = columns,
    .field = calloc(rows, sizeof(char *))
  };
  
  for (int i = 0; i < rows; i++) {
    (new_grid.field)[i] = calloc(columns, sizeof(char));
    for (int j = 0; j < columns; j++) {
      (new_grid.field)[i][j] = '.';
    }
  }
  
  return new_grid;
}

static void play_game() {
  grid board = initialize_grid(3, 3);
  (void) board;
}

int main(int argc, char *argv[]) {
  char option[64];

  while(true) {
    printf("Do you want to [ play | quit ] ? ");
    scanf("%s", option);

    if(!strcmp(option, "play")) {
      printf("Let's play some tic-tac-toe!\n");
      play_game();
    }
    else if(!strcmp(option, "quit")) {
      printf("We should do this again some time\n");
      break;
    }
    else {
      printf("Invalid option, try again!\n");
    }
    
    printf("Press Any Key to Continue\n");
    while(getchar()!='\n');
    getchar();
  }
}