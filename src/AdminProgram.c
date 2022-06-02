
/*
 * UserProgram.c
 *
 *  Created on: 27 mag 2022
 */

#include "AdminProgram.h"


// Menu Principale per l'accesso Amministrativo
void adminDashboard(Admin* admin, GraphViaggi* grafo){
	// Dichiarazioni e inizializzazioni variabili
	unsigned short int choice;
	int confirm;
	char nome[STRING_MAX];
	char* nomeFile;

	FILE* FileCitta;
	ListaAttesa *lista = NULL;
	GraphCitta* GrafoCitta = AllocaGrafoC();
	EdgeCitta* Vertice;

	lista = leggiAttesa(lista);

	// Benvenuto
	printf("Bentornato, %s\n",admin->nome);
	printf("Al momento le mete inserite sono:\n");
	stampaGrafo(grafo);
	printf("\n");
	if(lista!=NULL) {
		printf("Mete da collegare\n");
		stampaAttesa(lista);
	}

	// Scelta ambiente di lavoro (VIAGGI / ALBERGHI)
	do {
		printf("\n Si vuole lavorare su citta (0) o alberghi(1): ");
		fflush(stdout);
		fflush(stdin);

		if(scanf("%hu", &choice))
			break;

		printf("\n Valore non valido");
	}while(true);


	/**** MENU LAVORO SU CITTA ****/
	if(!choice){
		confirm = 0;
		while (confirm!=4) {
			printf("\nImmettere azione da eseguire (1. Aggiungi Meta - 2. Elimina Meta - 3. Aggiungi Arco - 4. Chiudi programma):");
			fflush(stdout);
			fflush(stdin);

			if(scanf("%d",&confirm)) {
				switch(confirm) {

					// Aggiungere una nuova meta (vertice 0 del grafo)
					case 1:
						printf("Nome Citta: ");
						fflush(stdout);
						fflush(stdin);
						scanf("%s", nome);
						if(!VerificaCitta(grafo, nome)){
							FILE* New = fopen(pathFileC(nome), "w");
							fclose(New);
						}
						InserisciVertice(grafo, nome);
						grafo->adj[grafo->numVertici-1]->key = grafo->numVertici-1;
						scriviFileViaggi(grafo);
						break;

					// Eliminare una meta e tutte le tratte che portano ad essa
					case 2:
						StampaMete(grafo);
						printf("Meta da Cancellare: ");
						fflush(stdout);
						fflush(stdin);
						scanf("%s", nome);
						if(!VerificaCitta(grafo, nome)){
							printf("Citta non Esistente\nRiprova\n");
							break;
						}
						if(remove(pathFileC(nome)))
							printf("File di %s rimosso", nome);

						grafo = rimuoviVerticeV(grafo, nome);

						scriviFileViaggi(grafo);
						break;

					// Aggiungere una nuova tratta
					case 3:
						stampaGrafo(grafo);
						grafo = menuAggiungiMeta(grafo);
						scriviFileViaggi(grafo);
						break;

					// Tornare indietro
					case 4:
						printf("Ciao\n");
						freeGraphViaggi(grafo);
						grafo = NULL;
						exit(EXIT_SUCCESS);

					default: printf("Valore non Valido\nRiprovare\n");
				}
			} else{
				confirm = 0;
				printf("Tipo non Valido\n");
			}
		}
	}


	/**** MENU LAVORO SU ALBERGHI ****/
	else{
		confirm = 0;
		char nomePartenza[STRING_MAX];
		char nomeArrivo[STRING_MAX];
		int tempo, tipoPartenza, tipoArrivo;
		EdgeCitta *verticePartenza, *verticeArrivo;
		while(confirm != 4){
			printf("\nImmettere azione da eseguire (1. Aggiungi Alberghi - 2. Elimina Alberghi - 3. Aggiungi Arco - 4. Chiudi programma): ");
			fflush(stdout);
			fflush(stdin);
			if(scanf("%d", &confirm)){
				switch(confirm){
					/*** AGGIUNGI ALBERGO ***/
					case 1:
						StampaMete(grafo);
						while(true){
							printf("Scegli la città a cui vuoi aggiungere Alberghi: ");
							fflush(stdin);
							fflush(stdout);
							scanf("%s", nome);

							if(!VerificaCitta(grafo, nome)){
								printf("Citta non Esistente\nRiprova\n");
								continue;
							}
							break;
						}

						FileCitta = fopen(nomeFile = pathFileC(nome), "r");
						GrafoCitta = AggiungiAlbergo(GrafoCitta, grafo, FileCitta, nomeFile);
						scriviFileAlberghi(GrafoCitta, nomeFile);
						fclose(FileCitta);
						break;
					/*** FINE AGGIUNGI ***/

					/*** ELIMINA ALBERGO ***/
					case 2:
						StampaMete(grafo);
						printf("Di quale citta si vuole eliminare l'albergo? Immettere: ");
						fflush(stdin);
						fflush(stdout);

						scanf("%s", nome);
						if(!VerificaCitta(grafo, nome)){
							printf("Citta non Esistente\nRiprova\n");
							break;
						}

						GrafoCitta = leggiFileAlberghi(GrafoCitta, pathFileC(nome));
						stampaAlberghi(GrafoCitta);
						do{
							printf("\nNome albergo da eliminare: ");
							fflush(stdin);
							fflush(stdout);
							scanf("%s", nome);
							if(!VerificaAlbergo(GrafoCitta, nome)){
								printf("Albergo non esistente");
								continue;
							}

							Vertice = TrovaVertice(GrafoCitta, nome);
							if(Vertice->tipo != 0){
								printf("\n***Si è selezionato un Aeroporto o una Stazione. Impossibile eliminare.***\n");
								break;
							}
							if(Vertice != NULL){
								GrafoCitta = rimuoviVerticeC(GrafoCitta, Vertice);
								scriviFileAlberghi(GrafoCitta, nomeFile);
							}
							break;
						}while(true);

						break;
					/*** FINE ELIMINA ***/

					/*** AGGIUNGI ARCO ***/
					case 3:
						//TODO
						printf("Mete Presenti\n");
						StampaMete(grafo);
						printf("Su quale Meta si intende Lavorare? Immettere: ");
						fflush(stdin);
						fflush(stdout);
						scanf("%s", nome);
						if(!VerificaCitta(grafo, nome)){
							printf("Citta non Esistente\nRiprova\n");
							break;
						}
						nomeFile = pathFileC(nome);
						GrafoCitta = leggiFileAlberghi(GrafoCitta, nomeFile);
						if(GrafoCitta!=NULL)
							stampaAlberghi(GrafoCitta);
						/*Se il file degli alberghi è vuoto GrafoCitta sarà NULL, quindi chiedo di inserire prima degli alberghi.
						GrafoCitta potrebbe avere anche un solo albergo in tal caso chiedo comunque di inserire altri alberghi dato
						che non ci possono essere nodi cappio*/
						if(GrafoCitta==NULL || GrafoCitta->numVertici==1) {
							printf("File %s.txt Vuoto o Incompleto. Inserire prima Alberghi\n", nome);
							break;
						}
						// Prendo Nome Albergo di Partenza
						while(1) {
							printf("Nome Albergo Partenza: ");
							fflush(stdout);
							fflush(stdin);
							scanf("%s", nomePartenza);
							if(!VerificaAlbergo(GrafoCitta, nomePartenza)) {
								printf("Albergo non Trovato\n");
								continue;
							}
							// Prendo il tipo dell albergo di partenza
							verticePartenza = TrovaVertice(GrafoCitta, nomePartenza);
							tipoPartenza = verticePartenza->tipo;
							break;
						}
						// Prendo Nome Albergo di Arrivo
						while(1) {
							printf("Nome Albergo Arrivo: ");
							fflush(stdout);
							fflush(stdin);
							scanf("%s", nomeArrivo);
							if(!VerificaAlbergo(GrafoCitta, nomeArrivo)) {
								printf("Albergo non Trovato\n");
								continue;
							}
							// Prendo il tipo dell albergo di arrivo
							verticeArrivo = TrovaVertice(GrafoCitta, nomeArrivo);
							tipoArrivo = verticeArrivo->tipo;
							break;
						}
						//Prendo il tempo della tratta
						while(1) {
							printf("Tempo Tratta: ");
							fflush(stdout);
							fflush(stdin);
							if(!scanf("%d", &tempo) || tempo<=0) {
								printf("Valore non Valido\n");
								continue;
							}
							break;
						}
						//Aggiungo gli archi
						for(int i=0; i<GrafoCitta->numVertici; i++) {
							if(strcmp(GrafoCitta->adj[i]->albergo, nomePartenza)==0)
								addArcoC(GrafoCitta, i, nomeArrivo, tempo, tipoArrivo);
							if(strcmp(GrafoCitta->adj[i]->albergo, nomeArrivo)==0)
								addArcoC(GrafoCitta, i, nomePartenza, tempo, tipoPartenza);
						}
						scriviFileAlberghi(GrafoCitta, nomeFile);
						break;

					/*** FINE ELIMINA ***/


					/*** USCITA PROGRAMMA ***/
					case 4:
						printf("Arrivederci");
						freeGraphViaggi(grafo);
						FreeC(GrafoCitta);
						free(nomeFile);
						exit(EXIT_SUCCESS);

					default:
						printf("\nValore non Valido");
						continue;
					}
			}
			else{
				confirm = 0;
				printf("\nValore non valido!");
				continue;
			}
		}
	}
	return;
}


