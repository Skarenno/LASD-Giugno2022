#include "ListaAttesa.h"

ListaAttesa* inizializzaNodo(ListaAttesa *nodo, char *nome) {
	nodo = (ListaAttesa*)malloc(sizeof(ListaAttesa));
	strcpy(nodo->nome, nome);
	nodo->next = NULL;

	return nodo;
}

ListaAttesa* inserisciNodo(ListaAttesa *lista, ListaAttesa *nodo) {
	if(lista==NULL)
		lista->numElem = 0;
	nodo->next = lista;
	lista = nodo;
	lista->numElem++;

	return lista;
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
	char *nome = (char*)malloc(sizeof(char)*STRING_MAX);
	while(!feof(fp)) {
		fscanf(fp, "%s", nome);
		ListaAttesa *nodo = NULL;
		lista = inserisciNodo(lista, inizializzaNodo(nodo, nome));
	}
	free(nome);
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
			fprintf(fp, "%s ", lista->nome);
		else
			fprintf(fp, "%s", lista->nome);
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
	while(lista->next!=NULL) {
		printf("%s -> ", lista->nome);
		lista = lista->next;
	}
	printf("%s\n", lista->nome);
	return;
}
