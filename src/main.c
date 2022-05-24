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
	Utente* UtenteAttuale, *ListaUtenti = NULL;
	pirntf("Ciao");
	// Si vuole entrare come admin o utente?

	// if(admn)
		//
	// else
		//

	UtenteAttuale = SchermataIniziale(ListaUtenti);

	GraphViaggi* grafo = NULL;
	grafo = leggiFileViaggi(grafo);
	stampaGrafo(grafo);

	return 0;
}
