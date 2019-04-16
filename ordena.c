#include "ordena.h"

void ordenaRanking(FILE *ranking)//menu para peguntar de que modo o usuário deseja ordenar
{
  int tam = contaLinhas(ranking), flag = 0;
  TabelaPontos *pts;
  pts = (TabelaPontos *)malloc((tam+1)*sizeof(TabelaPontos));//damos malloc para aumentar o tamanho em 1  
  passaParaStruct(ranking, tam, pts);
  initscr();
  erase();

  
  mvprintw(LINES/2, COLS/3, "Qual a ordem de preferencia?\n1-Por Nome\n2-Por Pontuação\n");

  while(!flag){
    char ch = getch();
    erase();
    if(ch==49){//caso aperte a tecla 1 ordenamos por nome
      printw("NOME\t\tPONTOS\n");
      ordenaNome(pts, 0, tam-1);
        for(int i=1; i<tam; i++)
              printw("%s\t\t%d\n", pts[i].nome, pts[i].pontos);
        flag = 1;
    }

    else if(ch == 50){//caso aperte a tecla 2 ordenamos por pontuação
        printw("NOME\t\tPONTOS\n");
        ordenaPont(pts, 0, tam-1);
            for(int i=0; i<tam-1; i++)
              printw("%s\t\t%d\n", pts[i].nome, pts[i].pontos);
          flag = 1;
    } 

    else 
      mvprintw(LINES/2, COLS/3, "Digite um numero valido\nQual a ordem de preferencia?\n1-Por Nome\n2-Por Pontuação\n");
  }

  getch();
  endwin();

}

int contaLinhas(FILE *arq)//essa função conta as linhas do arquivo
{
  int cont = 0;
  char ch;
  while( (ch=fgetc(arq))!= EOF )//enquanto nao for o fim do arquvio
      if(ch == '\n')
        cont++;//adicionamos 1 no contador
  
  rewind(arq);//rebobina o arquivo

  return cont;//retorna o numero de linhas
}

void ordenaPont(TabelaPontos *pts, int l, int r){
  if (l < r) {
      int q = ParticionePont(pts, l, r);
      ordenaPont(pts, l, q-1);
      ordenaPont(pts, q+1, r); 
   }
}

///quick sort de string para os nomes
void ordenaNome(TabelaPontos *pts, int l, int r){
  if (l < r) {
      int q = ParticioneNome(pts, l, r);
      ordenaNome(pts, l, q-1);
      ordenaNome(pts, q+1, r); 
   }
}

int ParticioneNome(TabelaPontos *pts, int l, int r) {
   char x[256];
   int i = l-1;
   int j;
   strcpy(x, pts[r].nome);
   for (j = l; j <= r - 1; j++) {
      if (strcmp(x, pts[j].nome)>=0) {
         i += 1;
         Swap(pts, i, j);
      }
   }
   Swap(pts, i+1, r);
   return i + 1;
}

//quick sort de int para a pontuação
int ParticionePont(TabelaPontos *pts, int l, int r) {
   int x = pts[r].pontos;
   int i = l-1;
   int j;
   for (j = l; j <= r - 1; j++) {
      if (pts[j].pontos >= x) {
         i += 1;
         Swap (pts, i, j);
      }
   }
   Swap(pts, i+1, r);
   return i + 1;
}

/*Troca dois elementos {i,j} de posição.*/
void Swap(TabelaPontos *pts, int i, int j) {
  TabelaPontos aux = pts[i];
  pts[i] = pts[j];
  pts[j] = aux;
}

//função para passar para uma struct os dados do arquivo
void passaParaStruct(FILE *ranking, int nroLinhas, TabelaPontos *v)
{
  char nome[10], pontos[10];
  fscanf(ranking,"%s\t\t%s\n", nome, pontos);//le a primeira linha do arquivo com a o cabeçalho
  

  for(int i=0; i<nroLinhas-1; i++)//lemos as linhas do arquivo
    fscanf(ranking,"%s\t%d\n", v[i].nome, &v[i].pontos);
}