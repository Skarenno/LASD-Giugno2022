/*
 * UserProgram.c
 *
 *  Created on: 26 mag 2022
 */

#include "UserProgram.h"


void userDashboard(Utente* user, GraphViaggi* GrafoViaggi){
	int AT=0;	// Aereo/Treno
	int PT=0;	// Prezzo migliore/Tratta migliore

	char partenza[STRING_MAX];
	char arrivo[STRING_MAX];

	int confirm=0;
	float price=0.0;

	while (!confirm) {

		while (!confirm) {
			printf("\n");
			printf("Bentornato, %s\n",user->nome);
			printf("Il tuo saldo: %.2f euro\n",user->saldo);

			printf("Al momento le mete disponibili sono: \n");
			StampaMete(GrafoViaggi);


			// LETTURA PARTENZA
			do{
				printf("Inserisci la citt‡ di partenza: ");
				fflush(stdout);
				fflush(stdin);
				scanf("%s", partenza);
				if(VerificaCitta(GrafoViaggi, partenza) == 1)
					break;
				else
					printf("---Nome citt‡ non valido... riprovare.\n");
			}while(true);

			// LETTURA ARRIVO
			do{
				printf("Inserisci la citt‡†di arrivo: ");
				fflush(stdout);
				fflush(stdin);
				scanf("%s", arrivo);
				if(VerificaCitta(GrafoViaggi, arrivo) == 1)
					break;
				else
					printf("---Nome citt‡ non valido... riprovare.\n");
			}while(true);

			printf("*************\nSi Ë selezionato il viaggio %s -> %s\n", partenza, arrivo);
			printf("Inserisci il tipo di trasporto desiderato (1. Aereo - 2. Treno): ");
			fflush(stdout);
			fflush(stdin);
			scanf("%d",&AT);
			printf("Inserisci 0 per il viaggio pi√π economico, 1 per la tratta pi√π rapida: ");
			scanf("%d",&PT);

			///TODO: Dijkstra(grafoV,AT,PT)
			//Lista di attesa se nessun risultato

			printf("Il prezzo di questo viaggio √® di <prezzo da Dijkstra> %.2f, vuoi prenotarlo?\n",price);
			printf("1: Conferma. 0: Annulla e torna al menu principale.\n");
			scanf("%d",&confirm);
		}
		user->saldo=user->saldo-price;
		printf("Complimenti, hai prenotato il tuo viaggio!\n");
		printf("Nella tua destinazione sono disponibili i seguenti alberghi: \n");
		///TODO: stampa lista alberghi
		printf("Pensi di soggiornare presso uno di questi alberghi? 1 per continuare, 0 per tornare al menu\n");
		scanf("%d",&confirm);
		if (confirm){
			///TODO: Dijkstra su grafo alberghi e stampa tempo
		}

		printf("Uscire dall'applicativo? (1:Si, 0:No)\n");
		scanf("%d",&confirm);
	}

}


void StampaMete (GraphViaggi* GrafoViaggi){
	for (int i = 0; i < GrafoViaggi->numVertici; i++){
		printf("%s ", GrafoViaggi->adj[i]->citta);
		if(i < GrafoViaggi->numVertici - 1)
			printf("- ");
	}

	printf("\n");
}

int VerificaCitta(GraphViaggi* GrafoViaggi, char citta[]){
	for(int i = 0; i < GrafoViaggi->numVertici; i++){
		if(strcmp(GrafoViaggi->adj[i]->citta, citta) == 0){
			return 1;
		}
	}

	return 0;
}
