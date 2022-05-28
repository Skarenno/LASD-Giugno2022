#include "GestioneAdmin.h"

/********************** FUNZIONI PER LA LISTA ADMIN **********************/
/**************************************************************************/



Admin* InizializzaNodoAdmin(Admin* nodo) {
	nodo = (Admin*)malloc(sizeof(Admin));
	nodo->nome[0] = '\0'; /*Inizializzo la stringa*/
	nodo->password[0] = '\0'; /*Inizializzo la stringa*/
	nodo->next = NULL;

	return nodo;
}

//Aggiunta in testa alla lista
Admin* AggiungiListaAdmin(Admin* ListaAdmin, char* nome, char* password) {
	Admin* new = NULL;
	new = InizializzaNodoAdmin(new);

	strcpy(new->nome, nome);
	strcpy(new->password, password);

	if(ListaAdmin==NULL)
		ListaAdmin = new;
	else {
		new->next = ListaAdmin;
		ListaAdmin = new;
	}
	return ListaAdmin;
}

// Trova un Admin nella lista, restituisce NULL se l'admin non viene trovato (Ricorsiva)
Admin* TrovaAdmin(char* nomeInserito, Admin* ListaAdmin) {
	if(ListaAdmin == NULL){
		return NULL;
	}

	if(strcmp(nomeInserito, ListaAdmin->nome)==0)
		return ListaAdmin;

	return TrovaAdmin(nomeInserito, ListaAdmin->next);
}

// Stampa a schermo la lista Admin (Ricorsiva)
void StampaListaAdmin(Admin* ListaAdmin) {
	printf("Nome: %s Password: %s\n", ListaAdmin->nome, ListaAdmin->password);

	if(ListaAdmin->next!=NULL)
		StampaListaAdmin(ListaAdmin->next);

	return;
}



/**************************************************************************/
/**************************************************************************/




/*************** FUNZIONI PER GESTIONE FILE UTENTI ************************/
/**************************************************************************/

// Scrivo la lista locale dal file Admin (Ricorsiva)
Admin* LeggiFileAdmin (FILE* file, Admin* ListaAdmin) {
	if(ListaAdmin==NULL)
		ListaAdmin = InizializzaNodoAdmin(ListaAdmin);

	if(!feof(file)) {
		fscanf(file, "%s %s", ListaAdmin->nome, ListaAdmin->password);
		ListaAdmin->next = LeggiFileAdmin(file, ListaAdmin->next);
	} else {
		free(ListaAdmin);
		return NULL;
	}

	return ListaAdmin;
}

// Riscrivo il file a partire dall'attuale lista degli Admin
void RiscriviFileAdmin(Admin* ListaAdmin) {
	FILE* FileAdmin = fopen(A_FILE, "w+");
	Admin* cursor = ListaAdmin;

	while(cursor!=NULL) {
		fprintf(FileAdmin, "%s %s", cursor->nome, cursor->password);
		cursor = cursor->next;
		if(cursor)
			fprintf(FileAdmin, "\n");
	}
}

/**************************************************************************/
/**************************************************************************/




/*********** FUNZIONI GENERALI PER MENU, ACCESSO E REGISTRAZIONE ***********/
/**************************************************************************/


