#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 25
#define COLS 80
#define INTERVAL 50
#define BUFF 1024

int choose_file(void);
int **dyn_mem(int rows, int cols, int inputFlag);
void free_all(int **a, int rows);
int input(int **a, const int *rows, const int *cols);
void output(int **a, int rows, int cols);
int count_neighbours(int **matrix, int row, int col);
int get_state(int **matrix, int row, int col);
void swap_matrices(int **matrixOld, int **matrixNew);
char switcher(int **a, int row, int col);
void looper(int **matrixOld, int **matrixNew, int speed);
void controls(char key, int *speed);
void cursed(int **matrixOld, int **matrixNew);