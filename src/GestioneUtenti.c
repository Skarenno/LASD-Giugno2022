#include "standard_header.h"
#include "GestioneUtenti.h"

/********************** FUNZIONI PER LA LISTA UTENTI **********************/
/**************************************************************************/



Utente* InizializzaNodoUtente(Utente* Nodo){
    Nodo = (Utente*)malloc(sizeof(Utente));
    Nodo->nome[0] = '\0';			// Inizializzo le stringhe altrimenti ho errori nella scrittura
    Nodo->password[0] = '\0';		// Inizializzo le stringhe altrimenti ho errori nella scrittura
    Nodo->next = NULL;

    return Nodo;
}


// Aggiunta in coda nella lista
Utente* AggiungiListaUtenti(Utente* ListaUtenti, char* nome, char* password){

	Utente* New = NULL;
	New = InizializzaNodoUtente(New);

	Utente* Cur = ListaUtenti;

	strcpy(New->nome, nome);
	strcpy(New->password, password);

	if(ListaUtenti == NULL)
		ListaUtenti = New;
	else{
		while(Cur->next != NULL)
			Cur = Cur->next;

		Cur->next = New;
	}
	return ListaUtenti;
}


// Trova un Utente nella lista, restituisce NULL se l'utente non viene trovato (Ricorsiva)
Utente* TrovaUtente(char *nomeInserito, Utente* ListaUtenti){
	if(ListaUtenti == NULL){
		return NULL;
	}

	if(strcmp(nomeInserito, ListaUtenti->nome) == 0){
		return ListaUtenti;
	}

	return TrovaUtente(nomeInserito, ListaUtenti->next);
}


// Stampa a schermo la lista Utenti
void StampaListaUtenti(Utente* Lista){
    printf("%s %s %.2f\n", Lista->nome, Lista->password, Lista->saldo);

    if(Lista->next != NULL)
        StampaListaUtenti(Lista->next);
    return;
}



/**************************************************************************/
/**************************************************************************/




/*************** FUNZIONI PER GESTIONE FILE UTENTI ************************/
/**************************************************************************/

