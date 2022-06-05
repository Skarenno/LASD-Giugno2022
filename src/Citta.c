#include "Citta.h"

/*********** FUNZIONI PER FILE ALBERGHI ************/
/***************************************************/

GraphCitta* leggiFileAlberghi(GraphCitta* grafo, char message[]) {
	// Dichirazione variabili
	grafo = AllocaGrafoC();
	FILE *fp;
	char *riga = NULL;
	riga = (char *)malloc((maxRiga+1)*sizeof(char));
	char albergo[STRING_MAX], *token;
	int tempo, i = 0, posizione = 0, tipo;

	// Verifiche sul file
	fp = fopen(message, "r");
	if(!VerificaFile(fp, message)){
		FreeC(grafo);
		return NULL;
	}
	fseek(fp, 0, SEEK_SET);

	// Inizio funzione
	while(!feof(fp)) {
		fscanf(fp, "%s", riga);
		token = strtok(riga, ";");
		strcpy(albergo, token);
		token = strtok(NULL, ";");
		tipo = atoi(token);

		InserisciVerticeC(grafo, albergo, tipo);
		while(token!=NULL) {
			token = strtok(NULL, ";");
			if(token==NULL)
				continue;
			if(i==0)
				strcpy(albergo, token);
			if(i==1)
				tipo = atoi(token);
			if(i==2) {
				tempo = atoi(token);
				i = -1;
				addArcoC(grafo, posizione, albergo, tempo, tipo);
			}
			i++;
		}
		posizione++;
	}
	ScriviChiaviAlberghi(grafo);

	free(riga);
	fclose(fp);
	return grafo;
}


void scriviFileAlberghi(GraphCitta* grafo, char message[]) {
	FILE* fp;
	if((fp=fopen(message, "w"))==NULL) {
		printf("Impossibile aprire il file\n");
		exit(1);
	}
	EdgeCitta* tmp = NULL;
	int j = 0;
	for(int i=0; i<grafo->numVertici; i++) {
		tmp = grafo->adj[i];
		while(tmp!=NULL) {
			if(j==1)
				fprintf(fp, ";%s;%d;%d", tmp->albergo, tmp->tipo, tmp->tempo);
			if(j==0) {
				fprintf(fp, "%s;%d", tmp->albergo, tmp->tipo);
				j++;
			}
			if(tmp->next==NULL) {
				if(i==(grafo->numVertici-1)) {
					tmp = tmp->next;
					continue;
				}
				fprintf(fp, "\n");
			}
			tmp = tmp->next;
		}
		j = 0;
	}
	fclose(fp);
}



/*********** FUNZIONI PER IL GRAFO CITTA ***********/
/***************************************************/
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

EdgeCitta* creaArcoC (char* albergo, int tempo, int tipo) {
    EdgeCitta* NuovoArco = (EdgeCitta*)malloc(sizeof(EdgeCitta));

    if(NuovoArco == NULL){
        printf("\nErrore Allocazione Arco");
        exit(EXIT_FAILURE);
    }

    strcpy(NuovoArco->albergo, albergo);
    NuovoArco->next = NuovoArco->prec = NULL;
    NuovoArco->tempo = tempo;
    NuovoArco->tipo = tipo;

    return NuovoArco;
}

