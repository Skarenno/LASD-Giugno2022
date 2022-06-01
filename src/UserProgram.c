/*
 * UserProgram.c
 *
 *  Created on: 26 mag 2022
 */

#include "UserProgram.h"
#include "Dijkstra.h"

void userDashboard(Utente* user, GraphViaggi* GrafoViaggi){
	int AT=0;	// Aereo/Treno
	int PT=0;	// Prezzo migliore/Tratta migliore
	float distance=0.0;

	char partenza[STRING_MAX];
	char arrivo[STRING_MAX];

	int key_partenza, key_arrivo;
	int tipoDijkstra;
	int confirm=0;
	float price=0.0;


	printf("\n");
	printf("Bentornato, %s\n",user->nome);
	printf("Il tuo saldo: %.2f euro\n",user->saldo);

	while (!confirm) {

		while (!confirm) {
			printf("Al momento le mete disponibili sono: \n");
			StampaMete(GrafoViaggi);


			// LETTURA PARTENZA
			do{
				printf("Inserisci la citt� di partenza: ");
				fflush(stdout);
				fflush(stdin);
				scanf("%s", partenza);
				key_partenza = VerificaCitta(GrafoViaggi, partenza);
				if(key_partenza != -1)
					break;
				else
					printf("---Nome citt� non valido... riprovare.\n");
			}while(true);

			// LETTURA ARRIVO
			do{
				printf("Inserisci la citt�di arrivo: ");
				fflush(stdout);
				fflush(stdin);
				scanf("%s", arrivo);
				key_arrivo = VerificaCitta(GrafoViaggi, arrivo);
				if(key_arrivo != -1)
					break;
				else
					printf("---Nome citt� non valido... riprovare.\n");
			}while(true);

			do{
				printf("*************\nSi � selezionato il viaggio %s -> %s\n", partenza, arrivo);
				printf("Inserisci il tipo di trasporto desiderato (0. Aereo - 1. Treno): ");
				fflush(stdout);
				fflush(stdin);

				if(!scanf("%d",&AT) || (AT != 1 && AT != 0)){
					printf("Valore non valido");
					continue;
				}

				printf("Inserisci 0 per il viaggio più economico, 1 per la tratta più rapida: ");

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

			price = dijkstra(GrafoViaggi, key_partenza, key_arrivo, tipoDijkstra, &distance);

			if(price == INT_MAX){
				printf("Tratta non disponibile");
				continue;
			}
			printf("La durata di questo viaggio � di %.0f minuti\n",distance);
			printf("Il prezzo di questo viaggio � di %.2f, vuoi prenotarlo?\n",price);
//			printf("1: Conferma. 0: Annulla e torna al menu principale.\n");
//			scanf("%d",&confirm);
		}

//		user->saldo=user->saldo-price;
//		printf("Complimenti, hai prenotato il tuo viaggio!\n");
//		printf("Nella tua destinazione sono disponibili i seguenti alberghi: \n");
//		///TODO: stampa lista alberghi
//		printf("Pensi di soggiornare presso uno di questi alberghi? 1 per continuare, 0 per tornare al menu\n");
//		scanf("%d",&confirm);
//		if (confirm){
//			///TODO: Dijkstra su grafo alberghi e stampa tempo
//		}
//
//		printf("Uscire dall'applicativo? (1:Si, 0:No)\n");
//		scanf("%d",&confirm);
	}

}