// Schermata Iniziale. Ritorna l'admin con cui si è effettuato l'accesso
Admin* SchermataInizialeAdmin(Admin* ListaAdmin) {
	//INIZIALIZZO VARIABILI LOCALI
	Admin* AdminAttuale = NULL;
	int scelta, check = 0;
	bool accesso = false;

	//Apro e leggo il file admin
	FILE* FileAdmin = fopen(A_FILE, "r+");
	if(FileAdmin==NULL) {
		printf("ERRORE DATABASE UTENTI");
		return NULL;
	}
	ListaAdmin = LeggiFileAdmin(FileAdmin, ListaAdmin);
	fclose(FileAdmin); // Chiusura file admin

	printf("***************\n **Benvenuto** \n***************\n\n");
	sleep(1);
	do {
		// ESCO DAL WHILE (E PASSO ALLA SCHERMATA SUCCESSIVA) SOLO QUANDO L'ACCESSO È AVVENUTO CORRETTAMENTE.
		printf("\nImmettere azione da eseguire (1. Accesso - 2. Registrazione - 3. Chiudi Applicativo):");
		fflush(stdout);
		fflush(stdin);
		check = scanf("%d", &scelta);

		if(check==1) {
			switch(scelta) {
				//Accesso
				case 1:
					AdminAttuale = AccessoAdmin(ListaAdmin);
					if(AdminAttuale!=NULL)
						accesso = true;
					break;
				// Registrazione
				case 2:
					ListaAdmin = RegistraAdmin(ListaAdmin);
					RiscriviFileAdmin(ListaAdmin); // Aggiorno il database quando registro un nuovo utente
					//StampaListaAdmin(ListaAdmin); // Per Debug stampo a schermo la lista dopo aver aggiunto il nodo del nuovo utente in testa
					continue;
				// Chiusura Programma
				case 3:
					// CHIUSURA
					printf("\nArrivederci!\n************");
					sleep(1);
					exit(EXIT_SUCCESS);
				default:
					printf("\n---Non valido!---\n");
					break;
			}
		} else {
			printf("Valore non valido\n");
		}
	}while(accesso == false);

	// Ritorno il nodo admin di cui ho effettuato l'accesso
	return AdminAttuale;
}