void InserisciVerticeC(GraphCitta* G, char *albergo, int tipo) {
    for(int i = 0; i< G->numVertici; i++){
        if(strcmp(albergo, G->adj[i]->albergo) == 0){ //Già esistente
            return;
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
    G->adj[G->numVertici] = creaArcoC(albergo, 0, tipo);
    G->adj[G->numVertici]->next = NULL;
    G->numVertici++;
}

void addArcoC(GraphCitta* grafo, int posizione, char albergo[], int tempo, int tipo) {
	EdgeCitta* tmp = grafo->adj[posizione]->next;

	while(tmp !=NULL) { /*Controlla che l'arco non sia giÃ  esistente*/
		if(strcmp(albergo, tmp->albergo) == 0)
			return;

		tmp = tmp->next;
	}

    tmp = creaArcoC(albergo, tempo, tipo);
    tmp->prec = grafo->adj[posizione];
    tmp->next = grafo->adj[posizione]->next;
    if(tmp->next != NULL)
    	tmp->next->prec = tmp;

    grafo->adj[posizione]->next = tmp;
	grafo->numArchi++;
}


int isEmptyC(GraphCitta* grafo) {
	if(grafo==NULL)
		return 1;
	if(grafo->adj==NULL)
		return 1;
	return 0;
}

int numVerticiC(GraphCitta* grafo) {
	return grafo->numVertici;
}

int numArchiC(GraphCitta* grafo) {
	return grafo->numArchi;
}

GraphCitta* FreeC(GraphCitta* grafo) {
	if(grafo==NULL)
		return NULL;
	if(grafo->adj==NULL) {
		free(grafo);
		return NULL;
	}
	for(int i=0; i<grafo->numVertici; i++) {
		if(grafo->adj[i]==NULL) {
			free(grafo->adj[i]);
		} else if(grafo->adj[i]->next==NULL) {
			free(grafo->adj[i]);
		} else {
			EdgeCitta* tmp = grafo->adj[i]->next;
			while(tmp!=NULL) {
				tmp = tmp->next;
				free(grafo->adj[i]->next);
				grafo->adj[i]->next = tmp;
			}
			free(grafo->adj[i]);
		}
	}
	free(grafo->adj);
	free(grafo);
	return NULL;
}

GraphCitta* rimuoviVerticeC(GraphCitta* grafo, EdgeCitta* vertice) {
	GraphCitta* grafo1 = AllocaGrafoC();
	if(isEmptyC(grafo))
		return grafo;
	for(int i=0; i<grafo->numVertici; i++) {
		if(strcmp(grafo->adj[i]->albergo, vertice->albergo)!=0)
			InserisciVerticeC(grafo1, grafo->adj[i]->albergo, grafo->adj[i]->tipo);
	}
	int j = 0;
	for(int i=0; i<grafo->numVertici; i++) {
		if(strcmp(grafo->adj[i]->albergo, vertice->albergo)!=0) {
			EdgeCitta* tmp = grafo->adj[i]->next;
			while(tmp!=NULL) {
				if(strcmp(tmp->albergo, vertice->albergo)!=0)
					addArcoC(grafo1, j, tmp->albergo, tmp->tempo, tmp->tipo);
				tmp = tmp->next;
			}
			j++;
		}
	}
	ScriviChiaviAlberghi(grafo1);
	FreeC(grafo);
	return grafo1;
}

GraphCitta* rimuoviArcoC(GraphCitta* grafo, EdgeCitta* vertice1, EdgeCitta* vertice2) {
	if(isEmptyC(grafo))
		return grafo;
	EdgeCitta* tmp = vertice1->next;
	while(tmp!=NULL) {
		if((strcmp(tmp->albergo, vertice2->albergo)) == 0 && (strcmp(tmp->prec->albergo, vertice1->albergo) == 0)) {
			vertice1->next = tmp->next;
			if(tmp->next!=NULL)
				tmp->next->prec = vertice1;
			free(tmp);
			grafo->numArchi-=2;
			return grafo;
		} else if((strcmp(tmp->albergo, vertice2->albergo)) == 0 && (strcmp(tmp->prec->albergo, vertice1->albergo) != 0)) {
			tmp->prec->next = tmp->next;
			if(tmp->next!=NULL)
				tmp->next->prec = tmp->prec;
			free(tmp);
			grafo->numArchi-=2;
			return grafo;
		}
		tmp = tmp->next;
	}
	return grafo;
}

void ScriviChiaviAlberghi(GraphCitta* grafo){
	EdgeCitta* Cursor = NULL;

	for(int i = 0; i < grafo->numVertici; i++){
		grafo->adj[i]->key = i;
	}

	for(int i = 0; i < grafo->numVertici; i++){
		Cursor = grafo->adj[i]->next;
		while(Cursor){
			Cursor->key = VerificaAlbergo(grafo, Cursor->albergo);
			Cursor = Cursor->next;
		}
	}
	return;
}


void stampaGrafoC(GraphCitta* grafo){
	if(isEmptyC(grafo)) {
		printf("Grafo Vuoto\n");
		return;
	}
	for(int i=0; i<grafo->numVertici; i++) {
		EdgeCitta* tmp = grafo->adj[i]->next;
		printf("Vertice (%d) %s: |", grafo->adj[i]->key, grafo->adj[i]->albergo);
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

/***************************************************/
/***************************************************/


/**************** FUNZIONI GENERICHE ***************/
/***************************************************/

// Ritorna il nome del Path del file della citta corrispondente a partire dal nome della città
char *pathFileC(char nomeCitta[]) {
	char *path = (char*)malloc((strlen("./src/FILES/Alberghi/")+STRING_MAX+4)*sizeof(char));
	strcpy(path, "./src/FILES/Alberghi/");
	strcat(path, nomeCitta);
	strcat(path, ".txt");
	return path;
}



EdgeCitta* TrovaVertice (GraphCitta* grafo, char nome[]){
	for(int i = 0; i < grafo->numVertici; i++){
		if(strcmp(nome, grafo->adj[i]->albergo) == 0)
			return grafo->adj[i];
	}
	return NULL;
}


void stampaAlberghi(GraphCitta* grafo){
	if(grafo==NULL)
		printf("Nessun Albergo da Mostrare\n");
	printf("- ");
	for(int i = 0; i < grafo->numVertici; i++){
		if(grafo->adj[i]->tipo==0) {
			printf("%s", grafo->adj[i]->albergo);
			if(i < grafo->numVertici - 1){
					printf(" - ");
			} else
				printf("\n");
		}
	}
}

void stampaAlberghiAlt(GraphCitta* grafo){
	if(grafo==NULL)
		printf("Nessun Albergo da Mostrare\n");
	for(int i = 0; i < grafo->numVertici; i++){
		printf("%s", grafo->adj[i]->albergo);
		if(i < grafo->numVertici - 1){
				printf(" - ");
		} else
			printf("\n");
	}
}

int VerificaAlbergo(GraphCitta* grafo, char albergo[]){ // ritorna indice se esiste
	for(int i = 0; i < grafo->numVertici; i++){
		if(strcmp(grafo->adj[i]->albergo, albergo) == 0){
			return i;
		}
	}

	return -1;
}

int VerificaTipo(GraphCitta* grafo, int tipo){ // ritorna indice se esiste
	for(int i = 0; i < grafo->numVertici; i++){
		if(grafo->adj[i]->tipo==tipo){
			return i;
		}
	}

	return -1;
}
