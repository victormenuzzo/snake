#include "queue.h"

/*Função para criar uma lista encadeada que tem comportamento de um TAD Fila.*/
Queue* create_queue () {
   return NULL;
}

/*Função para desalocar uma lista encadeada.*/
void free_queue (Queue *q) {
   while (q != NULL) {
      Queue *aux = q->next; /*guarda ref. p/ prox.*/
      free (q); /*libera a memória.*/
      q = aux; /*faz lista apontar p/ o prox. elem.*/
   }
}

/*Função para enfileirar um elemento. A posição do novo elemento é o final da lista encadeada. */
Queue* enqueue (Queue *q, int x, int y) {
   /*Criando novo elemento: */
   Queue *n = (Queue *)malloc(sizeof(Queue));
   n->x = x; /*inserindo o dado.*/
   n->y = y;
   n->next = NULL; /*último elemento da lista não tem próximo.*/
   /*Localizando a cauda da lista encadeda: */
   Queue *aux, *end = NULL;
   for (aux = q; aux != NULL; aux = aux->next) {
      end = aux; 
   }
   /*Se a lista não exister vazia a cabeça da lista se mantém.*/
   if (end != NULL) {
      end->next = n; /*conectando o novo elemento na cauda da lista.*/
      return q; /*retorne a cabeça da lista encadeada.*/
   }
   else {
      return n; /*A lista estava vazia, logo n é a cabeça da lista.*/
   }
}

/*Função para desenfileirar um elemento inteiro do início da lista encadeada. */
Queue* dequeue (Queue *q) {
   if (!Empty(q)) {
      Queue *aux = q->next; /*Guarda endereço do próximo elemento.*/
      free(q); /*Removendo nodo da lista.*/
      return aux; /*Nova cabeça da lista!*/
   }
   else {
      return NULL; /*Remoção em uma lista vazia.*/
   }
}

/*Função para mostrar sem desenfileirar o elemento do início da lista encadeada.*/
int frontX (Queue *q) {
   if (!Empty(q)) {
      return q->x;      
   }
   //return NOT_FOUND; 
}

int frontY (Queue *q) {
   if (!Empty(q)) {
      return q->y;      
   }
   //return NOT_FOUND; 
}

/*Função para testar se existem elementos na lista encadeada.*/
int Empty (Queue *q) {
   return (q == NULL);
}

void imprime(Queue *q, int x, int y){
	Queue *aux;
   int cont =0;
	for(aux=q; aux!=NULL; aux=aux->next){
		printw("\n%d, %d", aux->x, aux->y);
      	refresh();
	}	
}

