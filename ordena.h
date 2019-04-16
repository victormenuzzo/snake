#include "queue.h"

typedef struct _tabelaPontos{//struct usada para guardas as informações para a ordenação
	char nome[NOMEMAX];
	int pontos;
}TabelaPontos;

int contaLinhas(FILE *arq);
void passaParaStruct(FILE *ranking, int nroLinhas, TabelaPontos *v);
void Swap(TabelaPontos *pts, int i, int j);
int ParticionePont(TabelaPontos *pts, int l, int r);
void ordenaPont(TabelaPontos *pts, int l, int r);
void ordenaRanking(FILE *ranking);
int ParticioneNome(TabelaPontos *pts, int l, int r);
void ordenaNome(TabelaPontos *pts, int l, int r);