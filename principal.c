#include "menu.h"

int main (int argc, char *argv[])
{
	if (argc < 2)//para ver se foi passado o arquivo de rank
	{
    printf("Uso: %s arquivo_de_ranking\n", argv[0]);
    exit(1);
 	}

 	FILE *rankingR;

	rankingR = fopen(argv[1], "a+"); //abrimos o arquivo com a+ para escrever no fim do arquivo

 	srand(time(NULL));
 	menu(rankingR);//chamamos o menu
	return 0;
}