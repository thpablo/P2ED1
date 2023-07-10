#ifndef LIST_H
#define LIST_H

#include "maze.h" 

// NODE
typedef struct cell{
    struct cell *pProx; // Ponteiro para proxima
    Position *positions; 
} Cell;

// LIST
typedef struct list{
    Cell *Head, *End;
    int tam;
} Lista;

#endif // LIST_H