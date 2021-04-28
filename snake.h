#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "deck.h"

int kbhit(void);
void initialize_field (char field[SIZE][SIZE]);
void print_field (char field[SIZE][SIZE]);
int finish (Deck *d);
Point spawnFruta(Deck* d, char field[SIZE][SIZE]);
Deck* cresceSnakeFront(Deck* d, char field[SIZE][SIZE], char press, Point p);
Deck* cresceSnakeRear(Deck* d, char field[SIZE][SIZE], char press, Point p);
