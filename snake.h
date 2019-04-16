#include "ordena.h"

typedef struct coordenadas{//struct de coordenadas, foi usada para a saber a direção da cobra, a posição da maça e do bonus
	int x;
	int y;
}Coor;

int kbhit();
int bateu(Queue *snake);
Queue* moveSnake(Queue *snake, Coor dir, int velocidade, int pontos);
void colocaMaca(Coor *maca, int *comeu);
void comeuMaca(Queue *snake, Coor maca, int *comeu, int *pontos, Coor dir);
void colocaBonus(Coor *bonus, int *comeuB, int *pontos);
Queue* comeuBonus(Queue *snake, Coor bonus, int *comeuB, int *pontos, Coor dir);
Coor achaCabeca(Queue* snake, Coor pos);
