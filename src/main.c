#include <stdio.h>
#include <stdlib.h>

#include "standard_header.h"
#include "UserProgram.h"
#include "AdminProgram.h"
#include "Dijkstra.h"
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

	FILE* FileUtenti = fopen(U_FILE, "r");
	/**** INIZIALIZZAZIONE VARIABILI *****/
	GrafoViaggi = leggiFileViaggi(GrafoViaggi);
	GrafoAlberghi = NULL;

	/**** INIZIO UI ****/
	//stampaGrafo(GrafoViaggi); //Per Debug
	fflush(stdout);
	GrafoAlberghi = AllocaGrafoC();
	GrafoAlberghi = leggiFileAlberghi(GrafoAlberghi, pathFileC("Firenze"));

	tipo_utente = SelezioneAccesso();

	// Accesso come utente base
	if(tipo_utente == 1){
		Utente* UtenteAttuale, *ListaUtenti = NULL;
		UtenteAttuale = SchermataIniziale(ListaUtenti);	// Schermata INIZIALE

		ListaUtenti = NULL;
		ListaUtenti = LeggiFileUtenti(FileUtenti, ListaUtenti);

		//StampaListaUtenti(ListaUtenti);
		userDashboard(ListaUtenti, UtenteAttuale, GrafoViaggi);	//Schermata PRINCIPALE
	}

	// Accesso come amministratore
	else{
		Admin* AdminAttuale, *ListaAdmin = NULL;
		AdminAttuale = SchermataInizialeAdmin(ListaAdmin);
		adminDashboard(AdminAttuale, GrafoViaggi);
	}

	/**** FINE UI ****/


	// LIBERA MEMORIA
	freeGraphViaggi(GrafoViaggi);

	return 0;
}
