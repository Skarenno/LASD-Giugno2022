#include "standard_header.h"

typedef struct edgeCitta {
	int tempo;

    char albergo[STRING_MAX];

	struct edgeCitta* next;
	struct edgeCitta* prec;
}EdgeCitta;

typedef struct graphCitta {
	int numVertici, numArchi;
	EdgeCitta** adj;
}GraphCitta;


GraphCitta* AllocaGrafoC();
void InserisciVerticeC(GraphCitta* G, char* albergo);
EdgeCitta* CreaArcoC (char* albergo, int tempo);
void addArcoC(GraphCitta* grafo, int posizione, char *albergo, int tempo);
int isEmptyC(GraphCitta* grafo);
void stampaGrafoC(GraphCitta* grafo);
