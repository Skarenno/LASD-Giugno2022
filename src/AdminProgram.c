/*
 * UserProgram.c
 *
 *  Created on: 27 mag 2022
 */

#include "AdminProgram.h"
#ifndef STD_HEAD
#define STD_HEAD "standard_header.h"
#include STD_HEAD
#endif

void adminDashboard(Admin* admin, GraphViaggi* grafo){
	int confirm = 0;
	char nome[STRING_MAX];

	ListaAttesa *lista = NULL;
	lista = leggiAttesa(lista);
	printf("Bentornato, %s\n",admin->nome);
	printf("Al momento le mete inserite sono:\n");
	stampaGrafo(grafo);
	printf("\n");
	if(lista!=NULL) {
		printf("Mete da collegare\n");
		stampaAttesa(lista);
	}
	while (confirm!=4) {
		printf("\nImmettere azione da eseguire (1. Aggiungi Meta - 2. Elimina Meta - 3. Aggiungi Arco - 4. Menu precedente):");
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
					InserisciVertice(grafo, nome);
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
					rimuoviVerticeV(grafo, nome);
					remove(pathFileC(nome));
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
					exit(1);
				default: printf("Valore non Valido\nRiprovare\n");
			}
		} else{
			confirm = 0;
        	printf("Tipo non Valido\n");
        }
	}
	return;
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
		if(!VerificaCitta(grafo, nomePartenza))
			printf("Citta non Esistente\nRiprova\n");
		else
			break;
	} while(true);

	do {
		printf("Citta di Arrivo: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%s", nomeArrivo);
		if(!VerificaCitta(grafo, nomeArrivo))
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
