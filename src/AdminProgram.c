/*
 * UserProgram.c
 *
 *  Created on: 27 mag 2022
 */

#include "AdminProgram.h"

void adminDashboard(Admin* admin, GraphViaggi* grafo){
	int confirm = 0, check, confirm1 = 0;
	ListaAttesa *lista = NULL;
	lista = leggiAttesa(lista);
	if(lista==NULL)
		confirm1 = 1;
	while (!confirm) {
		while (!confirm1) {
			printf("Bentornato, %s\n",admin->nome);
			printf("Al momento le mete inserite sono:\n");
			stampaGrafo(grafo);
			printf("\n");
			printf("Mete da collegare\n");
			stampaAttesa(lista);
			lista = aggiungiMetaAttesa(grafo, lista);
			//TODO funzione per aggiungere alberghi alla meta appena collegata
			if(lista==NULL) {
				printf("Complimenti, hai collegato tutte le mete in attesa!\n");
				confirm1 = 1; //Tutte le mete collegate esco dal while
				//TODO Aggiornare i file
				scriviAttesa(lista); //Scrive la nuova lista di attesa
			} else {
				char choice;
				do {
					printf("Vuoi collegare le restanti Mete?(y/n)\n");
					scanf("%c", &choice);
					choice = tolower(choice);
					switch(choice) {
						case 'y':
							printf("Continuiamo...\n");
							confirm1 = 0;
							break;
						case 'n':
							printf("Ok\n");
							confirm1 = 1;
							//TODO Aggiornare i file
							scriviAttesa(lista); //Scrive la nuova lista di attesa
							break;
						default:
							printf("Valore non Valido\n");
					}
				} while(choice!='n');
			}
		}
		printf("\nImmettere azione da eseguire (1. Aggiungi Meta - 2. Elimina Meta - 3. Modifica Meta - 4. Chiudi Applicativo):");
		check = scanf("%d",&confirm);
		if(check==1) {
			switch(confirm) {
				//case 1:

			}
		} else{
			confirm = 0;
        	printf("Valore non valido\n");
        }
	}
	return;
}
