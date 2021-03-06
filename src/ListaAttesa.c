#include "ListaAttesa.h"

ListaAttesa* creaNodo(char *partenza, char *arrivo, int tipo) {
	ListaAttesa* nodo = NULL;
	nodo = (ListaAttesa*)malloc(sizeof(ListaAttesa));
	if(nodo == NULL) {
		printf("Errore Memoria per il Nodo Non Allocata\n");
		exit(-1);
	}
	nodo->next = NULL;
	strcpy(nodo->partenza, partenza);
	strcpy(nodo->arrivo, arrivo);
	nodo->tipo = tipo;
	return nodo;
}

ListaAttesa* aggiungiNodoTesta(ListaAttesa* Attesa, char *partenza, char *arrivo, int tipo) {
	ListaAttesa *nodo = NULL;
	if(Attesa==NULL) {
		nodo = creaNodo(partenza, arrivo, tipo);
		return nodo;
	}
	ListaAttesa *tmp = Attesa;
	while(tmp!=NULL) { // Controlla che il nodo non eista gi? nella lista di attesa
		if(strcmp(tmp->partenza, partenza)==0 && strcmp(tmp->arrivo, arrivo)==0 && tmp->tipo==tipo)
			return Attesa;
		tmp = tmp->next;
	}
	nodo = creaNodo(partenza, arrivo, tipo);
	nodo->next = Attesa;
	return nodo;
}

ListaAttesa* leggiAttesa(ListaAttesa *lista) {
	FILE *fp;
	if((fp=fopen(ATTESA, "r"))==NULL) {
		printf("Impossibile aprire il file ATTESA.txt\n");
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
	char *partenza = (char*)malloc(sizeof(char)*STRING_MAX);
	char *arrivo = (char*)malloc(sizeof(char)*STRING_MAX);
	int tipo;
	while(!feof(fp)) {
		fscanf(fp, "%s %s %d", partenza, arrivo, &tipo);
		lista = aggiungiNodoTesta(lista, partenza, arrivo, tipo);
	}
	free(partenza);
	free(arrivo);
	fclose(fp);

	return lista;
}

void scriviAttesa(ListaAttesa *lista) {
	FILE *fp;
	if((fp=fopen(ATTESA, "w"))==NULL) {
		printf("Impossibile aprire in scrittura il file ATTESA.txt\n");
		exit(1);
	}
	if(lista==NULL) {
		fclose(fp);
		return;
	}
	while(lista!=NULL) {
		if(lista->next!=NULL)
			fprintf(fp, "%s %s %d\n", lista->partenza, lista->arrivo, lista->tipo);
		else
			fprintf(fp, "%s %s %d", lista->partenza, lista->arrivo, lista->tipo);
		lista = lista->next;
	}
	fclose(fp);

	return;
}

ListaAttesa *svuotaLista(ListaAttesa *lista) {
	if(lista==NULL)
		return NULL;
	ListaAttesa *tmp = lista;
	while(tmp!=NULL) {
		lista = lista->next;
		free(tmp);
		tmp = lista;
	}
	return NULL;
}

ListaAttesa *rimuoviNodoAttesa(ListaAttesa *Attesa, ListaAttesa *nodo){

    ListaAttesa *tmp;

    if(Attesa==NULL || nodo==NULL) return NULL;

    if(Attesa==nodo){

        tmp=Attesa->next;

        free(Attesa);

        return tmp;

    }

    Attesa->next=rimuoviNodoAttesa(Attesa->next, nodo);

    return Attesa;

}

void stampaAttesa(ListaAttesa *lista) {
	if(lista==NULL) {
		printf("EMPTY\n");
		return;
	}
	while(lista!=NULL) {
		printf("Partenza: %s Arrivo: %s ", lista->partenza, lista->arrivo);
		if(lista->tipo==0)
			printf("Trasporto: Aereo\n");
		else
			printf("Trasporto: Treno\n");
		lista = lista->next;
	}
	return;
}
