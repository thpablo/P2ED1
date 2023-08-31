# Descrição
Projeto desenvolvido para o segundo trabalho prático da matéria de Estrutura de Dados 1 da Universidade Federal de Ouro Preto. O objetivo do projeto foi criar um código responsável para encontrar o caminho de um labirinto, através da implementação de Busca em Largura e Busca em Profundidade, utilizando pilhas e filas. 

# Pré-Requisitos

- [X] Compilador C (GCC)
- [X] CMake (optional)

# Compilação
Use o seguinte comando caso tenha instalado Make:
`make`
Ou compile manualmente:
`gcc *.c -c` 
`gcc *.o -o exe`

# Uso
Para usar os testes disponíveis no repositório, basta usar passando o caminho para a pasta e o teste desejável, por exemplo:

`exe < tests/cp-7-11-2`

*Note: Você pode ver a saída referente ao caso de teste usado utilizando o comando `cat teste.out` caso esteja no linux* 

Caso queira dar uma entrada diferente dos testes, deve utilizar o comando:

`exe`
E informar as dimensões do labirinto, sendo primeiro a altura e em seguida a largura, além da escolha do método de procura.
- *p: Irá procurar utilizando pilha.*
- *f: Irá procurar utlizando filas*
  
Após isso, o labirinto seguindo o padrão de paredes serem representadas por astericos '*' e a posição inicial do rato indicada com a letra M. A saída é sempre a última posição inferior direita. Exemplo:
```
7 11
p
***********
* *
********* *
*M* * * *
* *** * * *
*
***********
```
