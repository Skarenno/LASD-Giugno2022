/*
 * UserProgram.c
 *
 *  Created on: 26 mag 2022
 */

#include "UserProgram.h"
#include "Dijkstra.h"

void userDashboard(Utente* ListaUtenti, Utente* user, GraphViaggi* GrafoViaggi){
	int prenotato = 0, choice, tipoViaggio;
	char yn, *nomeArrivo = NULL;
	float nuovoSaldo = 0.0;
	nomeArrivo = (char*)malloc(sizeof(char)*STRING_MAX);
	printf("\n");
	printf("Bentornato, %s\n",user->nome);
	printf("Il tuo saldo: %.2f euro\n",user->saldo);

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
				prenotato = EffettuaPrenotazione(user, GrafoViaggi, nomeArrivo, &tipoViaggio);
				if(prenotato==0) {
					printf("Viaggio Annullato\n");
					break;
				}
				printf("Viaggio Prenotato. Si vuole scegliere un albergo?(y/n)\n");
				scanf("%c", &yn);
				yn = tolower(yn);
				switch(yn) {
					case 'y':
						//PercorsoAlbergo(tipoViaggio, nomeArrivo);
						break;
				}

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

int EffettuaPrenotazione(Utente* user, GraphViaggi* GrafoViaggi, char *nomeArrivo, int *tipoViaggio) {
	int AT=0;	// Aereo/Treno
	int PT=0;	// Prezzo migliore/Tratta migliore
	float distance=0.0;

	char partenza[STRING_MAX];
	char arrivo[STRING_MAX];

	int confirm = 0;
	int key_partenza, key_arrivo;
	int tipoDijkstra;
	float price=0.0;

	printf("Al momento le mete disponibili sono: \n");
	StampaMete(GrafoViaggi);

	// LETTURA PARTENZA
	do{
		printf("Inserisci la città di partenza: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%s", partenza);
		key_partenza = VerificaCitta(GrafoViaggi, partenza);
		if(key_partenza != -1)
			break;
		else
			printf("---Nome città non valido... riprovare.\n");
	}while(true);

	// LETTURA ARRIVO
	do{
		printf("Inserisci la città di arrivo: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%s", arrivo);
		key_arrivo = VerificaCitta(GrafoViaggi, arrivo);
		if(key_arrivo != -1)
			break;
		else
			printf("---Nome città non valido... riprovare.\n");
	}while(true);

	do{
		printf("*************\nSi è selezionato il viaggio %s -> %s\n", partenza, arrivo);
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
		return 0;
	}
	printf("La durata di questo viaggio è di %.0f minuti\n", distance);
	printf("Il prezzo di questo viaggio è di %.2f, vuoi prenotarlo?\n", price);
	while(true) {
		printf("1: Conferma. 0: Annulla e torna al menu principale.\n");
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
			return 1;
		} else
			printf("Saldo non sufficiente. Devi caricare almeno: %.2f\n", price-user->saldo);
	} else
		printf("Torno al Menu Precedente\n");
	return 0;
}

/*PercorsoAlbergo(tipoViaggio, nomeArrivo) {

}*/
