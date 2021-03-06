/*
 * UserProgram.c
 *
 *  Created on: 26 mag 2022
 */

#include "UserProgram.h"
#include "Dijkstra.h"
#include "ListaAttesa.h"

void userDashboard(Utente* ListaUtenti, Utente* user, GraphViaggi* GrafoViaggi){
	int prenotato = 0, choice, tipoViaggio, indiceAlbPartenza, indiceAlbArrivo;
	char yn, *nomeArrivo = NULL, albergoArrivo[STRING_MAX];
	float nuovoSaldo = 0.0, dijkstraTempoMin = 0.0;
	Utente* Cursor = ListaUtenti;
	GraphCitta* grafoCitta=AllocaGrafoC();
	bool annulla = false;

	nomeArrivo = (char*)malloc(sizeof(char)*STRING_MAX);
	printf("\n");
	printf("\n***********************\nBentornato, %s\n",user->nome);
	printf("Il tuo saldo attuale: %.2f euro\n",user->saldo);

	while (true) {
		while(true) {
			printf("\nImmettere azione da eseguire (1. Prenota Viaggio - 2. Carica Saldo - 3. Chiudi Programma): ");
			fflush(stdout);
			fflush(stdin);
			if(!scanf("%d", &choice) || (choice!=1 && choice!=2 && choice!=3)) {
				printf("Valore non Valido\n");
				continue;
			}
			break;
		}
		switch(choice) {
			case 1:
				prenotato = EffettuaPrenotazione(ListaUtenti, user, GrafoViaggi, nomeArrivo, &tipoViaggio);
				if(prenotato==0) {
					printf("TORNO AL MENU PRINCIPALE\n***********************\n");
					break;
				}

				Cursor = ListaUtenti;

				printf("\n*****************\nVIAGGIO PRENOTATO\n(Il tuo nuovo Saldo: %.2f).\n\nSi vuole scegliere un albergo dove alloggiare? (y/n): ", user->saldo);
				do{
					fflush(stdout);
					fflush(stdin);
					scanf(" %c", &yn);
					yn = tolower(yn);
					switch(yn) {
						case 'y':
							grafoCitta = leggiFileAlberghi(grafoCitta,pathFileC(nomeArrivo));
							//stampaGrafoC(grafoCitta);//Per Debug
							printf("Gli alberghi disponibili nella citt? di %s sono:\n", nomeArrivo);
							stampaAlberghi(grafoCitta);
							do{
								printf("\nScegli uno tra gli alberghi disponibili ('Annulla' per annullare): ");
								fflush(stdout);
								fflush(stdin);
								scanf("%s",albergoArrivo);
								if(strcmp(albergoArrivo, "Annulla") == 0){
									annulla = true;
									break;
								}
								indiceAlbArrivo = VerificaAlbergo(grafoCitta,albergoArrivo);
								if (indiceAlbArrivo == -1) {
									printf("Albergo non presente\n");
									continue;
								}
								if(grafoCitta->adj[indiceAlbArrivo]->tipo==1 || grafoCitta->adj[indiceAlbArrivo]->tipo==2) {
									printf("Non si ? Selezionato un Albergo!\n");
									continue;
								}
								break;
							} while (true);

							if(annulla == true){
								printf("Hai annullato la selezione dell'albergo ma il tuo viaggio ? comunque stato prenotato!");
								break;
							}
							indiceAlbPartenza = VerificaTipo(grafoCitta,tipoViaggio+1);
							printf("\n**Calcolo della tratta migliore da %s ", grafoCitta->adj[indiceAlbPartenza]->albergo);

							if(tipoViaggio+1 == 1)
								printf("(Aeroporto)**");

							else
								printf("(Stazione)**");

							fflush(stdout);
							sleep(1);

							dijkstraTempoMin = DijkstraAlberghi(grafoCitta,indiceAlbPartenza,indiceAlbArrivo);
							printf("Il tempo Totale della tratta ?: %.0f minuti\n", dijkstraTempoMin);
							break;
						case 'n':
							printf("Ok, non mostrer? la tratta per l'albergo!");
							break;
						default:
							printf("\nValore non valido! Riprovare (y/n): ");
							continue;
					}
					printf("\nGRAZIE PER AVER PRENOTATO CON NOI!\n");
					break;
				}while(true);

				break;
			case 2:
				while(true) {
					printf("Quanto vuoi Caricare? ");
					fflush(stdout);
					fflush(stdin);
					if(!scanf("%f", &nuovoSaldo) || nuovoSaldo<0) {
						printf("Valore non Valido\n");
						continue;
					}
					user->saldo+=nuovoSaldo;

					Cursor = ListaUtenti;
					while(Cursor != NULL){
						if(strcmp(user->nome, Cursor->nome) == 0){
							Cursor->saldo = user->saldo;
							break;
						}
						Cursor = Cursor->next;
					}

					printf("Nuovo Saldo: %.2f\n", user->saldo);
					RiscriviFileUtenti(ListaUtenti);
					break;
				}
				break;
			case 3:
				printf("Arrivederci\n");
				exit(EXIT_SUCCESS);
				break;
			default: printf("Valore non Valido\n");
		}
	}

}

