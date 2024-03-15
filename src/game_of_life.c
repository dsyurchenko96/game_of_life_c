#include "game_of_life.h"

int main(void) {
    int exitStatus = choose_file();
    int **matrixOld = NULL;
    if (!exitStatus && (matrixOld = dyn_mem(ROWS, COLS, 1)) != NULL) {
        int **matrixNew = dyn_mem(ROWS, COLS, 0);
        if (matrixNew) {
            if (freopen("/dev/tty", "r", stdin) != NULL) {
                cursed(matrixOld, matrixNew);
            }
            free_all(matrixNew, ROWS);
        } else {
            exitStatus = 1;
        }
        free_all(matrixOld, ROWS);
    } else {
        exitStatus = 1;
    }
    return exitStatus;
}

int choose_file(void) {
    int exit_status = 0;
    int num_file = 0;
    char filename[BUFF];
    printf("Choose your initial state (currently available from 1 to 8)\n");
    while (!num_file) {
        scanf("%d", &num_file);
    }
    sprintf(filename, "../init_states/%d.txt", num_file);
    if (freopen(filename, "r", stdin) == NULL) {
        exit_status = 1;
    }
    return exit_status;
}



void cursed(int **matrixOld, int **matrixNew) {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    looper(matrixOld, matrixNew, INTERVAL * 5);
    endwin();
}

void looper(int **matrixOld, int **matrixNew, int speed) {
    int newState;
    int curSpeed = speed;
    int key;
    while ((key = getch()) != 'q') {
        controls(key, &curSpeed);
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                newState = get_state(matrixOld, row, col);
                matrixNew[row][col] = newState;
            }
        }
        output(matrixNew, ROWS, COLS);
        printw(
            "\n\nCurrent delay between generations is %d ms.\nPress '+' to increase it or '-' to decrease it by "
            "%d ms, 'q' to quit.\n",
            curSpeed, INTERVAL);
        refresh();
        napms(curSpeed);
        clear();
        swap_matrices(matrixOld, matrixNew);
    }
}

void swap_matrices(int **matrixOld, int **matrixNew) {
    int temp = 0;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            temp = matrixOld[row][col];
            matrixOld[row][col] = matrixNew[row][col];
            matrixNew[row][col] = temp;
        }
    }
}

int count_neighbours(int **matrix, int row, int col) {
    int alive = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (matrix[(ROWS + i) % ROWS][(COLS + j) % COLS]) {
                alive++;
            }
        }
    }
    if (matrix[row][col] && alive) {
        alive -= 1;
    }
    return alive;
}

int get_state(int **matrix, int row, int col) {
    int curState = matrix[row][col], newState;
    int neighbours = count_neighbours(matrix, row, col);
    if (curState == 0 && neighbours == 3) {
        newState = 1;
    } else if (curState == 1 && (neighbours < 2 || neighbours > 3)) {
        newState = 0;
    } else {
        newState = curState;
    }
    return newState;
}

int **dyn_mem(int rows, int cols, int inputFlag) {
    int **ptrArray = calloc(rows, sizeof(int *));
    if (ptrArray) {
        for (int i = 0; i < rows && ptrArray; i++) {
            ptrArray[i] = calloc(cols, sizeof(int));
            if (ptrArray[i] == NULL) {
                free_all(ptrArray, i);
            }
        }
    } else {
        ptrArray = NULL;
    }
    if (inputFlag && input(ptrArray, &rows, &cols)) {
        ptrArray = NULL;
    }
    return ptrArray;
}

void free_all(int **a, int rows) {
    for (int i = 0; i < rows; i++) {
        free(a[i]);
    }
    free(a);
}

int input(int **a, const int *rows, const int *cols) {
    int buffer;
    for (int row = 0; row < *rows; row++) {
        for (int col = 0; col < *cols; col++) {
            if (!scanf("%d", &buffer)) {
                return 1;
            }
            a[row][col] = buffer;
        }
    }
    return 0;
}

void output(int **a, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            printw("%c", switcher(a, row, col));
        }
        if (row != rows - 1) {
            printw("\n");
        }
    }
}

char switcher(int **a, int row, int col) {
    char symbol;
    switch (a[row][col]) {
        case 0:
            symbol = ' ';
            break;

        case 1:
            symbol = '#';
            break;

        default:
            symbol = '?';
            break;
    }
    return symbol;
}

void controls(char key, int *speed) {
    switch (key) {
        case '-':
            if (*speed - INTERVAL >= INTERVAL) {
                *speed -= INTERVAL;
            }
            break;

        case '+':
            if (*speed + INTERVAL < INTERVAL * 10) {
                *speed += INTERVAL;
            }
            break;

        default:
            break;
    }
}
