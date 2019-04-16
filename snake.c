#include "snake.h"

int kbhit() {//Implementação da função kbhit do conio.h, checa se algo foi apertado no teclado
  struct timeval tv;
  fd_set read_fd;

  tv.tv_sec=0;
  tv.tv_usec=0;
  FD_ZERO(&read_fd);
  FD_SET(0,&read_fd);

  if(select(1, &read_fd, NULL, NULL, &tv) == -1)
    return 0;

  if(FD_ISSET(0,&read_fd))
    return 1;

  return 0;
}

Coor achaCabeca(Queue* snake, Coor pos){
  for(Queue *aux=snake; aux!=NULL; aux=aux->next){//tivemos que fazer esse for para ele procurar a cabeça da cobra, já que o inicio da fila era o rabo
    if(aux->next==NULL){
      pos.x=aux->x;
      pos.y=aux->y;
    }
  }
  return pos;
}

int bateu(Queue *snake) {//função que vai checar se a cobra bateu em alguma coisa
  Coor pos;

  pos=achaCabeca(snake, pos);

  if (pos.x == -1 || pos.x > COLS) {//caso tenha batido nas paredes
    return 1;
  }

  else if (pos.y == -1 || pos.y > LINES) {
    return 1;
  }

  return 0;
}

Queue* moveSnake(Queue *snake, Coor dir, int velocidade, int pontos) {
  Coor pos;
  pos=achaCabeca(snake, pos);
  pos.x = pos.x+dir.x;
  pos.y = pos.y+dir.y;

  snake=dequeue(snake);    
  snake=enqueue(snake, pos.x, pos.y);

  for(Queue *aux=snake; aux!=NULL; aux=aux->next){//Printa a cobrinha
  	  mvprintw(aux->y, aux->x, "S");
  }
  if (dir.y == 0)  // quando o Y é igual a 0 ele está indo para cima e como a largura é maior que a altura fica muito mais rapido, por isso diminuimos a velocidade
    usleep(700000/velocidade);
  
  else // se estiver indo para os lados velocidade mais rapida 
    usleep(1000000/velocidade);

  return snake; 
}

void colocaMaca(Coor *maca, int *comeuM) {//tivemos que passar por referencia pois como sempre fica atualizando no while da main ela ficava colocando maças aleatorias direto
    if(*comeuM){ //atualiza as posições da maça caso ela tenha sido comida
      maca->x = (rand() % COLS);
      maca->y = (rand() % LINES);
      *comeuM=0;//retornamos o comeu para 0 
    }
    mvprintw(maca->y, maca->x,"M");//printa a posição da maçã
}

void comeuMaca(Queue *snake, Coor maca, int *comeuM, int *pontos, Coor dir) {

  Coor pos;
  pos=achaCabeca(snake, pos);
  if (pos.x == maca.x && pos.y == maca.y) {//se o x tiver na posição da maça 
    *comeuM = 1; // vai atualizar o valor de comeu, assim quando passar dnv no while, vai passar na função coloca maça e colocar outra maça já que a atual foi comida
   
    int fimX = pos.x+dir.x;
    int fimY = pos.y+dir.y;
 

    snake = enqueue(snake, fimX,fimY);
    
    *pontos+=1;//adiciona 1 na pontuação do jogador
  }
}

void colocaBonus(Coor *bonus, int *comeuB, int *pontos){//tivemos que passar por referencia pois como sempre fica atualizando no while da main ela ficava colocando maças aleatorias direto
    int restoPontos = *pontos%3;

    if(*comeuB == 1){ //atualiza as posições da maça caso ela tenha sido comidaw
      bonus->x = (rand() % COLS);
      bonus->y = (rand() % LINES);
      *comeuB=0;//retornamos o comeu para 0 
    }
    
    if(restoPontos == 0 && *pontos>=3)//requsitos para printar um bonus 
      mvprintw(bonus->y, bonus->x,"B");//printa a posição da do bonus

}

