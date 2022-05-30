#include "ListaAttesa.h"

ListaAttesa* inizializzaNodo(ListaAttesa *nodo, char *partenza, char *arrivo) {
	nodo = (ListaAttesa*)malloc(sizeof(ListaAttesa));
	strcpy(nodo->partenza, partenza);
	strcpy(nodo->arrivo, arrivo);
	printf("\n%s %s", nodo->partenza, nodo->arrivo);
	fflush(stdout);
	nodo->next = NULL;

	return nodo;
}

ListaAttesa* inserisciNodo(ListaAttesa *lista, ListaAttesa *nodo) {

	if(lista == NULL){
		nodo->numElem = 1;
		return nodo;
	}

	nodo->next = lista;
	nodo->numElem = lista->numElem + 1;
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
	while(!feof(fp)) {
		fscanf(fp, "%s %s", partenza, arrivo);
		ListaAttesa *nodo = NULL;
		lista = inserisciNodo(lista, inizializzaNodo(nodo, partenza, arrivo));
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
			fprintf(fp, "%s %s\n", lista->partenza, lista->arrivo);
		else
			fprintf(fp, "%s %s", lista->partenza, lista->arrivo);
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

void stampaAttesa(ListaAttesa *lista) {
	if(lista==NULL) {
		printf("ListaAttesa: EMPTY\n");
		return;
	}
	printf("ListaAttesa: ");
	while(lista!=NULL) {
		printf("Partenza: %s Arrivo: %s\n", lista->partenza, lista->arrivo);
		lista = lista->next;
	}
	return;
}
