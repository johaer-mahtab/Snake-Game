#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

#define N 11
#define MAX_SNAKE_LEN N * N

char grid[N][N];
int cell_value_tracker[N * N];

int size_of_the_snake = 1;
int snake[MAX_SNAKE_LEN];

typedef struct coordinate_system {
  int x, y;
} point;

point make(int a, int b) {
    return (point){ .x = a, .y = b };
}

int ptoc(point a) {
  return a.x * N + a.y;
}

point ctop(int x) { // point to cell number convertor
  point now;
  now.x = x / N;
  now.y = x % N;
  return now;
}

void swap(char *x, char *y) {
  char temp = *x;
  *x = *y;
  *y = temp;
}

point fruit_cell_generator() {
  int index = rand() % (N * N);
  point now;

  while (1) {
    now = ctop(index);

    if (grid[now.x][now.y] != 'x') {
      break;
    }
    index = rand() % (N * N);
  }
  return now;
}

void reset_grid() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      grid[i][j] = ' ';
    }
  }
}

void put_the_snake_on_the_grid(point food) {
  reset_grid();
  for (int i = 0; i < size_of_the_snake; i++) {
    point curr = ctop(snake[i]);
    grid[curr.x][curr.y] = 'x';
  }
  grid[food.x][food.y] = 'o';
  return;
}

int key_value(char cc) {
  cc = tolower(cc);
  return (cc == 'l' ? 1 : (cc == 'j' ? -1 : (cc == 'k' ? N : -N)));
}

void print_grid() {
  for (int i = 0; i < N + 2; i++) {
    if (i > 0) {
      printf(" ");
    }
    printf("#");
  }
  printf("\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i >= 0) {
        if (j == 0) {
          printf("# ");
        } else {
          printf(" ");
        }
      }
     printf("%c", grid[i][j]);
    }
    if (i >= 0) printf(" #");
    printf("\n");
  }
  for (int i = 0; i < N + 2; i++) {
    if (i > 0) {
      printf(" ");
    }
    printf("#");
  }
  printf("\n");
  return;
}

int main() {

  printf("\e[?25l");

  srand(time(0));

  for (int i = 0; i < N * N; i++) {
    cell_value_tracker[i] = 0;
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      grid[i][j] = ' ';
    }
  }

  grid[N / 2][N / 2] = 'x';


  snake[0] = ptoc(make(N / 2, N / 2));
  point food = fruit_cell_generator();

  system("cls");
  put_the_snake_on_the_grid(food);
  print_grid();

  int score = 0;

  int prev_key_value = 1;
  
  while (1) {
    char now = getch();

    if (now == 'b') {
      break;
    }

    int add = (now == 's' ? prev_key_value : key_value(now));

    int prv = snake[size_of_the_snake - 1];
    cell_value_tracker[snake[0]] = add;
    snake[0] += add;

    int temp = snake[size_of_the_snake - 1];

    for (int i = 1; i < size_of_the_snake; i++) {
      snake[i] += cell_value_tracker[snake[i]];
    }

    if (ptoc(food) == snake[0]) {
      food = fruit_cell_generator();
      snake[size_of_the_snake] = prv;
      size_of_the_snake++;
      ++score;
    }

    system("cls");
    put_the_snake_on_the_grid(food);
    print_grid();
    printf("Score: %d\n", score);
  }


  return 0;
}
