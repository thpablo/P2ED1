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

void removeAllFila(Lista *fila){
    while(removePosFila(fila));
}


int BFS(Maze *maze, Lista *fila, Position *mouse){
    Position actions[4] = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}};
    Position newPos = *mouse; //Inicia com a posicao inicial do rato

    //mouse->x,y posicao inicial do rato
    if(!insertPosFila(fila, *mouse)){
        printf("Nao foi possivel inserir a posicao");
        return false;
    }

    int res = false;

    while(!isEmptyFila(fila)){

        // Verifica se chegou no final -> Retorna tamanho da fila
        if( fila->End->positions->x == maze->finalPosX && 
            fila->End->positions->y == maze->finalPosY   ){
                printf("%d\n", fila->tam - 1); //Nao sei porque - 3
                printMaze(maze);
                return fila->tam;
            }

        bool caminhoValido = false;

        for(int i = 0; i < 4; i++){
            newPos.x = fila->Head->pProx->positions->x + actions[i].x;
            newPos.y = fila->Head->pProx->positions->y + actions[i].y;

            if(isValid(maze, &newPos)){
                insertPosFila(fila, newPos);
                caminhoValido = true;
                maze->array[newPos.y][newPos.x] = '.';
                fila->tam++;
                break;
            }
        }

        if(!caminhoValido){
            removePosFila(fila);
        }
    }
    printf("RES: %d\n", res);
    return res; //Imprimir tentativa

} 

int main()
{
    int x = 0, y = 0;

    // Lendo dimensões do labirinto.
    scanf("%d %d", &y, &x);

    Lista* fila = iniciaFila();
    char flag;
    // Lendo a flag que diz o tipo de retorno do programa.
    scanf(" %c", &flag);

    Maze *maze = allocateMaze(y, x); // Alocando labirinto.

    Position *mouse = allocatePosition(); // Aloca Rato

    readMaze(maze, mouse); // Lê os caracteres que formam o labirinto.

    // Verifica se existe um menor caminho.
    int res = BFS(maze, fila, mouse);

    if (res)
        printf("Saiu\n");
    else
        printf("EPIC FAIL");

    // Libera os espaços alocados.
    freePosition(mouse);

    removeAllFila(fila);

    freeFilaOrPilha(fila);
    
    freeMaze(maze);

    return 0;
}