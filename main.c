#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "maze.h"

int main() {
  int x, y;
  double tempo = 0.0;
  // Lendo dimensões do labirinto.
  scanf("%d %d", &y, &x);

  char flag;
  // Lendo a flag que diz o tipo de retorno do programa.
  scanf(" %c", &flag);

  clock_t begin = clock();         // Inicializa Contagem do tempo.
  Maze *maze = allocateMaze(y, x); // Alocando labirinto.

  Position *mouse = allocatePosition(); // Aloca Rato

  readMaze(maze, mouse); // Lê os caracteres que formam o labirinto.

  Route *route = allocateRoute(y * x); // Aloca o array de rotas.

  // Verifica se existe um menor caminho.
  if (find(mouse, maze, route, 0)) {
    if (flag == 'p')
      printMaze(maze, route);
    else
      printRoute(route);
  } else
    printf("EPIC FAIL!");

  // Libera os espaços alocados.
  freePosition(mouse);

  freeRoute(route);

  freeMaze(maze);

  clock_t end = clock();
  tempo += (double)(end - begin) / CLOCKS_PER_SEC; //Variável para armazenar tempo gasto.


  return 0;
}
