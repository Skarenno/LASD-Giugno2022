/*
 * UserProgram.c
 *
 *  Created on: 27 mag 2022
 */

#include "AdminProgram.h"

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
	while (confirm!=5) {
		printf("\nImmettere azione da eseguire (1. Aggiungi Meta - 2. Elimina Meta - 3. Modifica Meta - 4. Aggiungi Arco - 5. Chiudi Applicativo):");
		if(scanf("%d",&confirm)) {
			switch(confirm) {
				case 1:
					printf("Nome Citta: ");
					scanf("%s", nome);
					InserisciVertice(grafo, nome);
					break;
				case 2:

				case 5:
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
