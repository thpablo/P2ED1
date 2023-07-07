#include "maze.h" 

typedef struct cell{
    struct cell *pProx; // Ponteiro para proxima
    Position *positions; 
} Cell;


typedef struct list{
    Cell *Head, *End;
    int tam;
} Lista;