// Scrivo la lista locale dal file Utenti (Ricorsiva)
Utente* LeggiFileUtenti (FILE* file, Utente* ListaUtenti){

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

// Riscrivo il file a partire dall'attuale lista degli Utenti
void RiscriviFileUtenti(Utente* ListaUtenti){
	FILE* FileUtenti = fopen (U_FILE, "w+");
    Utente* Cursor = ListaUtenti;

    while(Cursor != NULL){
        fprintf(FileUtenti, "%s %s %.2f", Cursor->nome, Cursor->password, Cursor->saldo);
        Cursor = Cursor->next;
        if(Cursor)
        	fprintf(FileUtenti, "\n");
    }
}

/**************************************************************************/
/**************************************************************************/




/*********** FUNZIONI GENERALI PER MENU, ACCESSO E REGISTRAZIONE ***********/
/**************************************************************************/




// Funzione per selezione admin
unsigned short int SelezioneAccesso(){
	unsigned short int tipo_utente;

	printf("***************\n **Benvenuto** \n***************\n\n");
	printf("Si vuole accedere come utente o amministratore?");

	while(true){
		printf(" (1: Utente - 2: Amministratore): ");
		fflush(stdout);
		fflush(stdin);
		if(scanf("%hu", &tipo_utente) == 1){
			if(tipo_utente != 1 && tipo_utente != 2){
				printf("Scelta non valida\nRiprovare");
				continue;
			}
			else
				return tipo_utente;;
		}
		else{
			printf("Tipo non valido\nRiprovare");
		}
	}
}

// Schermata Iniziale. Ritorna l'utente di cui si ï¿½ effettuato l'accesso
Utente* SchermataIniziale (Utente* ListaUtenti){

	// INIZIALIZZO VARIABILI LOCALI
	Utente* UtenteAttuale = NULL;
    int scelta, check = 0;
    bool accesso = false;


    // Apro e leggo il file utenti
    FILE* FileUtenti = fopen(U_FILE, "r+");
    if(FileUtenti == NULL){
    	printf("ERRORE DATABASE UTENTI");
    	return NULL;
    }
    ListaUtenti = LeggiFileUtenti(FileUtenti, ListaUtenti);
    fclose(FileUtenti);
    // Chiusura file utenti

    printf("\n************************************\n");
    printf("Si è scelto di entrare come Utente!");
    printf("\n************************************\n");

	sleep(1);
    do{
        // ESCO DAL WHILE (E PASSO ALLA SCHERMATA SUCCESSIVA) SOLO QUANDO L'ACCESSO ï¿½ AVVENUTO CORRETTAMENTE.
        printf("\nImmettere azione da eseguire (1. Accesso - 2. Registrazione - 3. Chiudi Applicativo):");
        fflush(stdout);
        fflush(stdin);
        check = scanf("%d", &scelta);

        if(check == 1){
			switch(scelta){

				// Accesso
				case 1:
					UtenteAttuale = AccessoUtente(ListaUtenti);
					if(UtenteAttuale != NULL)
						accesso = true;
					break;

				// Registrazione
				case 2:
					ListaUtenti = RegistraUtente(ListaUtenti);
					RiscriviFileUtenti(ListaUtenti); // Aggiorno il database quando registro un nuovo utente
					StampaListaUtenti(ListaUtenti);	// Per Debug stampo a schermo la lista dopo aver aggiunto il nodo del nuovo utente in coda
					continue;

				// Chiusura programma
				case 3:
					// CHIUSURA
					printf("\nArrivederci!\n************");
					sleep(1);
					exit(EXIT_SUCCESS);


				default:
					printf("\n---Non valido!---\n");
					break;
			}
        }else{
        	printf("Valore non valido\n");
        }
    }while(accesso == false);

    // Ritorno il nodo utente di cui ho effettuato l'accesso
    return UtenteAttuale;
}


// Funzione per l'accesso
Utente* AccessoUtente (Utente* ListaUtenti){
    char n_utente[STRING_MAX];
    char password[STRING_MAX];
    bool quit_login = false;
    char yes_no;

    printf("\nInserire nome utente: ");
    fflush(stdout);
    scanf("%s", n_utente);

    Utente* Utente = TrovaUtente(n_utente, ListaUtenti);

    /** DUE CASI **/

    // 1. L'utente non ï¿½ presente nel Database e si richiede se si vuole registrarsi
    if(Utente == NULL){
    	printf("\nUtente non trovato... desidera registrarsi (y/n)? ");
    	fflush(stdout);
    	fflush(stdin);
    	scanf("%c", &yes_no);

    	// Il while serve per il default nello switch
    	while(1){
			switch(yes_no){

				// Se si, procedo alla registrazione
				case 'y':
					RegistraUtente(ListaUtenti);
					RiscriviFileUtenti(ListaUtenti);
					break;

				// Se no, ritorno al menu iniziale
				case 'n':
					Utente = NULL;
					printf("*****************\nRITORNO AL MENU INIZIALE\n");
					return Utente;

				// Richiesta non valida
				default:
					printf("Carattere non valido. Riprovare. (y/n): ");
					fflush(stdout);
					fflush(stdin);
					scanf("%c", &yes_no);
					continue;
				}
			break;
    	}

    // 2. L'utente ï¿½ presente e ne verifico la password. Se non si riesce ad accedere si puï¿½ tornare alla schermata precedente
    }
    else{
    	// VERIFICO LA PASSWORD
		do{
			printf("Inserire password: ");
			fflush(stdout);
			scanf("%s", password);

			// Password corretta, posso uscire dal loop impostando il flag di quit a true. Effettuo l'accesso.
			if(strcmp(password, Utente->password) == 0){
				quit_login = true;
				printf("\nEffettuo l'accesso!\n");
			}
			// Password Errata. Richiesta di un nuovo tentativo
			else{
				printf("************\nPASSWORD ERRATA\nSi desidera riprovare (y/n): ");
				fflush(stdout);
				fflush(stdin);
				scanf("%c", &yes_no);

				switch(yes_no){
					// Si riprova a inserire la password
					case 'y':
						printf("\n");
						break;
					case 'n':

					// Si ritorna al menu iniziale ritornando NULL all'utente attuale.
						Utente = NULL;
						printf("*****************\nRITORNO AL MENU INIZIALE\n");
						return Utente;

					// Richiesta non valida
					default:
						printf("Carattere non valido. Riprovare (y/n)");
						fflush(stdout);
						fflush(stdin);
						continue;
					}
			}

		}while(!quit_login);
	}

    return Utente;
}

// Funzione per la registrazione
Utente* RegistraUtente (Utente* ListaUtenti){

	char username[STRING_MAX];
	char password[STRING_MAX];

	while(true){
		printf("Inserire nome utente: ");
		fflush(stdin);
		fflush(stdout);

		scanf("%s", username);

		// Se il nome utente ï¿½ giï¿½ presente si richiede un nuovo inserimento.
		if(TrovaUtente(username, ListaUtenti) != NULL){
			printf("Nome utente giï¿½ esistente. Riprovare.\n");
			continue;
		}
		break;
	}
	printf("Inserire password: ");
	fflush(stdin);
	fflush(stdout);
	scanf("%s", password);

	// Aggiungo il nuovo utente alla lista.
	ListaUtenti = AggiungiListaUtenti(ListaUtenti, username, password);

	return ListaUtenti;
}




/**************************************************************************/
/**************************************************************************/
