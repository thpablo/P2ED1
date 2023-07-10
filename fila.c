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

    filaAlocated->tam = 0;

    return filaAlocated;
}


bool isEmptyFila(Lista *Fila){
    return Fila->Head->pProx == NULL;
}

bool insertPosFila(Lista* fila, Position pos){

    // Nova Celula alocada
    Cell *newCell = (Cell *) malloc(sizeof(Cell));

    newCell->positions = allocatePosition();

    // Falha na alocacao da nova celula
    if(newCell == NULL)
        return false;

    // Nova Celula recebe as posicoes
    newCell->positions->x = pos.x;
    newCell->positions->y = pos.y;

    // Proximo da Antiga celula final aponta para nova Celula
    fila->End->pProx = newCell;
    
    // Final aponta para nova celula
    fila->End = newCell;

    // Proximo da nova celula aponta para NULL
    newCell->pProx = NULL;

    fila->tam++;

    return true;
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
    while(!isEmptyFila(Fila)){
        removePosFila(Fila);
    }
    free(Fila->Head);
    free(Fila);
}

int BFS(Maze *maze, Lista *fila, Position *mouse){
    Position actions[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    Position newPos = *mouse; //Inicia com a posicao inicial do rato

    //mouse->x,y posicao inicial do rato
    if(!insertPosFila(fila, *mouse)){
        printf("Nao foi possivel inserir a posicao");
        return false;
    }

    while(!isEmptyFila(fila)){

        // Verifica se chegou no final -> Retorna tamanho da fila
        if( fila->End->positions->x == maze->finalPosX && 
            fila->End->positions->y == maze->finalPosY){
                return true;
            }

        bool caminhoValido = false;

        for(int i = 0; i < 4; i++){
            newPos.x = fila->Head->pProx->positions->x + actions[i].x;
            newPos.y = fila->Head->pProx->positions->y + actions[i].y;

            if(isValid(maze, &newPos)){
                insertPosFila(fila, newPos);
                caminhoValido = true;
                maze->array[newPos.y][newPos.x] = 'o';
                
                break;
            }
        }

        if(!caminhoValido){
            //if(maze->array[newPos.y][newPos.x] == '.')
                //maze->array[newPos.y][newPos.x] = ' ';
            removePosFila(fila);
        }
    }
    return false; //Imprimir tentativa
} 

void resolveBFS(Maze *maze, Position *mouse)
{
    Lista *fila = iniciaFila();

    BFS(maze, fila, mouse);
    fila->tam -= 2;
    printf("%d\n", fila->tam);
    // Libera os espaços alocados.
    freeFila(fila);
}