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

    // Free na posicao da ultima celula
    if(!isEmptyPilha(pilha))
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
/*
A segunda parte do trabalho é muito parecida com a implementação com filas. A diferença está no ponto
em que ao invés de usar uma fila, uma pilha será usada.
Semelhante ao que foi feito com a fila, uma estrutura de dados do tipo pilha será usada para guardar
as posições dos diversos caminhos do labirinto. Esse tipo de implementação é chamada de Busca em
Profundidade. Apesar de ser uma estratégia conhecida por fazer um uso mais eficiente de utilização de
memória, não garante que a solução com o menor caminho será encontrado como na estratégia anterior.
Nessa estratégia, inicia-se inserindo na pilha vazia um item com a posição inicial do rato. A busca pela
saída é feita repetindo-se as seguintes instruções:
1. Desempilhe um item da fila.
2. Se o item desempilhado for nulo (NULL) retorne NULL.
3. Se o item desempilhado não for nulo, remove-se o item da pilha e empilha-se todas as posições vizinhas a fila.
*/

//Pilha iniciada no main

int DFS(Maze *maze, Lista *pilha, Position *mouse){
    Position actions[4] = {{0, -1}, {1, 0}, {-1, 0}, {0, 1}};
    
    Position newPos = *mouse; //Inicia com a posicao inicial do rato
    //mouse->x,y posicao inicial do rato
    if(!insertPosPilha(pilha, *mouse)){
        printf("Nao foi possivel inserir a posicao");
        return false;
    }

    while(!isEmptyPilha(pilha)){

        if(pilha->Head->pProx->positions->x == maze->finalPosX &&
        pilha->Head->pProx->positions->y == maze->finalPosY)
            return pilha->tam;

        for(int i = 0; i < 4; i++){
            newPos.x = newPos.x + actions[i].x;
            newPos.y = newPos.y + actions[i].y;

            if(isValid(maze, &newPos)){
                insertPosPilha(pilha, newPos);
            }
        }
    }
    return false; //Imprimir tentativa
}


int main()
{
    Position pos;
    pos.x = 3;
    pos.y = 4;


    Lista *pilha = iniciaPilha();

    if (isEmptyPilha(pilha))
        printf("e vazia\n");


    // 1 insercao
    if (insertPosPilha(pilha, pos))
        printf("Inseriu\n");
    
    // 2 insercao
    if (insertPosPilha(pilha, pos))
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