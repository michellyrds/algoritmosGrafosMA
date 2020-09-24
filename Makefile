all: Main.cpp MatrizAdjacencia.o
	g++ -o Grafo Main.cpp MatrizAdjacencia.o

MatrizAdjacencia.o: MatrizAdjacencia.cpp MatrizAdjacencia.h
	g++ -c MatrizAdjacencia.cpp