GraphCitta* AggiungiAlbergo(GraphCitta* GrafoCitta, GraphViaggi* grafo, FILE* FileCitta, char* nomeFile){
	int tipo;
	char nome[STRING_MAX];
	char choice_yn;

	// Se non sono presenti aeroporti o stazioni vanno aggiunti!
	if(!VerificaFile(FileCitta, nomeFile)){

		printf("Non sono presenti Aeroporti o Stazioni. Inserire una delle due.\n Inserire nome Aeroporto/Stazione: ");

		fflush(stdin);
		fflush(stdout);
		scanf("%s", nome);
		printf("Tipo [Stazione Aereoporto: 1 - Stazione Treno: 2]: ");
		fflush(stdin);
		fflush(stdout);

		do{
		if(scanf("%d", &tipo ) || (tipo != 1 && tipo != 2)){
			InserisciVerticeC(GrafoCitta, nome, tipo);
			break;
		}

		printf("Valore non valido. Riprovare [Stazione Aereoporto: 1 - Stazione Treno: 2]: ");
		continue;

		}while(true);

		do{
			printf("Si vuole inserire anche l'altra (y/n)? Inserire: ");
			fflush(stdin);
			fflush(stdout);
			scanf("%c", &choice_yn);
			choice_yn = tolower(choice_yn);

			switch(choice_yn){
				case 'y':
					printf("Inserire nome: ");
					scanf("%s", nome);
					if(tipo == 1)
						InserisciVerticeC(GrafoCitta, nome, tipo + 1);
					else
						InserisciVerticeC(GrafoCitta, nome, tipo - 1);

					break;

				case 'n':
					break;
				default:
					printf("Valore non valido");
					continue;
			}
			break;
		}while(true);
	}
	else{
		GrafoCitta = leggiFileAlberghi(GrafoCitta, nomeFile);
		printf("Scrivere nome Albergo: ");
		fflush(stdin);
		fflush(stdout);
		scanf("%s", nome);
		InserisciVerticeC(GrafoCitta, nome, 0);
	}

	return GrafoCitta;
}

