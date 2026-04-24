#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ROWS 10
#define COLS 30
#define FPS 10

typedef struct {
  int x, y;
} Vector2;

typedef struct {
  Vector2 pos;
  int dx, dy;
} Ball;

typedef struct {
  Vector2 pos;
  int w;
  int dx;
} Paddle;

typedef struct {
  char cells[ROWS * COLS];
  Ball ball;
  Paddle paddle;
} Game;

void show(Game *game) {
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLS; x++) {
      printf("%c", game->cells[y * COLS + x]);
    }
    printf("\n");
  }
}

void assign_letters(Game *game) {
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLS; x++) {
      if (y == game->ball.pos.y && x == game->ball.pos.x) {
        game->cells[y * COLS + x] = 'O';
      } else if (y == game->paddle.pos.y && x >= game->paddle.pos.x &&
                 x < game->paddle.pos.x + game->paddle.w) {
        game->cells[y * COLS + x] = '=';
      } else {
        game->cells[y * COLS + x] = ' ';
      }
    }
  }
}

void reset_ball_pos(Game *game) {
  game->ball.dx = (rand() % 2) * 2 - 1;
  game->ball.dy = (rand() % 2) * 2 - 1;
  game->ball.pos.x = rand() % COLS;
  game->ball.pos.y = rand() % ROWS;
}

void update(Game *game) {
  if (game->ball.pos.x <= 0 || game->ball.pos.x >= COLS - 1) {
    game->ball.dx = -game->ball.dx;
  }

  if (game->ball.pos.y <= 0) {
    game->ball.dy = -game->ball.dy;
  }

  if (game->ball.pos.y > game->paddle.pos.y) {
    if (game->ball.pos.x >= game->paddle.pos.x &&
        game->ball.pos.x < game->paddle.pos.x + game->paddle.w) {
      game->ball.dy = -game->ball.dy;
    } else {
      // TODO: decrease ball life count
      reset_ball_pos(game);
    }
  }

  assign_letters(game);

  game->ball.pos.x += game->ball.dx;
  game->ball.pos.y += game->ball.dy;
  game->paddle.pos.x += game->paddle.dx;
}

void init_game(Game *game) {
  reset_ball_pos(game);

  game->paddle.dx = 0;
  game->paddle.w = 4;
  game->paddle.pos.x = COLS / 2 - game->paddle.w;
  game->paddle.pos.y = ROWS - 1;

  assign_letters(game);
}

int main() {
  srand(time(NULL));

  Game game = {0};
  init_game(&game);

  printf("\033[2J");

  while (1) {
    printf("\033[H");
    show(&game);
    update(&game);
    usleep((1000 * 1000) / FPS);
  }

  return 0;
}
