#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>

// TAD MAZE

typedef struct maze
{
  char **array;
  int y, x;
  int finalPosY, finalPosX;
}Maze;


typedef struct position
{
  int y;
  int x;
} Position;

typedef struct route
{
  Position *positions;    // Array de posições percorridas
  Position *minPositions; // Array de posições do menor caminho
  int distance;           // Distância total da rota
  int minDistance;        // Menor distância percorrida
  int size;               // Tamanho atual dos arrays
}Route;

// Aloca o TAD MAZE.
Maze *allocateMaze(int, int);

// Desaloca o TAD MAZE.
void freeMaze(Maze *);

// Aloca o TAD Route.
Route *allocateRoute(int);

// Desaloca o TAD Route.
void freeRoute(Route *);

// Aloca uma posição
Position *allocatePosition();

// Desaloca o espaço reservado para uma posição.
void freePosition(Position *);

// Armazena o labirinto do arquivo em uma matriz.
void readMaze(Maze *, Position *);

// Imprime a soluçao do labirinto.
void printMaze(Maze *);

// Imprime a distância e as coordenadas feitas pelo mouse.
void printRoute(Route *);

// Verifica se e valido
int isValid(Maze *maze, Position *new_position);

// Função recursiva que procura o menor caminho.
int find(Position *, Maze *, Route *, int);

#endif // MAZE_H