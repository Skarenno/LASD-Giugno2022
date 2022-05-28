#include "standard_header.h"
#define CITTA "./src/FILES/Viaggi.txt"


// Se non c'è collegamento Treno/Aereo il peso associato al tempo e al prezzo è 0

typedef struct edgeViaggi { /*Gestisce sia grafi orientati che non*/
	float prezzoAereo, prezzoTreno;
    int tempoAereo, tempoTreno;

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
