#ifndef CITTA_H
#define CITTA_H

#include "standard_header.h"

typedef struct edgeCitta {
	int tempo;
	int tipo; //0=Meta, 1=Aereoporto, 2=Stazione Treno

    char albergo[STRING_MAX];

	struct edgeCitta* next;
	struct edgeCitta* prec;
}EdgeCitta;

typedef struct graphCitta {
	int numVertici, numArchi;
	EdgeCitta** adj;
}GraphCitta;


GraphCitta* AllocaGrafoC();
void InserisciVerticeC(GraphCitta* G, char *albergo, int tipo);
EdgeCitta* creaArcoC (char* albergo, int tempo, int tipo);
void addArcoC(GraphCitta* grafo, int posizione, char albergo[], int tempo, int tipo);
GraphCitta* leggiFileAlberghi(GraphCitta* grafo, char message[]);
void scriviFileAlberghi(GraphCitta* grafo, char message[]);
int isEmptyC(GraphCitta* grafo);
int numVerticiC(GraphCitta* grafo);
int numArchiC(GraphCitta* grafo);
GraphCitta* FreeC(GraphCitta* grafo);
GraphCitta* rimuoviVerticeC(GraphCitta* grafo, EdgeCitta* vertice);
GraphCitta* rimuoviArcoC(GraphCitta* grafo, EdgeCitta* vertice1, EdgeCitta* vertice2);
char *pathFileC(char nomeCitta[]);
void stampaGrafoC(GraphCitta* grafo);

#endif
