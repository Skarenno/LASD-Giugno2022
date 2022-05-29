/*
 * UserProgram.c
 *
 *  Created on: 27 mag 2022
 */

#include "AdminProgram.h"

void adminDashboard(Admin* admin, GraphViaggi* grafo){
	int confirm = 0, tempoAereo, tempoTreno;
	float prezzoAereo = 0, prezzoTreno = 0;
	char nome[STRING_MAX];
	char nomePartenza[STRING_MAX], nomeArrivo[STRING_MAX];
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
		printf("\nImmettere azione da eseguire (1. Aggiungi Meta - 2. Elimina Meta - 3. Aggiungi Arco - 4. Chiudi Applicativo):");
		if(scanf("%d",&confirm)) {
			switch(confirm) {
				case 1:
					printf("Nome Citta: ");
					scanf("%s", nome);
					InserisciVertice(grafo, nome);
					break;
				case 2:
					StampaMete(grafo);
					printf("Meta da Cancellare: ");
					scanf("%s", nome);
					if(!VerificaCitta(grafo, nome))
						printf("Citta non Esistente\nRiprova\n");
					rimuoviVerticeV(grafo, nome);
					remove(pathFileC(nome));
					break;
				case 3:
					stampaGrafo(grafo);
					do {
						printf("Citta di Partenza: ");
						scanf("%s", nomePartenza);
						if(!VerificaCitta(grafo, nomePartenza))
							printf("Citta non Esistente\nRiprova\n");
						else
							break;
					} while(true);
					do {
						printf("Citta di Partenza: ");
						scanf("%s", nomeArrivo);
						if(!VerificaCitta(grafo, nomeArrivo))
							printf("Citta non Esistente\nRiprova\n");
						else
							break;
					} while(true);
					do {
						printf("Tempo Aereo(0 se non presente collegamento aereo): ");
						if(!scanf("%d", &tempoAereo) || tempoAereo<0) {
							printf("Valore non Valido\n");
							continue;
						}
						if(tempoAereo!=0) {
							do {
								printf("Prezzo Aereo(>0): ");
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
						if(!scanf("%d", &tempoTreno) || tempoTreno<0) {
							printf("Valore non Valido\n");
							continue;
						}
						if(tempoTreno!=0) {
							do {
								printf("Prezzo Treno(>0): ");
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
					scriviFileViaggi(grafo);
					break;
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
