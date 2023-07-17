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

    pilha->tam = 0;

    return pilha;
}

bool isEmptyPilha(Lista *pilha)
{
    return pilha->Head->pProx == NULL;
}

bool insertPosPilha(Lista *pilha, Position pos)
{
    Cell *newCell = (Cell *) malloc(sizeof(Cell));
    newCell->positions = allocatePosition();

    // Falha na alocacao da nova celula
    if (newCell == NULL)
        return false;

    // Posicao da nova celula recebe valores de pos;
    newCell->positions->x = pos.x;
    newCell->positions->y = pos.y;

    /* Se for o primeiro item a ser inserido */
    if(isEmptyPilha(pilha)){

        // Proximo da cabeca recebe nova celula
        pilha->Head->pProx = newCell;
        
        // Final aponta para nova celula
        pilha->End = newCell;

        // Proximo da nova Celula aponta para NULL
        newCell->pProx = NULL;
        
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

    // Free na posicao da ultima celula
    if(!isEmptyPilha(pilha))
        freePosition(pilha->Head->pProx->positions);
    
    // Free na ultima celula
    free(pilha->Head->pProx);

    pilha->Head->pProx = cellAux;

    return true;
}


void freePilha(Lista* pilha){
    free(pilha->Head);
    free(pilha);
}


int DFS(Maze *maze, Lista *pilha, Position *mouse){
    Position actions[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    Position newPos = *mouse; //Inicia com a posicao inicial do rato
    //mouse->x,y posicao inicial do rato
    if(!insertPosPilha(pilha, *mouse)){
        printf("Nao foi possivel inserir a posicao");
        return false;
    }

    int res = false;

    while(!isEmptyPilha(pilha)){

        // Verifica se chegou no final -> Retorna tamanho da pilha
        if( pilha->Head->pProx->positions->x == maze->finalPosX && 
            pilha->Head->pProx->positions->y == maze->finalPosY)
            res = true;

        bool caminhoValido = false;

        for(int i = 0; i < 4; i++){
            newPos.x = pilha->Head->pProx->positions->x + actions[i].x;
            newPos.y = pilha->Head->pProx->positions->y + actions[i].y;

            if(isValid(maze, &newPos)){
                insertPosPilha(pilha, newPos);
                caminhoValido = true;
                maze->array[newPos.y][newPos.x] = 'o';
                break;
            }
        }

        if(!caminhoValido){
            removePosPilha(pilha);
        }
    }
    return res; //Imprimir tentativa
}

void resolveDFS(Maze *maze, Position *mouse)
{
    Lista* pilha = iniciaPilha();

    DFS(maze, pilha, mouse);
    pilha->tam -= 2;
    printf("%d\n", pilha->tam);

    // Libera os espaços alocados.
    freePilha(pilha);
}
