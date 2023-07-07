#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"

/* Só para deixar os pontos vermelhos */
#define RED "\033[31m"
#define RESET "\033[0m"

// TAD MAZE, define o labirinto.


// TAD Position, define uma coordenada.


/*
 * TAD Route, define uma estrutura de rota composta de
 * coordenadas [y, x], e a distância total da rota.
 */

/* -------- Lista Encadeada ----------- */

// **Lista Encadeada para recursao tambem?


// Aloca o TAD MAZE.
Maze *allocateMaze(int y, int x)
{
  // Aloca memória para o TAD MAZE.
  Maze *maze = (Maze *)malloc(sizeof(Maze));

  // Define o tamanho do labirinto.
  maze->y = y;
  maze->x = x;

  // Aloca memória para a matriz que representa o labirinto.
  maze->array = (char **)malloc(y * sizeof(char *));
  for (int i = 0; i < y; i++)
    maze->array[i] = (char *)malloc(x * sizeof(char));

  // Saída do labirinto.
  maze->finalPosY = y - 2;
  maze->finalPosX = x - 1;

  // Retorna o ponteiro para o labirinto alocado.
  return maze;
}

// Libera o espaço alocado para o labirinto.
void freeMaze(Maze *maze)
{
  // Libera a memória alocada para a matriz do labirinto.
  for (int i = 0; i < maze->y; i++)
    free(maze->array[i]);
  free(maze->array);

  // Libera a memória alocada para o TAD MAZE.
  free(maze);
}

// Aloca o TAD Route
Route *allocateRoute(int MAX_SIZE)
{
  Route *route = (Route *)malloc(sizeof(Route));
  route->positions = (Position *)malloc(sizeof(Position) * MAX_SIZE);
  route->distance = 0;
  route->minPositions = (Position *)malloc(sizeof(Position) * MAX_SIZE);
  route->minDistance = INT_MAX; // Inicialmente definido como um valor alto.
  route->size = 0;

  return route;
}

// Libera o espaço alocado para Route
void freeRoute(Route *route)
{
  free(route->positions);
  free(route->minPositions);
  free(route);
}

// Aloca o TAD Position
Position *allocatePosition()
{
  Position *position = (Position *)malloc(sizeof(Position));
  return position;
}

void freePosition(Position *position) { free(position); }

// Lê o labirinto do arquivo.
void readMaze(Maze *maze, Position *mouse)
{
  getchar(); // Descarta o caractere de quebra de linha inicial.

  for (int i = 0; i < maze->y; i++)
  {
    for (int j = 0; j < maze->x; j++)
    {
      scanf("%c", &(maze->array[i][j]));
      if (maze->array[i][j] == 'M')
      {
        mouse->y = i;
        mouse->x = j;
      }
    }
    getchar(); // Descarta o caractere de quebra de linha após cada linha.
  }
}

// Função para imprimir o labirinto.
void printMaze(Maze *maze, Route *positionsTraveled)
{
  printf("%d\n", positionsTraveled->size);

  for (int i = 0; i < maze->y; i++)
  {
    for (int j = 0; j < maze->x; j++)
    {
      if (maze->array[i][j] == '.')
      {
        printf(RED "%c" RESET, maze->array[i][j]);
      }
      else
        printf("%c", maze->array[i][j]);
    }
    printf("\n");
  }
}

// Função para imprimir as coordenadas da rota.
void printRoute(Route *route)
{

  printf("%d\n", route->size);
  for (int i = 0; i < route->size; i++)
  {
    printf("%d, %d\n", route->positions[i].y, route->positions[i].x);
  }
}

// Função verifica se a posição é válida.
int isValid(Maze *maze, Position *new_position)
{

  if (new_position->y < 0 || new_position->x < 0 ||
      new_position->y >= maze->y || new_position->x >= maze->x)
  {
    // A posição está fora dos limites do labirinto.
    return 0;
  }

  if (maze->array[new_position->y][new_position->x] == '*' ||
      maze->array[new_position->y][new_position->x] == '#')
  {
    // A posição contém uma parede.
    return 0;
  }

  if (maze->array[new_position->y][new_position->x] == '.')
    // Ele já andou naquele local
    return 0;
/*
  if ((index >= 2) && (new_position->y == routeTraveled->positions[index - 2].y &&
  new_position->x == routeTraveled->positions[index - 2].x) && isRecursion)
  {
    /*
     * (Index - 2). Pois ele soma 1 para uma possível posicao futura na chamada
     * da funcao (+1) e pois ele quer ver uma posicao anterior a atual (+1).
     * Totalizando 2 posicoes a mais que a ser verificada.
     */
    //return 0;
  //}

  return 1;
}

int find(Position *mouse, Maze *maze, Route *route, int index)
{
  if ((mouse->y == maze->finalPosY && mouse->x == maze->finalPosX))
  {
    // O rato encontrou a saída do labirinto.

    /*
     * Quando acha a saída, armazena o tamanho do caminho que teve ao
     * chegar.
     */
    if (route->distance < route->minDistance)
    {
      route->minDistance = route->distance;

      for (int i = 0; i < route->distance; i++)
      {
        route->minPositions[i] = route->positions[i];
      }

      route->distance = 0;
    }

    route->size = index;
    return 1;
  }

  // Define as quatro ações possíveis.
  Position actions[4] = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}};

  // Testa com os 4 movimentos possíveis.
  for (int i = 0; i < 4; i++)
  {

    Position new_position = {mouse->y + actions[i].y,
                             mouse->x + actions[i].x}; // Atualiza a posição.

    // Verifica se a posição for válida
    if (isValid(maze, &new_position))
    {
      route->positions[index] =
          new_position; // Nova posição armazenada no array.
      route->distance++;

      // Adiciona ponto onde andou
      if (maze->array[new_position.y][new_position.x] != 'M')
        maze->array[new_position.y][new_position.x] = '.';

      if (find(&new_position, maze, route, index + 1))
      {
        // Caminho encontrado.

        return 1;
      }
      if (maze->array[new_position.y][new_position.x] != 'M')
        maze->array[new_position.y][new_position.x] = ' ';
      // Desfazendo alterações antes de explorar a proxima ação.
      route->distance--;
    }
  }

  // Não há caminho válido a partir desta posição.
  return 0;
}