GraphViaggi* menuAggiungiMeta(GraphViaggi* grafo){
	int tempoAereo, tempoTreno;
	float prezzoAereo = 0, prezzoTreno = 0;
	char nomePartenza[STRING_MAX];
	char nomeArrivo[STRING_MAX];

	do {
		printf("Citta di Partenza: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%s", nomePartenza);
		if(VerificaCitta(grafo, nomePartenza)==-1)
			printf("Citta non Esistente\nRiprova\n");
		else
			break;
	} while(true);

	do {
		printf("Citta di Arrivo: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%s", nomeArrivo);
		if(VerificaCitta(grafo, nomeArrivo)==-1)
			printf("Citta non Esistente\nRiprova\n");
		else
			break;
	} while(true);

	do {
		printf("Tempo Aereo(0 se non presente collegamento aereo): ");
		fflush(stdout);
		fflush(stdin);

		if(!scanf("%d", &tempoAereo) || tempoAereo<0) {
			printf("Valore non Valido\n");
			continue;
		}
		if(tempoAereo!=0) {
			do {
				printf("Prezzo Aereo(>0): ");
				fflush(stdout);
				fflush(stdin);

				if(!scanf("%f", &prezzoAereo) || prezzoAereo<=0) {
					printf("Valore non Valido\n");
					continue;
				}
				break;
			} while(true);
		}
		break;
	}while(true);
	do {
		printf("Tempo Treno(0 se non presente collegamento stazione): ");
		fflush(stdout);
		fflush(stdin);

		if(!scanf("%d", &tempoTreno) || tempoTreno<0) {
			printf("Valore non Valido\n");
			continue;
		}
		if(tempoTreno!=0) {
			do {
				printf("Prezzo Treno(>0): ");
				fflush(stdout);
				fflush(stdin);

				if(!scanf("%f", &prezzoTreno) || prezzoTreno<=0) {
					printf("Valore non Valido\n");
					continue;
				}
				break;
			} while(true);
		}
		break;
	}while(true);
	if(tempoAereo==0 && tempoTreno==0) {
		printf("Collegamento Ignorato\n");
		return grafo;
	}
	for(int i=0; i<grafo->numVertici; i++)
		if(strcmp(nomePartenza, grafo->adj[i]->citta)==0) {
			addArco(grafo, i, nomeArrivo, prezzoAereo, prezzoTreno, tempoAereo, tempoTreno);
			break;
		}
	for(int i=0; i<grafo->numVertici; i++)
		if(strcmp(nomeArrivo, grafo->adj[i]->citta)==0) {
			addArco(grafo, i, nomePartenza, prezzoAereo, prezzoTreno, tempoAereo, tempoTreno);
			break;
		}

	return grafo;
}
