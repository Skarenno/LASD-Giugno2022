#include "Citta.h"
#define ALBERGHI "./FILES/Citta.txt"


GraphCitta* AllocaGrafoC() {
	GraphCitta* grafo = (GraphCitta*)malloc(sizeof(GraphCitta));

	if(grafo==NULL) {
		printf("Errore: impossibile allocare memoria per il grafo\n");
		exit(1);
	}
	grafo->adj = NULL;
	grafo->numArchi = 0;
	grafo->numVertici = 0;

	return grafo;
}

//GraphCitta* PopolaGraphCitta(){
//
//}






EdgeCitta* creaArcoC (char* albergo, int tempo){
    EdgeCitta* NuovoArco = (EdgeCitta*)malloc(sizeof(EdgeCitta));

    if(NuovoArco == NULL){
        printf("\nErrore Allocazione Arco");
        exit(EXIT_FAILURE);
    }

    strcpy(NuovoArco->albergo, albergo);
    NuovoArco->next = NuovoArco->prec = NULL;
    NuovoArco->tempo = tempo;

    return NuovoArco;
}

void InserisciVerticeC(GraphCitta* G, char *albergo){
    for(int i = 0; i< G->numVertici; i++){
        if(strcmp(albergo, G->adj[i]->albergo) == 0){
            return;                             // Già esistente
        }
    }

    if(G->adj == NULL){
        G->adj = (EdgeCitta**)malloc(sizeof(EdgeCitta*));
    }
    else{
        G->adj = (EdgeCitta**)realloc(G->adj, (G->numVertici + 1)*sizeof(EdgeCitta*));
    }

    if(G->adj == NULL){
        printf("\nErrore allocazione vertice.");
        exit(1);
    }
    G->adj[G->numVertici] = creaArcoC(albergo, 0);
    G->adj[G->numVertici]->next = NULL;
    G->numVertici++;
}

void addArcoC(GraphCitta* grafo, int posizione, char albergo[], int tempo){
	EdgeCitta* tmp = grafo->adj[posizione]->next;

	while(tmp !=NULL) { /*Controlla che l'arco non sia già esistente*/
		if(strcmp(albergo, tmp->albergo) == 0)
			return;

		tmp = tmp->next;
	}

    tmp = creaArcoC(albergo, tempo);
    tmp->prec = grafo->adj[posizione];
    tmp->next = grafo->adj[posizione]->next;
    if(tmp->next != NULL)
    	tmp->next->prec = tmp;

    grafo->adj[posizione]->next = tmp;
	grafo->numArchi++;
}


void stampaGrafoC(GraphCitta* grafo){
	/*if(isEmpty(grafo)) {
		printf("Grafo Vuoto\n");
		return;
	}*/
	for(int i=0; i<grafo->numVertici; i++) {
		EdgeCitta* tmp = grafo->adj[i]->next;
		printf("Vertice %s: |", grafo->adj[i]->albergo);
		if(tmp==NULL) {
			printf("EMPTY|\n");
			continue;
		}
		while(tmp->next!=NULL) {
			printf("%s -> ", tmp->albergo);
			tmp = tmp->next;
		}
		printf("%s|\n", tmp->albergo);
	}
}
