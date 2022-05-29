#include <stdio.h>
#include <stdlib.h>

#include "standard_header.h"
#include "GestioneUtenti.h"
#include "Citta.h"
#include "UserProgram.h"

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

	/**** DICHIARAZIONE VARIABILI ****/
	unsigned short int tipo_utente;
	GraphViaggi* GrafoViaggi = NULL;
	GraphCitta* GrafoAlberghi = NULL;

	/**** INIZIALIZZAZIONE VARIABILI *****/
	GrafoViaggi = leggiFileViaggi(GrafoViaggi);
	GrafoAlberghi = NULL;

	/**** INIZIO UI ****/
	tipo_utente = SelezioneAccesso();

	// Accesso come utente base
	if(tipo_utente == 1){
		Utente* UtenteAttuale, *ListaUtenti = NULL;
		UtenteAttuale = SchermataIniziale(ListaUtenti);	// Schermata INIZIALE
		userDashboard(UtenteAttuale, GrafoViaggi);	//Schermata PRINCIPALE
	}

	// Accesso come amministratore
	else{
		/*
		Admin* AdminAttuale, *ListaAdmin = NULL;
		AdminAttuale = AccessoAdmin(ListaAdmin);
		*/
	}

	/**** FINE UI ****/


	// LIBERA MEMORIA
	freeGraphViaggi(GrafoViaggi);




/**** TEMP ****/
//	GraphViaggi* grafo = NULL;
//	grafo = leggiFileViaggi(grafo);
//	stampaGrafo(grafo);
//	addArco(grafo, 2, "Napoli", 45.56, 23.67, 120, 80);
//	scriviFileViaggi(grafo);
//
//	GraphCitta *grafo = NULL;
//	char *path = pathFileC("Bari");
//	printf("%s\n", path);
//	grafo = leggiFileAlberghi(grafo, path);
//	stampaGrafoC(grafo);
//	//scriviFileAlberghi(grafo, path);
//	free(path);
//	grafo = FreeC(grafo);
//	return 0;
}
