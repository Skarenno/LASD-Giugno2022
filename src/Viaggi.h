#ifndef VIAGGI_H
#define VIAGGI_H

#include "standard_header.h"
#define CITTA "./src/FILES/VIAGGI.txt"


// Se non c'è collegamento Treno/Aereo il peso associato al tempo e al prezzo è 0

typedef struct edgeViaggi { /*Gestisce sia grafi orientati che non*/
	float prezzoAereo, prezzoTreno;
    int tempoAereo, tempoTreno;
    int key;

    char citta[STRING_MAX];

	struct edgeViaggi* next;
	struct edgeViaggi* prec;
}EdgeViaggi;

typedef struct graphViaggi {
	int numVertici, numArchi;
	EdgeViaggi** adj;
}GraphViaggi;


GraphViaggi* AllocaGrafo();
void InserisciVertice(GraphViaggi* G, char *citta);
EdgeViaggi* CreaArco (char* citta, float prezzoAereo, float prezzoTreno, int tempoAereo, int  tempoTreno);
void addArco(GraphViaggi* grafo, int posizione, char *citta, float prezzoAereo, float prezzoTreno, int tempoAereo, int  tempoTreno);
GraphViaggi* leggiFileViaggi(GraphViaggi* grafo);
int isEmpty(GraphViaggi* grafo);
void stampaGrafo(GraphViaggi* grafo);
void freeGraphViaggi(GraphViaggi* grafo);
void StampaMete (GraphViaggi* GrafoViaggi);
int VerificaCitta(GraphViaggi* GrafoViaggi, char citta[]);
GraphViaggi *rimuoviVerticeV(GraphViaggi *grafo, char nomeCitta[]);
GraphViaggi* rimuoviArcoV(GraphViaggi* grafo, char* vertice1, char* vertice2);
void scriviFileViaggi(GraphViaggi* grafo);
void ScriviChiavi(GraphViaggi* grafo);
GraphViaggi *updateArchi(GraphViaggi *grafo, char *vertice1, char *vertice2, int tipo);

#endif
