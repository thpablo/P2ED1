#include "list.h"
#include "maze.h"
#include <stdlib.h>
#include <stdbool.h>

Lista *iniciaFila(){
    Lista *filaAlocated = (Lista*) malloc(sizeof(Lista));
    
    // Falha na alocacao
    if(filaAlocated == NULL)
        return NULL;

    // Aloca cabeca
    filaAlocated->Head = (Cell *) malloc(sizeof(Cell));
    
    // Falha na alocacao
    if(filaAlocated->Head == NULL){
        free(filaAlocated);
        return NULL;
    }

    // Final aponta para cabeca
    filaAlocated->End = filaAlocated->Head;

    // Proximo da cabeca aponta para NULL
    filaAlocated->Head->pProx = NULL;

    return filaAlocated;
}


bool isEmptyFila(Lista *Fila){
    return Fila->Head->pProx == NULL;
}

bool insertPosFila(Lista* fila, Position* pos){

    // Nova Celula alocada
    Cell *newCell = (Cell *) malloc(sizeof(Cell));

    // Falha na alocacao da nova celula
    if(newCell == NULL)
        return false;

    // Nova Celula recebe as posicoes
    newCell->positions = pos;

    // Proximo da Antiga celula final aponta para nova Celula
    fila->End->pProx = newCell;
    
    // Final aponta para nova celula
    fila->End = newCell;

    // Proximo da nova celula aponta para NULL
    newCell->pProx = NULL;

    fila->tam++;

    return true;
}
void showPos(Lista *Fila)
{
    Cell *cellAux = Fila->Head->pProx;
    while (cellAux != NULL)
    {
        printf("x = %d y = %d\n", cellAux->positions->x, cellAux->positions->y);
        cellAux = cellAux->pProx;
    }
}

bool removePosFila(Lista *fila){

    // Se fila for vazia
    if(isEmptyFila(fila))
        return false;
    

    // AuxCell recebe o proximo da primeira celula (2nd Item);
    Cell *auxCell = fila->Head->pProx->pProx;
    
    // Free nas posicoes do primeiro item **?
     free(fila->Head->pProx->positions);

    // Free no primeiro item
    free(fila->Head->pProx);

    // Proximo da cebaca recebe auxCell
    fila->Head->pProx = auxCell;

    return true;
}
void freeFila(Lista* Fila){
    free(Fila->Head);
    free(Fila);
}


int main()
{
    Position *pos = allocatePosition();
    pos->x = 3;
    pos->y = 4;

    Position *pos2 = allocatePosition();
    pos2->x = 5;
    pos2->y = 8;

    Lista *Fila = iniciaFila();

    if (isEmptyFila(Fila))
        printf("e vazia\n");


    // 1 insercao
    if (insertPosFila(Fila, pos))
        printf("Inseriu\n");
    
    // 2 insercao
    if (insertPosFila(Fila, pos2))
        printf("Inseriu\n");
    
    showPos(Fila);

    if(removePosFila(Fila))
        printf("Removeu\n");
    showPos(Fila);

    if(removePosFila(Fila))
        printf("Removeu\n");
    
    showPos(Fila);

    if (isEmptyFila(Fila))
    {
        printf("e vazia, %d\n", isEmptyFila(Fila));
    }

    freeFila(Fila);

    return 0;
}