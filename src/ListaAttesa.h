#ifndef ATTESA_H
#define ATTESA_H

#include "standard_header.h"
#define ATTESA "./src/FILES/ATTESA.txt"

typedef struct l_node {
	char partenza[STRING_MAX];
	char arrivo[STRING_MAX];
	int tipo;

	struct l_node *next;
}ListaAttesa;

ListaAttesa* inizializzaNodo(ListaAttesa *nodo, char *partenza, char*arrivo, int tipo);
ListaAttesa* inserisciNodo(ListaAttesa *lista, ListaAttesa *nodo);
ListaAttesa *rimuoviNodoAttesa(ListaAttesa *Attesa, ListaAttesa *nodo);
ListaAttesa* leggiAttesa(ListaAttesa *lista);
void scriviAttesa(ListaAttesa *lista);
ListaAttesa *svuotaLista(ListaAttesa *lista);
void stampaAttesa(ListaAttesa *lista);

#endif