int EffettuaPrenotazione(Utente* ListaUtenti, Utente* user, GraphViaggi* GrafoViaggi, char *nomeArrivo, int *tipoViaggio) {
	int AT=0;	// Aereo/Treno
	int PT=0;	// Prezzo migliore/Tratta migliore
	float distance=0.0;

	char partenza[STRING_MAX];
	char arrivo[STRING_MAX];

	int confirm = 0;
	int key_partenza, key_arrivo;
	int tipoDijkstra;
	float price=0.0;
	ListaAttesa *Attesa = NULL;
	Attesa = leggiAttesa(Attesa);

	Utente* Cursor = ListaUtenti;
	printf("\nAl momento le mete disponibili sono: \n");
	StampaMete(GrafoViaggi);

	// LETTURA PARTENZA
	do{
		printf("Inserisci la citt? di partenza: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%s", partenza);
		key_partenza = VerificaCitta(GrafoViaggi, partenza);
		if(key_partenza != -1)
			break;
		else
			printf("---Nome citt? non valido... riprovare.\n");
	}while(true);

	// LETTURA ARRIVO
	do{
		printf("Inserisci la citt? di arrivo: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%s", arrivo);
		key_arrivo = VerificaCitta(GrafoViaggi, arrivo);
		if(key_arrivo != -1)
			break;
		else
			printf("---Nome citt? non valido... riprovare.\n");
	}while(true);

	do{
		printf("*************\nSi ? selezionato il viaggio %s -> %s\n", partenza, arrivo);
		printf("Inserisci il tipo di trasporto desiderato (0. Aereo - 1. Treno): ");
		fflush(stdout);
		fflush(stdin);

		if(!scanf("%d",&AT) || (AT != 1 && AT != 0)){
			printf("Valore non valido");
			continue;
		}

		printf("Inserire il tipo di viaggio (0. Pi? economico - 1. Pi? rapido) : ");

		fflush(stdout);
		fflush(stdin);

		if(!scanf("%d",&PT) || (PT != 1 && PT != 0)){
			printf("Valore non valido");
			continue;
		}

		break;
	}while(true);

	if(!AT){
		if(!PT){
			tipoDijkstra = 0;
		}
		else
			tipoDijkstra = 1;
	}
	else{
		if(!PT){
			tipoDijkstra = 2;
		}
		else
			tipoDijkstra = 3;
	}

	price = DijkstraViaggi(GrafoViaggi, key_partenza, key_arrivo, tipoDijkstra, &distance);

	if(price >= INT_MAX){
		printf("\n****TRATTA NON DISPONIBILE****\n");
		Attesa = aggiungiNodoTesta(Attesa, GrafoViaggi->adj[key_partenza]->citta, GrafoViaggi->adj[key_arrivo]->citta, AT);
		scriviAttesa(Attesa);
		printf("Tratta Aggiunta alla Lista Attesa\n\n");
		sleep(1);
		return 0;
	}
	printf("La durata di questo viaggio ? di %.0f minuti\n", distance);
	printf("Il prezzo di questo viaggio ? di %.2f?, vuoi prenotarlo? (1: Conferma. 0: Annulla e torna al menu principale.)\n", price);
	while(true) {
		printf("Immetti selezione: ");
		fflush(stdout);
		fflush(stdin);
		if(!scanf("%d",&confirm) || (confirm!=1 && confirm!=0)) {
			printf("Valore non Valido\n");
			continue;
		}
		break;
	}
	if(confirm) {
		if(user->saldo>=price) {

			user->saldo-=price;
			strcpy(nomeArrivo, arrivo);
			*tipoViaggio = AT;

			while(Cursor != NULL){
				if(strcmp(user->nome, Cursor->nome) == 0){
					Cursor->saldo = user->saldo;
					break;
				}
				Cursor = Cursor->next;
			}

			RiscriviFileUtenti(ListaUtenti);

			return 1;
		} else
			printf("Saldo non sufficiente. Devi caricare almeno: %.2f\n", price-user->saldo);
	} else
		printf("**VIAGGIO ANNULLATO**\n");
	return 0;
}
