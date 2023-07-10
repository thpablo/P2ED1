all: fila.o maze.o pilha.o main.o
	@gcc fila.o maze.o pilha.o main.o -o exe -lm
	@rm -r fila.o
	@rm -r maze.o
	@rm -r pilha.o
	@rm -r main.o
maze.o: maze.c
	@gcc maze.c -c -Wall
pilha.o: pilha.c
	@gcc pilha.c -c -Wall
fila.o: fila.c
	@gcc fila.c -c -Wall
main.o: main.c
	@gcc main.c -c -Wall
run:
	@./exe
