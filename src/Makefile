CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -lncurses

all: start

game_of_life:
	$(CC) $(FLAGS) game_of_life.c -o game_of_life

start: game_of_life
	./game_of_life

clean:
	rm -rf game_of_life

rebuild:
	make clean
	make all

statictest:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	make all
	make rebuild

beforecommit:
	make statictest
	make clean

test_leaks: game_of_life
ifeq ($(shell uname -s), Linux)
	valgrind --leak-check=yes ./game_of_life
else
	leaks --atExit -- ./game_of_life
endif