// Funzione per l'accesso
Admin* AccessoAdmin(Admin* ListaAdmin) {
	char n_admin[STRING_MAX];
	char password[STRING_MAX];
	bool quit_login = false;
	char yes_no;

	printf("\nInserire nome admin: ");
	fflush(stdout);
	scanf("%s", n_admin);

    Admin* admin = TrovaAdmin(n_admin, ListaAdmin);

    /** DUE CASI **/

    // 1. L'utente non è presente nel Database e si richiede se si vuole registrarsi
    if(admin==NULL) {
    	printf("\nAdmin non trovato... desidera registrarsi (y/n)? ");
    	fflush(stdout);
    	fflush(stdin);
    	scanf("%c", &yes_no);

    	// Il while serve per il default nello switch
    	while(1) {
    		switch(yes_no) {
				// Se si, procedo alla registrazione
				case 'y':
					RegistraAdmin(ListaAdmin);
					RiscriviFileAdmin(ListaAdmin);
					break;

				// Se no, ritorno al menu iniziale
				case 'n':
					admin = NULL;
					printf("*****************\nRITORNO AL MENU INIZIALE\n");
					return admin;

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
    // 2. L'utente è presente e ne verifico la password. Se non si riesce ad accedere si può tornare alla schermata precedente
    } else {
    	// VERIFICO LA PASSWORD
    	do{
    		printf("Inserire password: ");
    		fflush(stdout);
    		scanf("%s", password);

    		// Password corretta, posso uscire dal loop impostando il flag di quit a true. Effettuo l'accesso.
    		if(strcmp(password, admin->password) == 0){
    			quit_login = true;
    			printf("\nEffettuo l'accesso!\n");
    		} else{ // Password Errata. Richiesta di un nuovo tentativo
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
    					admin = NULL;
    					printf("*****************\nRITORNO AL MENU INIZIALE\n");
    					return admin;
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

    return admin;
}

// Funzione per la registrazione
Admin* RegistraAdmin (Admin* ListaAdmin){

	char username[STRING_MAX];
	char password[STRING_MAX];

	while(true){
		printf("Inserire nome admin: ");
		fflush(stdin);
		fflush(stdout);

		scanf("%s", username);

		// Se il nome admin è già presente si richiede un nuovo inserimento.
		if(TrovaAdmin(username, ListaAdmin)!=NULL){
			printf("Nome admin già esistente. Riprovare.\n");
			continue;
		}
		break;
	}
	printf("Inserire password: ");
	fflush(stdin);
	fflush(stdout);
	scanf("%s", password);

	// Aggiungo il nuovo admin alla lista.
	ListaAdmin = AggiungiListaAdmin(ListaAdmin, username, password);

	return ListaAdmin;
}

ListaAttesa *aggiungiMetaAttesa(GraphViaggi *grafo, ListaAttesa *lista) {
	if(lista==NULL)
		return NULL;
	ListaAttesa *tmp = lista;
	while(tmp!=NULL) {
		InserisciVertice(grafo, tmp->nome);
		tmp = tmp->next;
	}
	ListaAttesa *lista1 = NULL;
	char *nome = (char*)malloc(sizeof(char)*STRING_MAX);
	int tempoAereo = 0, tempoTreno = 0;
	float prezzoAereo = 0, prezzoTreno = 0;
	bool check = false;
	for(int i=grafo->numVertici-lista->numElem; i<grafo->numVertici; i++) {
		printf("Inserisci collegamenti per %s\n", grafo->adj[i]->citta);
		char choice; //Permette l'uscita dal do while nella riga successiva
		do {
			printf("Nome Citta: ");
			scanf("%s", nome);
			printf("\n");
			fflush(stdin);
			nome[0] = toupper(nome[0]);
			for(int j=0; j<grafo->numVertici; j++) //Controllo se la citta esiste nel grafo, se non esiste la faccio collegare ma la inserisco in attesa
				if(strcmp(grafo->adj[i]->citta, nome)==0)
					check = true;
			if(check==false) { //Eventuale aggiunta alla ListaAttesa
				printf("Meta non esistente! Aggiunta alla lista di Attesa!\n");
				ListaAttesa *nodo = NULL;
				lista1 = inserisciNodo(lista, inizializzaNodo(nodo, nome));
			}
			do { //Controlli per tempo viaggio aereo
				printf("Tempo Aereo: ");
				if(!scanf("%d", &tempoAereo) || tempoAereo<0) {
					printf("\nValore non Valido\n");
					fflush(stdin);
				} else {
					printf("\n");
					break;
				}
			} while(1);
			fflush(stdin);
			do { //Controlli per prezzo viaggio aereo
				printf("Prezzo Aereo: ");
				if(!scanf("%f", &prezzoAereo) || (prezzoAereo==0 && tempoAereo>0)) { //Controlla che il prezzo inserito sia valido e che non sia 0 se il tempoAereo>0
					printf("\nValore non Valido\n");
					fflush(stdin);
				} else {
					printf("\n");
					break;
				}
			} while(1);
			fflush(stdin);
			do { //Controlli per tempo viaggio treno
				printf("Tempo Treno: ");
				if(!scanf("%d", &tempoTreno) || tempoTreno<0) {
					printf("\nValore non Valido\n");
					fflush(stdin);
				} else {
					printf("\n");
					break;
				}
			} while(1);
			fflush(stdin);
			do { //Controlli per prezzo viaggio treno
				printf("Prezzo Treno: ");
				if(!scanf("%f", &prezzoTreno) || (prezzoTreno==0 && tempoTreno>0)) { //Controlla che il prezzo inserito sia valido e che non sia 0 se il tempoTreno>0
					printf("\nValore non Valido\n");
					fflush(stdin);
				} else {
					printf("\n");
					break;
				}
			} while(1);
			fflush(stdin);
			addArco(grafo, i, nome, prezzoAereo, prezzoTreno, tempoAereo, tempoTreno);
			do {
				printf("Devi aggiungere altri collegamenti?(y/n)\n");
				scanf("%c", &choice);
				fflush(stdin);
				choice = tolower(choice);
				if(choice!='y' && choice!='n')
					printf("Valore non Valido!\n");
				else
					break;
			} while(1);
		} while(choice!='n');
	}
	lista = svuotaLista(lista);
	return lista1;
}
