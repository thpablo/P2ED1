#include "maze.h" 
#include <stdlib.h>

typedef struct cell{
    struct cell *pProx; // Ponteiro para proxima
    Position *positions; 
} Cell;


typedef struct list{
    Cell *Head, *End;
    int tam;
} Lista;

void freeFilaOrPilha(Lista* FilaOrPilha){
    free(FilaOrPilha->Head);
    free(FilaOrPilha);
}

void freeFilaOrPilha(Lista* );