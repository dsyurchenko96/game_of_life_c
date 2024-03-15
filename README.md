# Game of Life

John Conway's Game of Life is a 0-player game implemented in C using the Ncurses library with terminal-based graphics. The user may choose one of the several initial states available, start the game and watch the cells live, die and get reborn.

## How to Play

- Increase Speed: '+' Key
- Decrease Speed: '-' Key
- Quit Game: 'q' Key

## Building and Running

To build and play the game, make sure you have `gcc` and the `ncurses` library installed. Use the following command in the terminal:

``` bash
make start
```

## Additional Commands

- `make clean`: Removes the compiled files and the executable.
- `make rebuild`: Cleans and rebuilds the project.
- `make cpp`: Runs static code analysis using cppcheck.