Queue* comeuBonus(Queue *snake, Coor bonus, int *comeuB, int *pontos, Coor dir) {
  Coor pos;

  pos=achaCabeca(snake, pos);

  if (pos.x == bonus.x && pos.y == bonus.y) {//se o x e o y tiver na posição da bonus 
    *comeuB = 1; // vai atualizar o valor de comeu, assim quando passar dnv no while, vai passar na função coloca maça e colocar outra maça já que a atual foi comida
   
    snake = dequeue(snake);//tira da fila da snake
    *pontos+=4;//adiciona 4 na pontuação do jogador
  }
  return snake;
}


void iniciaJogo(FILE *rankingR){//função que da inicio ao jogo
  int tamanho = contaLinhas(rankingR);

  TabelaPontos *pts;
  pts = (TabelaPontos *)malloc((tamanho+1)*sizeof(TabelaPontos));
  passaParaStruct(rankingR, tamanho, pts);//passamos para a struct oque estava contido no txt 

  Queue *snake = create_queue();
  Coor maca, bonus, dir;//variaveis que utilizam de coordenadas x e y
  dir.x = 0;   //vai iniciar com a snake indo para baixo
  dir.y = 1;
  int teclaAtual,
  velocidade = 11, //velocidade da cobra
  comeuM = 1, //se comeu maça
  comeuB=1;   //se comeu a bonus

  snake = enqueue(snake, 0, 0);//inicia uma cobra com tamanho 3 nas determinadas posições
  snake = enqueue(snake, 0, 1);
  snake = enqueue(snake, 0, 2);

  int pontos = 0;  //pontuação inicial do jogador

  initscr();
  curs_set(false);//cursor fica invisivel
  keypad(stdscr, TRUE); 
  noecho();//não aparece o que esta sendo digitado

  while (!bateu(snake)) {//enquanto a cobra não colidir com algo
    clear();
    colocaMaca(&maca, &comeuM);
    colocaBonus(&bonus, &comeuB, &pontos);
    snake = moveSnake(snake, dir, velocidade, pontos);
    comeuMaca(snake, maca, &comeuM, &pontos, dir);
    snake = comeuBonus(snake, bonus, &comeuB, &pontos, dir);

    refresh();

    //serve para mudar a posição da cobra
    if (kbhit()) {//essa função retorna se tem algum dado pressionado no buffer do teclado

      teclaAtual = getch();

      if (teclaAtual == KEY_UP && dir.y != 1 && dir.x != 0) {//Se apertar para cima, a direção de y vira -1 (vai para cima), também tem que ser diferentes dessas direções para não mudar de cima para baixo por exemplo
        dir.y = -1;
        dir.x = 0;
      }
      if (teclaAtual == KEY_DOWN && dir.y != -1 && dir.x != 0) {//Se apertar para baixo, a direção de y vira 1 (vai para baixo)
        dir.y = 1;
        dir.x = 0;
      }
      if (teclaAtual == KEY_LEFT && dir.y != 0 && dir.x != 1) {//Se apertar para a esquerda, a direção de x vira -1 (vai para direita)
        dir.y = 0;
        dir.x = -1;
      }
      if (teclaAtual == KEY_RIGHT && dir.y != 0 && dir.x != -1) {//Se apertar direita, a direção de x vira  1 (vai para cima)
        dir.y = 0;
        dir.x = 1;
      }
    }
  }
  erase();//limpamos a tela
  echo();//voltamos a mostrar oque é digitado
  curs_set(true);//habilitamos o cursos
  char nome[NOMEMAX];//definimos o tamanho de nome max como padrão


  mvprintw(LINES/2,COLS/3,"Parabens, sua pontuacao foi: %d", pontos);
  mvprintw(LINES/1.5,COLS/3,"Digite seu nome aqui:");
  scanw("%s", &nome);

  strcpy(pts[tamanho].nome, nome);
  pts[tamanho].pontos = pontos;

  fprintf(rankingR, "%s\t%d\n", pts[tamanho].nome, pts[tamanho].pontos);//inserimos no arquivo o dado do jogador atual

  endwin();
}

