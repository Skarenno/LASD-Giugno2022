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

EdgeViaggi* creaArco (char* citta, float prezzoAereo, float prezzoTreno, int tempoAereo, int  tempoTreno){
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
        	printf("Meta già esistente!, %s", citta);
            return;                             // GiÃ  esistente
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
	while(tmp!=NULL) { /*Controlla che l'arco non sia giÃ  esistente*/
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

GraphViaggi* rimuoviArcoV(GraphViaggi* grafo, char* vertice1, char* vertice2) {
	if(isEmpty(grafo))
		return grafo;
	EdgeViaggi* verticePartenza = NULL;
	EdgeViaggi* verticeArrivo = NULL;
	for(int i=0; i<grafo->numVertici; i++) {
		if(strcmp(vertice1, grafo->adj[i]->citta)==0)
			verticePartenza = grafo->adj[i];
		if(strcmp(vertice2, grafo->adj[i]->citta)==0)
			verticeArrivo = grafo->adj[i];
	}
	EdgeViaggi* tmp = verticePartenza->next;
	while(tmp!=NULL) {
		if(tmp==verticeArrivo && tmp->prec==verticePartenza) {
			verticePartenza->next = tmp->next;
			if(tmp->next!=NULL)
				tmp->next->prec = verticePartenza;
			free(tmp);
			grafo->numArchi-=2;
			return grafo;
		} else if(tmp==verticeArrivo && tmp->prec!=verticePartenza) {
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
	ScriviChiavi(grafo);
	free(riga);
	fclose(fp);
	return grafo;
}

void scriviFileViaggi(GraphViaggi* grafo){

	if(!isEmpty(grafo)){
		FILE* FileViaggi = fopen(CITTA, "w+");
		if(FileViaggi == NULL){
			printf("\n---Errore scrittura database città---");
		}

		EdgeViaggi* Cursor = NULL;

		for(int i = 0; i < grafo->numVertici; i++){
			Cursor = grafo->adj[i];
			fprintf(FileViaggi, "%s;", Cursor->citta);
			Cursor = Cursor->next;
			while(Cursor != NULL){
				fprintf(FileViaggi, "%s;%.2f;%d;%.2f;%d;", Cursor->citta, Cursor->prezzoAereo, Cursor->tempoAereo, Cursor->prezzoTreno, Cursor->tempoTreno);
				Cursor = Cursor->next;
			}
			if(i == grafo->numVertici -1)
				continue;

			fprintf(FileViaggi, "\n");


		}

		fclose(FileViaggi);
	}

	return;
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
		printf("Vertice (%d) %s: |", grafo->adj[i]->key, grafo->adj[i]->citta);
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

void ScriviChiavi(GraphViaggi* grafo){
	EdgeViaggi* Cursor = NULL;

	for(int i = 0; i < grafo->numVertici; i++){
		grafo->adj[i]->key = i;
	}

	for(int i = 0; i < grafo->numVertici; i++){
		Cursor = grafo->adj[i]->next;
		while(Cursor){
			Cursor->key = VerificaCitta(grafo, Cursor->citta);
			Cursor = Cursor->next;
		}
	}
	return;
}

void freeGraphViaggi(GraphViaggi* grafo){

	EdgeViaggi* Cursor;

	for(int i = 0; i < grafo->numVertici; i++){
		Cursor = grafo->adj[i];
		while(grafo->adj[i] != NULL){
			Cursor = grafo->adj[i];
			grafo->adj[i] = grafo->adj[i]->next;
			free(Cursor);
		}
	}

	free(grafo);
}

void StampaMete (GraphViaggi* GrafoViaggi){
	for (int i = 0; i < GrafoViaggi->numVertici; i++){
		printf("%s ", GrafoViaggi->adj[i]->citta);
		if(i < GrafoViaggi->numVertici - 1)
			printf("- ");
	}

	printf("\n");
}


int VerificaCitta(GraphViaggi* GrafoViaggi, char citta[]){ // ritorna 1 se esiste
	for(int i = 0; i < GrafoViaggi->numVertici; i++){
		if(strcmp(GrafoViaggi->adj[i]->citta, citta) == 0){
			return i;
		}
	}

	return -1;
}

GraphViaggi *rimuoviVerticeV(GraphViaggi *grafo, char nomeCitta[]) {
	GraphViaggi *grafo1 = AllocaGrafo();
	EdgeViaggi *vertice = NULL;
	int k = 0;

	for(int i=0; i<grafo->numVertici; i++) {
		if(strcmp(nomeCitta, grafo->adj[i]->citta)==0)
			vertice = grafo->adj[i];
		else {
			InserisciVertice(grafo1, grafo->adj[i]->citta);
			grafo1->adj[k]->key = k;
			k++;
		}
	}
	int j = 0;
	for(int i=0; i<grafo->numVertici; i++) {
		if(grafo->adj[i]!=vertice) {
			EdgeViaggi *tmp = grafo->adj[i]->next;
			while(tmp!=NULL) {
				if(strcmp(tmp->citta, vertice->citta)!=0)
					addArco(grafo1, j, tmp->citta, tmp->prezzoAereo, tmp->prezzoTreno, tmp->tempoAereo, tmp->tempoTreno);
				tmp = tmp->next;
			}
			j++;
		}
	}
	freeGraphViaggi(grafo);
	return grafo1;
}

GraphViaggi *updateArchi(GraphViaggi *grafo, char *vertice1, char *vertice2, int tipo) {
	int indice1, indice2;
	indice1 = VerificaCitta(grafo, vertice1);
	indice2 = VerificaCitta(grafo, vertice2);
	EdgeViaggi *tmp = grafo->adj[indice1]->next;
	while(tmp!=NULL) {
		if(indice2==tmp->key) {
			if(tipo==1) {
				tmp->prezzoAereo = 0;
				tmp->tempoAereo = 0;
				break;
			} else {
				tmp->prezzoTreno = 0;
				tmp->tempoTreno = 0;
				break;
			}
		}
		tmp = tmp->next;
	}
	tmp = grafo->adj[indice2]->next;
	while(tmp!=NULL) {
		if(indice1==tmp->key) {
			if(tipo==1) {
				tmp->prezzoAereo = 0;
				tmp->tempoAereo = 0;
				if(tmp->tempoTreno==0) {
					grafo = rimuoviArcoV(grafo, vertice1, vertice2);
					printf("Collegamento tra le città rimosso, perchè non esistono più ne treni ne aerei\n");
				}
				break;
			} else {
				tmp->prezzoTreno = 0;
				tmp->tempoTreno = 0;
				if(tmp->tempoAereo==0) {
					grafo = rimuoviArcoV(grafo, vertice1, vertice2);
					printf("Collegamento tra le città rimosso, perchè non esistono più ne treni ne aerei\n");
				}
				break;
			}
		}
		tmp = tmp->next;
	}
	return grafo;
}
