#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"
#include "list.h"
#include "pilha.h"
#include "fila.h"

int main() {
  // Lendo dimensões do labirinto.
  int x, y;
  scanf("%d %d", &y, &x);

  // Lendo a flag que diz o tipo de retorno do programa.
  char flag;
  scanf(" %c", &flag);

  // Var's. Contagem tempo
  double tempo = 0.0;
  clock_t begin = clock();         // Inicializa Contagem do tempo.
  Maze *maze = allocateMaze(y, x); // Alocando labirinto.

  // Var's. Labirinto e metodo de resolucao
  Position *mouse = allocatePosition(); // Aloca Rato
  readMaze(maze, mouse); // Lê os caracteres que formam o labirinto.

  /* Escolha o modo de resolver o labirinto */
  switch(flag){
    /* Recursao */
    case 'r':
      if(!resolveRecursive(maze, mouse, x, y)){ 
        resolveDFS(maze, mouse);
      }
    break;

  /* Busca em Profundidade */
    case 'p':
      resolveDFS(maze, mouse);
    break;

  /* Busca em Largura */
    case 'f':
      resolveBFS(maze, mouse);
    break;

  }
  printMaze(maze);
  
  // Libera os espaços alocados.
  freePosition(mouse);

  freeMaze(maze);

  clock_t end = clock();
  tempo += (double)(end - begin) / CLOCKS_PER_SEC; //Variável para armazenar tempo gasto.

  return 0;
}
