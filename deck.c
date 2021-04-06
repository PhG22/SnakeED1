#include "deck.h"

Deck* createDeck () {
  return NULL;
}

/*Função que retorna a coordenada armazenada na cabeça da lista encadeada (assuma que o endereço do Deck *d aponta para a cabeça)!*/
Point getFront (Deck *d) {
	return d->p;
}

/*Função que retorna a coordenada armazenada na cauda da lista encadeada (assuma que o endereço do Deck *d aponta para a cabeça)!*/
Point getRear (Deck *d) {
	Deck *aux = (Deck *)malloc(sizeof(Deck));
	for(aux = d; aux->next != NULL; aux = aux->next){}
	return aux->p;
}

/*Função para inserir na cabeça da lista encadeada (assuma que o endereço do Deck *d aponta para a cabeça)!*/
Deck* insertFront (Deck *d, Point p, char field[][SIZE]) { 	
	Deck *new = (Deck *)malloc(sizeof(Deck));
	new->p = p;
	new->prev = NULL;
	new->next = d;
	if(d!=NULL){
		d->prev = new;
	}
	field[p.x][p.y] = '*'; /*Ponto inserido faz parte do corpo da Snake!*/
	return new;
}

/*Função para inserir na cauda da lista encadeada (assuma que o endereço do Deck *d aponta para a cabeça)!*/
Deck* insertRear (Deck *d, Point p, char field[][SIZE]) {	
	Deck *new = (Deck *)malloc(sizeof(Deck));
	Deck *aux = (Deck *)malloc(sizeof(Deck));
	aux = d;
	while(aux->next != NULL){
		aux = aux->next;
	}
	new->p = p;
	new->next = NULL;
	new->prev = aux;
	field[p.x][p.y] = '*';  /*Ponto inserido faz parte do corpo da Snake!*/
	aux->next = new;
	return d;
}

/*Função para remover a cabeça da lista encadeada (assuma que o endereço do Deck *d aponta para a cabeça)!*/
Deck* deleteFront (Deck *d, char field[][SIZE]) {
   	Deck *aux = d;
	int x, y;
	d = d->next;
      	d->prev = NULL;
	x = aux->p.x;
	y = aux->p.y;	
   	field[x][y] = ' '; /*Ponto eliminado agora é marcado como vazio!*/
   	free(aux);
	return d;
}

/*Função para remover a cauda da lista encadeada (assuma que o endereço do Deck *d aponta para a cabeça)!*/
Deck* deleteRear (Deck *d, char field[][SIZE]) {
   	Deck *aux1;
	while(aux1->next!=NULL){
		aux1 = aux1->next;
	}
	Deck *aux2 = aux1->prev;
	aux2->next = NULL;
	int x, y;
	x = aux1->p.x;
	y = aux1->p.y;
	field[x][y] = ' '; /*Ponto eliminado agora é marcado como vazio!*/
   	free(aux1);
	return d;
}
