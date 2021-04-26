#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "deck.h"

int kbhit(void) {
  struct termios oldt, newt;
  int ch;
  int oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if(ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}

void initialize_field (char field[SIZE][SIZE]) {
   int i, j;
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         field[i][j] = ' ';
      } 
   }
}

void print_field (char field[SIZE][SIZE]) {
   int i, j;
   int c = '#';
   printf("  ");
   for (i = 0; i < SIZE; i++) {
      printf("\e[1;33m %c\e[0m", c);
   }
   printf("\n");
   for (i = 0; i < SIZE; i++) {
      printf("\e[1;33m %c \e[0m",c);
      for (j = 0; j < SIZE; j++) {
      	if(field[i][j] == '@')
         printf("\e[1;31m%c \e[0m", field[i][j]);
        else if(field[i][j] == '*')
         printf("\e[1;32m%c \e[0m", field[i][j]); 
        else
         printf("%c ", field[i][j]);
      } 
      printf("\e[1;33m%c\n\e[0m", c);
   }
   printf("  ");
   for (i = 0; i < SIZE; i++) {
      printf("\e[1;33m %c\e[0m", c);
   }
   printf("\n");
}

int finish (Deck *d) {
   
   Point p1 = getRear (d);
   Point p2 = getFront (d);

   if (p1.x < 1 || p1.x > SIZE-2 || p1.y < 1 || p1.y > SIZE-1)
      return 1;
   
   else if (p2.x < 1 || p2.x > SIZE-2 || p2.y < 1 || p2.y > SIZE-1)
      return 1;

   for(Deck* i = d->next; i != NULL; i = i->next){
	if(p2.x == i->p.x && p2.y == i->p.y)
		return 1;
   }

   for(Deck* i = d; i->next != NULL; i = i->next){
   	if(p1.x == i->p.x && p1.y == i->p.y)
		return 1;
   		
   }
 
   return 0;
}

Point spawnFruta(Deck* d, char field[SIZE][SIZE]){
   int x, y, valido;
   do{
   	x = (rand()%22) + 2;
   	y = (rand()%22) + 2;
   	valido = 1;
   
   	for(Deck* i = d; i != NULL; i = i->next){
     		if(x == i->p.x && y == i->p.y){
			valido = 0;
			break;
		}
   	}
    } while(!valido);

   field[x][y] = '@';

   return (Point){x,y};
}

Deck* cresceSnakeFront(Deck* d, char field[SIZE][SIZE], char press, Point p){

	if (press ==  'w') { d = insertFront (d, (Point){p.x-1, p.y}, field); }
       	else if (press ==  's') { d = insertFront (d, (Point){p.x+1, p.y}, field); }
        else if (press ==  'a') { d = insertFront (d, (Point){p.x, p.y-1}, field); }
        else { d = insertFront (d, (Point){p.x, p.y+1}, field); }

	return d;
}

Deck* cresceSnakeRear(Deck* d, char field[SIZE][SIZE], char press, Point p){

        if (press ==  'w') { d = insertRear (d, (Point){p.x-1, p.y}, field); }
        else if (press ==  's') { d = insertRear (d, (Point){p.x+1, p.y}, field); }
        else if (press ==  'a') { d = insertRear (d, (Point){p.x, p.y-1}, field); }
        else { d = insertRear (d, (Point){p.x, p.y+1}, field); }

	return d;
}

int main () {

   char field[SIZE][SIZE];
   initialize_field (field); 
   int center = SIZE/2;
   int snake_size = 5;
   Deck *d = createDeck ();
   long long int score = 0;
   int dificuldade = 300000;

   /*Inserindo a Snake no centro do campo: */
   int i;
   for (i = center-snake_size/2; i <= center+snake_size/2; i++) {
      d = insertFront (d, (Point){center, i}, field);
   }

   char pressionou_prv = ' ';
   char pressionou_act = 'a';
   int reverse = 0; /*variável para inverter cabeça com cauda (e vice-versa)*/
   srand(time(NULL));
   Point fruta = spawnFruta(d,field);
   while (!finish(d)) {
     while((!kbhit()) && (!finish(d))) {
       if (reverse) {
           Point p = getFront (d);
	   d = cresceSnakeFront(d, field, pressionou_act, p);
	   d = deleteRear (d, field);
        }
        else {
           Point p = getRear (d);
	   d = cresceSnakeRear(d, field, pressionou_act, p);
	   d = deleteFront (d, field);
        }

       if(reverse){
           Point p = getFront(d);
           if(p.x == fruta.x && p.y == fruta.y){
	      d = cresceSnakeFront(d, field, pressionou_act, p);
	      fruta = spawnFruta(d,field);
	      snake_size++;
	      score += 100;
	      dificuldade -= 5000;
           }
        }
        else{
           Point p = getRear(d);
           if(p.x == fruta.x && p.y == fruta.y){
	      d = cresceSnakeRear(d, field, pressionou_act, p);
	      fruta = spawnFruta(d, field);
	      snake_size++;
	      score += 100;
	      dificuldade -= 5000;
           }
        }

        print_field (field);
	printf("\n \e[4;37mScore:\e[0m \e[1;32m%lld\e[0m   \e[4;37mTamanho:\e[0m \e[1;32m%d\e[0m\n",score, snake_size);
        usleep(dificuldade);
        system("clear");
     }
     if (!finish(d)) {
        /*Cada vez que uma tecla é pressionada o controle executa esse trecho: */
        pressionou_prv = pressionou_act;
        pressionou_act = getchar();
        if ((pressionou_act ==  's') && (pressionou_prv ==  'w')) { reverse = !reverse; }
        else if ((pressionou_act ==  'w') && (pressionou_prv ==  'w')) { reverse = !reverse; }
        else if ((pressionou_act ==  'a') && (pressionou_prv ==  'd')) { reverse = !reverse; }
        else if ((pressionou_act ==  'd') && (pressionou_prv ==  'a')) { reverse = !reverse; }

     }
   }
   printf ("      \e[4;31mFIM DE JOGO\e[0m      \n \e[1;37mPontuacao Final:\e[0m \e[1;33m %lld \e[0m\n", score);
   return 0;
}
