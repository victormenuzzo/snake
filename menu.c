#include "menu.h"

void menu(FILE *rankingR){
  initscr(); //inicia as atividas na janela
  refresh();
  printw("\n");
  printw("############\t###       ##\t############\t##      ####\t############\n");
  printw("############\t####      ##\t############\t##     #### \t############   \n");
  printw("##          \t## ##     ##\t##        ##\t##   ####   \t##\n");
  printw("############\t##  ##    ##\t##        ##\t#####       \t##\n");
  printw("############\t##   ##   ##\t############\t#####       \t############\n");
  printw("          ##\t##    ##  ##\t############\t#####       \t############\n");
  printw("          ##\t##     ## ##\t##        ##\t##  #####   \t##\n");  
  printw("############\t##      ####\t##        ##\t##    ##### \t############\n");
  printw("############\t##        ##\t##        ##\t###     ####\t############\n");
  printw("\n1- JOGAR\n");
  printw("2- RECORDES\n");
  char ch = getch();//tem que ver se esse  é o metodo mais otimizado de pegar um dado e comparar
  
  if(ch==49){
    iniciaJogo(rankingR);//caso aperte 1 inicia o jogo
  }
  else if(ch==50){
    ordenaRanking(rankingR);//caso aperte 2 vai para o menu de ordenar ranking
  }

  endwin(); //encerra a atividade da janela
}