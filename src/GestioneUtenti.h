#ifndef GESTIONEUTENTI_H_
#define GESTIONEUTENTI_H_

#include "standard_header.h"

#define U_FILE "./src/FILES/UTENTI.txt"

typedef struct u_node{
	char nome[STRING_MAX];
	char password[STRING_MAX];

	float saldo;
	struct u_node* next;
}Utente;


// TODO Ordina prototipi e aggiungi prototipi mancanti


Utente* InizializzaNodoUtente(Utente* Nodo);
Utente* AggiungiListaUtenti(Utente* ListaUtenti, char* nome, char* password);
Utente* TrovaUtente(char *nomeInserito, Utente* ListaUtenti);
void StampaListaUtenti(Utente* Lista);



Utente* LeggiFileUtenti (FILE* file, Utente* ListaUtenti);
void RiscriviFileUtenti(Utente* ListaUtenti);


Utente* SchermataIniziale(Utente* ListaUtenti);
Utente* AccessoUtente(Utente* ListaUtenti);
Utente* RegistraUtente (Utente* ListaUtenti);

#endif /* GESTIONEUTENTI_H_ */
