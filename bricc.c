#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ROWS 10
#define COLS 30
#define FPS 60

void show(int x0, int y0) {
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLS; x++) {
      if (y == y0 && x == x0) {
        printf("O");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
}

int main() {
  srand(time(NULL));

  int x = rand() % COLS;
  int y = rand() % ROWS;

  int dx = (rand() % 2) * 2 - 1;
  int dy = (rand() % 2) * 2 - 1;

  printf("\033[2J");

  while (1) {
    printf("\033[H");
    show(x, y);
    x += dx;
    y += dy;

    if (x <= 0 || x >= COLS - 1) {
      dx = -dx;
    }

    if (y <= 0 || y >= ROWS - 1) {
      dy = -dy;
    }

    usleep((1000 * 1000) / FPS);
  }

  return 0;
}
