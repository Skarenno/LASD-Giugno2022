/*
 * UserProgram.c
 *
 *  Created on: 26 mag 2022
 */

#include "UserProgram.h"

void userDashboard(Utente* user){
	int AT=0;
	int PT=0;
	int confirm=0;
	float price=0.0;
	while (!confirm) {
	while (!confirm) {
	printf("\n");
	printf("Bentornato, %s\n",user->nome);
	printf("Il tuo saldo: %.2f euro\n",user->saldo);

	printf("Al momento le mete disponibili sono: \n");
	///TODO: stampa lista mete
	printf("\n");
	printf("Inserisci la città di partenza \n");

	printf("Inserisci la città di arrivo \n");

	printf("Inserisci il tipo di trasporto desiderato, 0 per Aereo, 1 per Treno\n");
	scanf("%d",&AT);
	printf("Inserisci 0 per il viaggio più economico, 1 per la tratta più rapida\n");
	scanf("%d",&PT);

	///TODO: Dijkstra(grafoV,AT,PT)
	//Lista di attesa se nessun risultato

	printf("Il prezzo di questo viaggio è di <prezzo da Dijkstra> %.2f, vuoi prenotarlo?\n",price);
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
