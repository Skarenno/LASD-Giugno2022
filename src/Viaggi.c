#include "Viaggi.h"

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
    for(int i = 0; i<G->numVertici; i++){
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
        printf("Errore allocazione vertice.\n");
        exit(1);
    }
    G->adj[G->numVertici] = creaArco(citta, 0, 0, 0, 0);
    G->adj[G->numVertici]->next = NULL;
    G->numVertici++;
}

void addArco(GraphViaggi* grafo, int posizione, char citta[], float prezzoAereo, float prezzoTreno, int tempoAereo, int  tempoTreno){
	EdgeViaggi* tmp = grafo->adj[posizione]->next;
	while(tmp!=NULL) { /*Controlla che l'arco non sia già esistente*/
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

GraphViaggi* leggiFileViaggi(GraphViaggi* grafo) {
	grafo = AllocaGrafo();
	FILE *fp;
	if((fp=fopen(CITTA, "r"))==NULL) {
		printf("Impossibile aprire il file Viaggi.txt\n");
		exit(1);
	}
	if (fp!=NULL) { /*Controlla che il file non sia vuoto*/
	   	fseek(fp, 0, SEEK_END);
	   	int size = ftell(fp);
		if (size==0) {
	       	return NULL;
		}
	}
	fseek(fp, 0, SEEK_SET);
	char *riga = NULL;
	/*char c;
	int count = 0, maxRiga = 0;*/
	/*Conto quanto � lunga la riga pi� grande in modo da allocare la memoria per riga*/
	/*while((c=fgetc(fp))!=EOF) {
		if(c!='\n')
			count++;
		if(c=='\n') {
			if(maxRiga<count)
				maxRiga = count;
			count = 0;
		}
	}*/
	fseek(fp, 0, SEEK_SET);
	riga = (char *)malloc((maxRiga+1)*sizeof(char));
	char citta[STRING_MAX], *token;
	float prezzoAereo, prezzoTreno;
	int tempoAereo, tempoTreno, i = 0, posizione = 0;
	while(!feof(fp)) {
		fscanf(fp, "%s", riga);
		token = strtok(riga, ";");
		if(token==NULL)
			InserisciVertice(grafo, riga);
		else
			InserisciVertice(grafo, token);
		while(token!=NULL) {
			token = strtok(NULL, ";");
			if(token==NULL)
				continue;
			if(i==0)
				strcpy(citta, token);
			if(i==1)
				prezzoAereo = atof(token);
			if(i==2)
				tempoAereo = atoi(token);
			if(i==3)
				prezzoTreno = atof(token);
			if(i==4) {
				tempoTreno = atoi(token);
				i = -1;
				addArco(grafo, posizione, citta, prezzoAereo, prezzoTreno, tempoAereo, tempoTreno);
			}
			i++;
		}
		posizione++;
	}
	free(riga);
	fclose(fp);
	return grafo;
}

int isEmpty(GraphViaggi* grafo) {
	if(grafo==NULL)
		return 1;
	if(grafo->adj==NULL)
		return 1;
	return 0;
}

void stampaGrafo(GraphViaggi* grafo){
	if(isEmpty(grafo)) {
		printf("Grafo Vuoto\n");
		return;
	}
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
