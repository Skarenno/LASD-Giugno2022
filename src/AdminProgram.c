
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
		printf("\nSi vuole lavorare su citta (0) o alberghi(1): ");
		fflush(stdout);
		fflush(stdin);

		if(scanf("%hu", &choice))
			break;

		printf("\n Valore non valido");
	}while(true);


	/**** MENU LAVORO SU CITTA ****/
	if(!choice){
		confirm = 0;
		while (confirm!=5) {
			printf("\nImmettere azione da eseguire (1. Aggiungi Meta - 2. Elimina Meta - 3. Aggiungi/Aggiorna Tratta - 4. Rimuovi Tratta - 5. Chiudi programma): ");
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
						if(VerificaCitta(grafo, nome)==-1){
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
						if(VerificaCitta(grafo, nome)==-1){
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
					// Rimuovi Arco
					case 4:
						stampaGrafo(grafo);
						grafo = menuEliminaArco(grafo);
						scriviFileViaggi(grafo);
						break;

					// Tornare indietro
					case 5:
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
			printf("\nImmettere azione da eseguire (1. Aggiungi Alberghi - 2. Elimina Alberghi - 3. Aggiungi Percorso - 4. Chiudi programma): ");
			fflush(stdout);
			fflush(stdin);
			if(scanf("%d", &confirm)){
				switch(confirm){
					/*** AGGIUNGI ALBERGO ***/
					case 1:
						StampaMete(grafo);
						while(true){
							printf("Scegli la citt? a cui vuoi aggiungere Alberghi: ");
							fflush(stdin);
							fflush(stdout);
							scanf("%s", nome);

							if(VerificaCitta(grafo, nome)==-1){
								printf("Citta non Esistente\nRiprova\n");
								continue;
							}
							break;
						}

						FileCitta = fopen(nomeFile = pathFileC(nome), "r");
						GrafoCitta = AggiungiAlbergo(GrafoCitta, grafo, FileCitta, nomeFile);
						ScriviChiaviAlberghi(GrafoCitta);
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
						if(VerificaCitta(grafo, nome)==-1){
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
							if(VerificaAlbergo(GrafoCitta, nome) == -1){
								printf("Albergo non esistente");
								continue;
							}

							Vertice = TrovaVertice(GrafoCitta, nome);
							if(Vertice->tipo != 0){
								printf("\n***Si ? selezionato un Aeroporto o una Stazione. Impossibile eliminare.***\n");
								break;
							}
							if(Vertice != NULL){
								GrafoCitta = rimuoviVerticeC(GrafoCitta, Vertice);
								ScriviChiaviAlberghi(GrafoCitta);
								scriviFileAlberghi(GrafoCitta, nomeFile);
							}
							break;
						}while(true);

						break;
					/*** FINE ELIMINA ***/

					/*** AGGIUNGI ARCO ***/
					case 3:
						printf("Mete Presenti\n");
						StampaMete(grafo);
						printf("Su quale Meta si intende Lavorare? Immettere: ");
						fflush(stdin);
						fflush(stdout);
						scanf("%s", nome);
						if(VerificaCitta(grafo, nome)==-1){
							printf("Citta non Esistente\nRiprova\n");
							break;
						}
						nomeFile = pathFileC(nome);
						GrafoCitta = leggiFileAlberghi(GrafoCitta, nomeFile);
						if(GrafoCitta!=NULL)
							stampaAlberghiAlt(GrafoCitta);
						/*Se il file degli alberghi ? vuoto GrafoCitta sar? NULL, quindi chiedo di inserire prima degli alberghi.
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
							if(VerificaAlbergo(GrafoCitta, nomePartenza)==-1) {
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
							if(VerificaAlbergo(GrafoCitta, nomeArrivo)==-1) {
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
						ScriviChiaviAlberghi(GrafoCitta);
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
	int tempoAereo = 0, tempoTreno = 0;
	float prezzoAereo = 0, prezzoTreno = 0;
	char nomePartenza[STRING_MAX];
	char nomeArrivo[STRING_MAX];
	ListaAttesa *Attesa = NULL;
	Attesa = leggiAttesa(Attesa);

	do {
		printf("Citta di Partenza ('Annulla' per uscire): ");
		fflush(stdout);
		fflush(stdin);
		scanf("%s", nomePartenza);
		if(strcmp(nomePartenza, "Annulla") == 0)
			return grafo;
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
	FILE *controlloArrivo = fopen(pathFileC(nomeArrivo), "r");
	if(controlloArrivo==NULL) {
		printf("Impossibile Aprire il File: %s.txt\n", nomeArrivo);
		return grafo;
	}
	fclose(controlloArrivo);
	GraphCitta *GrafoCitta = AllocaGrafoC();
	GrafoCitta = leggiFileAlberghi(GrafoCitta, pathFileC(nomeArrivo));

	FILE *controlloPartenza = fopen(pathFileC(nomePartenza), "r");
	if(controlloArrivo==NULL) {
		printf("Impossibile Aprire il File: %s.txt\n", nomePartenza);
		return grafo;
	}
	fclose(controlloPartenza);
	GraphCitta *GrafoCittaPartenza = AllocaGrafoC();
	GrafoCittaPartenza = leggiFileAlberghi(GrafoCittaPartenza, pathFileC(nomePartenza));
	if(VerificaTipo(GrafoCitta, 1)!=-1 && VerificaTipo(GrafoCittaPartenza, 1)!=-1) { //Svolto solo se presente aeroporto nella citt? di arrivo e partenza
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
	} else {
		printf("Aereoporto non disponibile nella citt? di arrivo o di partenza\n");
	}
	if(VerificaTipo(GrafoCitta, 2)!=-1 && VerificaTipo(GrafoCittaPartenza, 2)!=-1) { //Svolto solo se presente stazione treno nella citt? di arrivo e partenza
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
	} else {
		printf("Stazione del Treno non disponibile nella citt? di arrivo o di partenza\n");
	}
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
	ListaAttesa *tmp = Attesa;
	ListaAttesa *succ = NULL;
	int indicePartenza, indiceArrivo;
	float distanceReturned, dijkstraReturn;
	while(tmp!=NULL) { //Controllo su lista di attesa
		indicePartenza = VerificaCitta(grafo, tmp->partenza);
		indiceArrivo = VerificaCitta(grafo, tmp->arrivo);
		if(indicePartenza==-1) {
			succ = tmp->next;
			Attesa = rimuoviNodoAttesa(Attesa, tmp);
			tmp = succ;
			continue;
		} else if(indiceArrivo==-1) {
			succ = tmp->next;
			Attesa = rimuoviNodoAttesa(Attesa, tmp);
			fflush(stdout);
			tmp = succ;
			continue;
		}
		dijkstraReturn = DijkstraViaggiNoPrint(grafo, indicePartenza, indiceArrivo, tmp->tipo+1, &distanceReturned);
		if(dijkstraReturn<INT_MAX) {
			succ = tmp->next;
			if(tmp->tipo==0)
				printf("Partenza: %s  Arrivo: %s  Tipo Viaggio: %s   COLLEGATO [RIMOSSO DA LISTA D'ATTESA]\n", tmp->partenza, tmp->arrivo, "Aereo");
			else
				printf("Partenza: %s  Arrivo: %s  Tipo Viaggio: %s   COLLEGATO [RIMOSSO DA LISTA D'ATTESA]\n", tmp->partenza, tmp->arrivo, "Treno");
			Attesa = rimuoviNodoAttesa(Attesa, tmp);
			tmp = succ;
			continue;
		} else
			tmp = tmp->next;
	}
	tmp = Attesa;
	scriviAttesa(Attesa);
	return grafo;
}

GraphViaggi *menuEliminaArco(GraphViaggi *grafo) {
	char vertice1[STRING_MAX];
	char vertice2[STRING_MAX];
	int choice;
	while(true) {
		printf("Inserire Vertice di Partenza('Annulla' per uscire): ");
		fflush(stdout);
		fflush(stdin);
		scanf("%s", vertice1);
		if(strcmp("Annulla", vertice1)==0)
			return grafo;
		if(VerificaCitta(grafo, vertice1)==-1) {
			printf("Citta non Trovata!\n");
			continue;
		}
		break;
	}
	while(true) {
		printf("Inserire Vertice di Arrivo('annulla' per uscire): ");
		fflush(stdout);
		fflush(stdin);
		scanf("%s", vertice2);
		if(strcmp("annulla", vertice2)==0)
			return grafo;
		if(VerificaCitta(grafo, vertice2)==-1) {
			printf("Citta non Trovata!\n");
			continue;
		}
		break;
	}
	while(true) {
		printf("Elimina 1. Aereo - 2. Treno - 3. Entrambi. Scegli: ");
		fflush(stdout);
		fflush(stdin);
		if(!scanf("%d", &choice) || (choice<1 && choice>3)) {
			printf("Valore non Valido\n");
			continue;
		}
		switch(choice) {
			case 1:
				printf("Rimuovo collegamento\n");
				grafo = updateArchi(grafo, vertice1, vertice2, choice);
				break;
			case 2:
				printf("Rimuovo collegamento\n");
				grafo = updateArchi(grafo, vertice1, vertice2, choice);
				break;
			case 3:
				printf("Rimuovo Tratta\n");
				grafo = rimuoviArcoV(grafo, vertice1, vertice2);
				grafo = rimuoviArcoV(grafo, vertice2, vertice1);
				break;
		}
		break;
	}
	return grafo;
}
