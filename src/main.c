#include <stdio.h>
#include <stdlib.h>

#include "standard_header.h"
#include "Viaggi.h"
#include "GestioneUtenti.h"

/*
 * main.c
 *
 *  Created on: 20 mag 2022
 *      Author: valerio, giovanni, salvatore
 */


int main(){
	//Utente* ListaUtenti = NULL;
	//SchermataIniziale(ListaUtenti);


	GraphViaggi* G = AllocaGrafo();
	InserisciVertice(G, "Napoli");
	addArco(G, 0, "Bologna", 23 ,57, 7, 2);
	addArco(G, 0, "Firenze", 23 ,45 ,67 ,54);

	stampaGrafo(G);

	return 0;
}
