#include "standard_header.h"

#define U_FILE "./FILES/UTENTI.txt"

typedef struct u_node{
	char nome[STRING_MAX];
	char password[STRING_MAX];

	float saldo;
	struct u_node* next;
}Utente;


Utente* LeggiFileUtenti(FILE* file, Utente* ListaUtenti);
void RiscriviFileUtenti(FILE* FileUtenti, Utente* ListaUtenti);
Utente* SchermataIniziale(Utente* ListaUtenti);
Utente* AccessoUtente(Utente* ListaUtenti);
void RegistraUtente (Utente* ListaUtenti);
void StampaListaUtenti(Utente* Lista);
