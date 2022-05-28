#include "standard_header.h"
#define ATTESA "./src/FILES/ATTESA.txt"

typedef struct l_node {
	char nome[STRING_MAX];
	int numElem;

	struct l_node *next;
}ListaAttesa;

ListaAttesa* inizializzaNodo(ListaAttesa *nodo, char *nome);
ListaAttesa* inserisciNodo(ListaAttesa *lista, ListaAttesa *nodo);
ListaAttesa* leggiAttesa(ListaAttesa *lista);
void scriviAttesa(ListaAttesa *lista);
ListaAttesa *svuotaLista(ListaAttesa *lista);
void stampaAttesa(ListaAttesa *lista);
