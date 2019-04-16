#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>//biblioteca que usamos para a função uspleep
#include <time.h>
#include <string.h>
#define NOMEMAX 40 


typedef struct _queue{
    struct _queue *next, *prev;
    int x;//adicionamos x e y para guardar as coordenadas
    int y;
}Queue;

/*Função para criar uma lista encadeada que tem comportamento de um TAD Fila.*/
Queue* create_queue ();

/*Função para desalocar uma lista encadeada.*/
void free_queue (Queue *q);

/*Função para enfileirar um elemento. A posição do novo elemento é o final da lista encadeada. */
Queue* enqueue (Queue *q, int x, int y);

/*Função para desenfileirar um elemento inteiro do início da lista encadeada. */
Queue* dequeue (Queue *q);

/*Função para mostrar sem desenfileirar o elemento do início da lista encadeada.*/
int frontX (Queue *q);
int frontY (Queue *q);


/*Função para testar se existem elementos na lista encadeada.*/
int Empty (Queue *q);

void imprime(Queue *q, int x, int y);


