#include "list.h"
#include "maze.h"

#include <stdlib.h>
#include <stdbool.h>

Lista *iniciaPilha()
{
    Lista *pilha = (Lista *)malloc(sizeof(Lista));

    // Falha na alocacao da pilha
    if (pilha == NULL)
        return NULL;

    pilha->Head = (Cell *) malloc(sizeof(Cell));

    // Falha na alocacao de Head
    if (pilha->Head == NULL)
    {
        free(pilha);
        return NULL;
    }

    pilha->End = pilha->Head;
    pilha->Head->pProx = NULL;

    return pilha;
}

bool isEmptyPilha(Lista *pilha)
{
    return pilha->Head->pProx == NULL;
}

bool insertPosPilha(Lista *pilha, Position *pos)
{
    Cell *newCell = (Cell *) malloc(sizeof(Cell));

    // Falha na alocacao da nova celula
    if (newCell == NULL)
        return false;

    // Posicao da nova celula recebe pos;
    newCell->positions = pos;

    /* Se for o primeiro item a ser inserido */
    if(isEmptyPilha(pilha)){
        // Proximo da cabeca recebe nova celula
        pilha->Head->pProx = newCell;
        
        // Final aponta para nova celula
        pilha->End = newCell;

        // Proximo da nova Celula aponta para NULL
        newCell->pProx = NULL;
        
        printf(" Primeira celula: %d %d \n", pilha->Head->pProx->positions->x, pilha->Head->pProx->positions->y );
        pilha->tam++;
         
        return true;
    }
    
    // Proximo Nova celula aponta para a antiga ultima celula. 
    newCell->pProx = pilha->Head->pProx;

    // Proximo da Cabeca aponta para nova Celula
    pilha->Head->pProx = newCell;
    
    pilha->tam++;
    
    return true;
}

bool removePosPilha(Lista *pilha)
{
    // Verifica se a pilha e vazia
    if (isEmptyPilha(pilha))
        return false;
    
    // Celula auxiliar recebe atual penultimo item
    Cell *cellAux = pilha->Head->pProx->pProx;

    printf("%d\n", &pilha->Head->pProx);

    // Free na posicao da ultima celula
    if(pilha->Head->pProx != NULL)
        freePosition(pilha->Head->pProx->positions);
    
    // Free na ultima celula
    free(pilha->Head->pProx);

    pilha->Head->pProx = cellAux;
    
    pilha->tam--;

    return true;
}

/* Mostrar a posicao da celula */
void showPos(Lista *pilha)
{
    Cell *cellAux = pilha->Head->pProx;
    while (cellAux != NULL)
    {
        printf("x = %d y = %d\n", cellAux->positions->x, cellAux->positions->y);
        cellAux = cellAux->pProx;
    }
}

void freePilha(Lista* pilha){
    free(pilha->Head);
    free(pilha);
}

int main()
{
    Position *pos = allocatePosition();
    pos->x = 3;
    pos->y = 4;

    Position *pos2 = allocatePosition();
    pos2->x = 5;
    pos2->y = 8;

    Lista *pilha = iniciaPilha();

    if (isEmptyPilha(pilha))
        printf("e vazia\n");


    // 1 insercao
    if (insertPosPilha(pilha, pos))
        printf("Inseriu\n");
    
    // 2 insercao
    if (insertPosPilha(pilha, pos2))
        printf("Inseriu\n");
    
    showPos(pilha);

    if(removePosPilha(pilha))
        printf("Removeu\n");
    
    if(removePosPilha(pilha))
        printf("Removeu\n");
    
    showPos(pilha);

    if (isEmptyPilha(pilha))
    {
        printf("e vazia, %d\n", isEmptyPilha(pilha));
    }

    freePilha(pilha);

    return 0;
}