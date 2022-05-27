#include <stdio.h>
#include <stdlib.h>

#include "standard_header.h"
#include "Viaggi.h"
#include "GestioneUtenti.h"
#include "Citta.h"

/*
 * main.c
 *
 *  Created on: 20 mag 2022
 *      Author: valerio, giovanni, salvatore
 */


/*
 *  TIPO_UTENTE: 1. User
 * 				 2. Amministratore
 *
 */

int main(){

	Utente* UtenteAttuale, *ListaUtenti = NULL;
	unsigned short int tipo_utente;
	tipo_utente = SelezioneAccesso();

	if(SelezioneAccesso == 1){	// Utente normale
		UtenteAttuale = SchermataIniziale(ListaUtenti);
	}
	else{
		// Funzioni amministratore
	}



	/*GraphViaggi* grafo = NULL;
	grafo = leggiFileViaggi(grafo);
	stampaGrafo(grafo);*/
	GraphCitta *grafo = NULL;
	char *path = pathFileC("Bari");
	printf("%s\n", path);
	grafo = leggiFileAlberghi(grafo, path);
	stampaGrafoC(grafo);
	//scriviFileAlberghi(grafo, path);
	free(path);
	grafo = FreeC(grafo);
	return 0;
}
