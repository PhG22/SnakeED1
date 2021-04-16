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
	
	Deck* aux = d;
	
	while(aux->next != NULL)
		aux = aux->next;
	
	return aux->p;
}

/*Função para inserir na cabeça da lista encadeada (assuma que o endereço do Deck *d aponta para a cabeça)!*/
Deck* insertFront (Deck *d, Point p, char field[][SIZE]) { 
	
	Deck* novo = (Deck*) malloc(sizeof(Deck));
	if(d == NULL){
		novo->p = p;
		novo->prev = NULL;
		novo->next = d;
	}
	
	else{
		novo->p = p;
		novo->prev = NULL;
		novo->next = d;
		d->prev = novo;
	}
	
	field[p.x][p.y] = '*'; /*Ponto inserido faz parte do corpo da Snake!*/
	
	return novo;
}

/*Função para inserir na cauda da lista encadeada (assuma que o endereço do Deck *d aponta para a cabeça)!*/
Deck* insertRear (Deck *d, Point p, char field[][SIZE]) {
	
	Deck* novo = (Deck *)malloc(sizeof(Deck));
	
	Deck* aux = d;

	while(aux->next != NULL){
		aux = aux->next;
	}
	
	novo->p = p;
	novo->next = NULL;
	novo->prev = aux;
	
	field[p.x][p.y] = '*';  /*Ponto inserido faz parte do corpo da Snake!*/
	
	aux->next = novo;
	
	return d;
}

/*Função para remover a cabeça da lista encadeada (assuma que o endereço do Deck *d aponta para a cabeça)!*/
Deck* deleteFront (Deck *d, char field[][SIZE]) {
	
   	Deck* aux = d;

	d = d->next;
      	d->prev = NULL;

	if(field [aux->p.x][aux->p.y] != '@')
   		field[aux->p.x][aux->p.y] = ' '; /*Ponto eliminado agora é marcado como vazio!*/
	
   	free(aux);
	
	return d;
}

/*Função para remover a cauda da lista encadeada (assuma que o endereço do Deck *d aponta para a cabeça)!*/
Deck* deleteRear (Deck *d, char field[][SIZE]) {
	
   	Deck* aux1 = d;
	
	while(aux1->next != NULL)
		aux1 = aux1->next;
	
	Deck* aux2 = aux1->prev;
	aux2->next = NULL;
	if(field [aux1->p.x][aux1->p.y] != '@')
		field[aux1->p.x][aux1->p.y] = ' '; /*Ponto eliminado agora é marcado como vazio!*/
	
   	free(aux1);
	
	return d;
}
