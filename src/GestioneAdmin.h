#ifndef GESTIONEADMIN_H_
#define GESTIONEADMIN_H_

#ifndef STD_HEAD
#define STD_HEAD "standard_header.h"
#include STD_HEAD
#endif

#ifndef VIAGGI_H
#define VIAGGI_H "Viaggi.h"
#include VIAGGI_H
#endif

#include "Citta.h"
#include "ListaAttesa.h"


#define A_FILE "./src/FILES/ADMIN.txt"

typedef struct a_node {
	char nome[STRING_MAX];
	char password[STRING_MAX];

	struct a_node* next;
}Admin;

Admin* InizializzaNodoAdmin(Admin* nodo);
Admin* AggiungiListaAdmin(Admin* ListaAdmin, char* nome, char* password);
void StampaListaAdmin(Admin* ListaAdmin);



Admin* LeggiFileAdmin (FILE* file, Admin* ListaAdmin);
void RiscriviFileAdmin(Admin* ListaAdmin);


Admin* SchermataInizialeAdmin(Admin* ListaAdmin);
Admin* AccessoAdmin(Admin* ListaAdmin);
Admin* RegistraAdmin(Admin* ListaAdmin);

ListaAttesa *aggiungiMetaAttesa(GraphViaggi *grafo, ListaAttesa *lista);
void aggiungiAlberghi(ListaAttesa *lista);

#endif /* GESTIONEADMIN_H_ */
