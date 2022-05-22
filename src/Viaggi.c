#include "Viaggi.h"
#define CITTA "./FILES/Citta.txt"


GraphViaggi* AllocaGrafo() {
	GraphViaggi* grafo = (GraphViaggi*)malloc(sizeof(GraphViaggi));

	if(grafo==NULL) {
		printf("Errore: impossibile allocare memoria per il grafo\n");
		exit(1);
	}
	grafo->adj = NULL;
	grafo->numArchi = 0;
	grafo->numVertici = 0;

	return grafo;
}

//GraphViaggi* PopolaGraphViaggi(){
//
//}






EdgeViaggi* creaArco (char* citta, int prezzoAereo, int prezzoTreno, int tempoAereo, int  tempoTreno){
    EdgeViaggi* NuovoArco = (EdgeViaggi*)malloc(sizeof(EdgeViaggi));
    
    if(NuovoArco == NULL){
        printf("\nErrore Allocazione Arco");
        exit(EXIT_FAILURE);
    }

    strcpy(NuovoArco->citta, citta);
    NuovoArco->next = NuovoArco->prec = NULL;
    NuovoArco->prezzoAereo = prezzoAereo;
    NuovoArco->prezzoTreno = prezzoTreno;
    NuovoArco->tempoAereo = tempoAereo;
    NuovoArco->tempoTreno = tempoTreno;

    return NuovoArco;
}

void InserisciVertice(GraphViaggi* G, char *citta){
    for(int i = 0; i< G->numVertici; i++){
        if(strcmp(citta, G->adj[i]->citta) == 0){
            return;                             // Già esistente
        }
    }

    if(G->adj == NULL){
        G->adj = (EdgeViaggi**)malloc(sizeof(EdgeViaggi*));
    }
    else{
        G->adj = (EdgeViaggi**)realloc(G->adj, (G->numVertici + 1)*sizeof(EdgeViaggi*));
    }

    if(G->adj == NULL){
        printf("\nErrore allocazione vertice.");
        exit(1);
    }
    G->adj[G->numVertici] = creaArco(citta, 0, 0, 0, 0);
    G->adj[G->numVertici]->next = NULL;
    G->numVertici++;
}

void addArco(GraphViaggi* grafo, int posizione, char citta[], int prezzoAereo, int prezzoTreno, int tempoAereo, int  tempoTreno){
	EdgeViaggi* tmp = grafo->adj[posizione]->next;

	while(tmp !=NULL) { /*Controlla che l'arco non sia già esistente*/
		if(strcmp(citta, tmp->citta) == 0)
			return;

		tmp = tmp->next;
	}
    
    tmp = creaArco(citta, prezzoAereo, prezzoTreno, tempoAereo, tempoTreno);
    tmp->prec = grafo->adj[posizione];
    tmp->next = grafo->adj[posizione]->next;
    if(tmp->next != NULL)
    	tmp->next->prec = tmp;

    grafo->adj[posizione]->next = tmp;
	grafo->numArchi++;
}


void stampaGrafo(GraphViaggi* grafo){
	/*if(isEmpty(grafo)) {
		printf("Grafo Vuoto\n");
		return;
	}*/
	for(int i=0; i<grafo->numVertici; i++) {
		EdgeViaggi* tmp = grafo->adj[i]->next;
		printf("Vertice %s: |", grafo->adj[i]->citta);
		if(tmp==NULL) {
			printf("EMPTY|\n");
			continue;
		}
		while(tmp->next!=NULL) {
			printf("%s -> ", tmp->citta);
			tmp = tmp->next;
		}
		printf("%s|\n", tmp->citta);
	}
}
