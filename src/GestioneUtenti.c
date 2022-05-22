#include "GestioneUtenti.h"


Utente* InizializzaNodoUtente(Utente* Nodo){
    Nodo = (Utente*)malloc(sizeof(Utente));
    Nodo->next = NULL;

    return Nodo;
}


void RiscriviFileUtenti(FILE* FileUtenti, Utente* ListaUtenti){
    Utente* Cursor = ListaUtenti;

    while(Cursor != NULL){
        fprintf(FileUtenti, "%s %s %.2f", Cursor->nome, Cursor->password, Cursor->saldo);
        Cursor = Cursor->next;
    }
}

Utente* LeggiFileUtenti (FILE* file, Utente* ListaUtenti){

	/***
	 *
	 *
	 * AGGIUSTARE FILE NON APERTO
	 *
	 *
	 */


    if(ListaUtenti == NULL)
        ListaUtenti = InizializzaNodoUtente(ListaUtenti);

    if(!feof(file)){
        fscanf(file, "%s %s %f", ListaUtenti->nome, ListaUtenti->password, &ListaUtenti->saldo);
        ListaUtenti->next = LeggiFileUtenti(file, ListaUtenti->next);
    }
    else{
        free(ListaUtenti);
        return NULL;
    }

    return ListaUtenti;
}


Utente* SchermataIniziale (Utente* ListaUtenti){

	/***
	 *
	 *
	 * AGGIUSTARE FILE NON APERTO
	 *
	 *
	 */


    int n;
    int check;
    bool accesso = false;

    Utente* AccessoUtente = NULL;
    FILE* FileUtenti = fopen(U_FILE, "r+");

    ListaUtenti = LeggiFileUtenti(FileUtenti, ListaUtenti);

    StampaListaUtenti(ListaUtenti);

	printf("***************\n **Benvenuto** \n***************\n\n");
    sleep(1);

    while(!accesso){

        // ESCO DAL WHILE SOLO QUANDO L'ACCESSO E AVVENUTO CORRETTAMENTE.
        printf("\nImmettere azione da eseguire (1. Accesso - 2. Registrazione - 3. Chiudi Applicativo): ");
        fflush(stdin);
        check = scanf("%d", &n);

        if(check == 1){
            switch(n){
                case 1:
                    // ACCESSO
                    accesso = true;
                    break;

                case 2:
                    // REGISTRAZIONE
                    continue;

                case 3:
                    // CHIUSURA
                    printf("\nArrivederci!\n************");
                    sleep(1);
                    exit(EXIT_SUCCESS);
                default:
                    printf("\n---Non valido!---\n");
                    break;
            }
        }
        else{
            printf("\nERROR: NOT A NUMBER\n");
        }

    }

    return AccessoUtente; // PER ORA PER NON FAR APPARIRE WARNING
}


/****************************************** TO DO ****************************************** */

// Funzione per l'accesso
Utente* AccessoUtente (Utente* ListaUtenti){
    return NULL;
}

// Funzione per la registrazione
void RegistraUtente(Utente* ListaUtenti){
    return;
}



/****************************************** TEMP PER DEBUGGING ****************************************** */

void StampaListaUtenti(Utente* Lista){
    printf("%s %s %.2f\n", Lista->nome, Lista->password, Lista->saldo);

    if(Lista->next != NULL)
        StampaListaUtenti(Lista->next);

    return;
}
