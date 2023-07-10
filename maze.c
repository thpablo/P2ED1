#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"

/* Só para deixar os pontos vermelhos */
#define RED "\033[31m"
#define RESET "\033[0m"

// Aloca o TAD MAZE.
Maze *allocateMaze(int y, int x)
{
  // Aloca memória para o TAD MAZE.
  Maze *maze = (Maze *)malloc(sizeof(Maze));

  // Define o tamanho do labirinto.
  maze->y = y;
  maze->x = x;

  // Conversao de tipos de variaveis para alocacao
  long unsigned int convertedY = (long unsigned int) y;
  long unsigned int convertedX = (long unsigned int) x;

  // Aloca memória para a matriz que representa o labirinto.
  maze->array = (char **) malloc(convertedY * sizeof(char *));
  for (int i = 0; i < y; i++)
    maze->array[i] = (char *) malloc(convertedX * sizeof(char));

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
  long unsigned int convertedMaxSize = (long unsigned int) MAX_SIZE;
  Route *route = (Route *)malloc(sizeof(Route));
  route->positions = (Position *)malloc(sizeof(Position) * convertedMaxSize);
  route->distance = 0;
  route->minPositions = (Position *)malloc(sizeof(Position) * convertedMaxSize);
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
        maze->inicialPosY = i;
        maze->inicialPosX = j;
      }
    }
    getchar(); // Descarta o caractere de quebra de linha após cada linha.
  }
}

// Função para imprimir o labirinto.
void printMaze(Maze *maze)
{
  maze->array[maze->inicialPosY][maze->inicialPosX] = 'M';
  for (int i = 0; i < maze->y; i++)
  {
    for (int j = 0; j < maze->x; j++)
    {
      
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

  if (maze->array[new_position->y][new_position->x] == 'o')
    // Ele já andou naquele local
    return 0;

  return 1;
}

int find(Position *mouse, Maze *maze, Route *route, int index)
{
  if ((mouse->y == maze->finalPosY && mouse->x == maze->finalPosX))
  {
    route->size = index;
    return 1;
  }

  // Define as quatro ações possíveis.
  Position actions[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  // Testa com os 4 movimentos possíveis.
  for (int i = 0; i < 4; i++)
  {

    Position new_position = {mouse->y + actions[i].y,
                             mouse->x + actions[i].x}; // Atualiza a posição.
    // Verifica se a posição for válida
    if (isValid(maze, &new_position))
    {
      route->positions[index] = new_position; // Nova posição armazenada no array.
      route->distance++;

      // Adiciona ponto onde andou
      if (maze->array[new_position.y][new_position.x] != 'M')
        maze->array[new_position.y][new_position.x] = 'o';

      if (find(&new_position, maze, route, index + 1))
      {
        // Caminho encontrado.
        return 1;
      }
      if (maze->array[new_position.y][new_position.x] != 'M'){
        maze->array[new_position.y][new_position.x] = ' ';
      }
      // Desfazendo alterações antes de explorar a proxima ação.
      route->distance--;
    }
  }
  // Não há caminho válido a partir desta posição.
  return 0;
}

int resolveRecursive(Maze *maze, Position *mouse, int x, int y){
    Route *route = allocateRoute(y * x); // Aloca o array de rotas.

      if(find(mouse, maze, route, 0)){
        printf("%d\n", route->size);  
        freeRoute(route);
        return 1;
      }

      freeRoute(route);
      return 0;
}