/*
 * UserProgram.h
 *
 *  Created on: 26 mag 2022
 */

#ifndef USERPROGRAM_H_
#define USERPROGRAM_H_

#ifndef STD_HEAD
#define STD_HEAD "standard_header.h"
#include STD_HEAD
#endif

#ifndef VIAGGI_H
#define VIAGGI_H "Viaggi.h"
#include VIAGGI_H
#endif

#include "GestioneUtenti.h"


void userDashboard(Utente* user, GraphViaggi* GrafoViaggi);
void StampaMete (GraphViaggi* GrafoViaggi);
int VerificaCitta(GraphViaggi* GrafoViaggi, char citta[]);

#endif /* USERPROGRAM_H_ */
