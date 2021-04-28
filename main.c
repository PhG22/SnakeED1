#include "snake.h"

int main () {

   char field[SIZE][SIZE];
   initialize_field (field); 
   int center = SIZE/2;
   int snake_size = 5;
   Deck *d = createDeck ();
   long long int score = 0;
   int dificuldade = 300000;
  
   system("clear");
   
   printf("\e[1;32m    _______  __    _  _______  ___   _  _______ \e[0m\n");
   printf("\e[1;32m   |       ||  |  | ||   _   ||   | | ||       |\e[0m\n");
   printf("\e[1;32m   |  _____||   |_| ||  |_|  ||   |_| ||    ___|\e[0m\n");
   printf("\e[1;32m   | |_____ |       ||       ||      _||   |___ \e[0m\n");
   printf("\e[1;32m   |_____  ||  _    ||       ||     |_ |    ___|\e[0m\n");
   printf("\e[1;32m    _____| || | |   ||   _   ||    _  ||   |___ \e[0m\n");
   printf("\e[1;32m   |_______||_|  |__||__| |__||___| |_||_______|\e[0m\n");
   
   printf("\n\n\e[1;37mControles: W = Cima, A = Esquerda, S = Baixo, D = Direita\e[0m\n\n         \e[4;33mPressione enter para iniciar!!!\e[0m\n");
   getchar();

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
   printf("\e[1;31m _____ _____ _____    ____  _____       __ _____ _____ _____ \e[0m\n");
   printf("\e[1;31m|   __|     |     |  |    ||   __|   __|  |     |   __|     |\e[0m\n");
   printf("\e[1;31m|   __|-   -| | | |  |  |  |   __|  |  |  |  |  |  |  |  |  |\e[0m\n");
   printf("\e[1;31m|__|  |_____|_|_|_|  |____/|_____|  |_____|_____|_____|_____|\e[0m\n");
   printf("\e[1;31m                                                             \e[0m\n");
   printf ("\n                   \e[1;37mPontuacao Final:\e[0m \e[1;33m %lld \e[0m\n\n", score);
   return 0;
}
