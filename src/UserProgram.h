/*
 * UserProgram.h
 *
 *  Created on: 26 mag 2022
 */

#ifndef USERPROGRAM_H_
#define USERPROGRAM_H_

#include "standard_header.h"
#include "Viaggi.h"

#include "GestioneUtenti.h"


void userDashboard(Utente* user, GraphViaggi* GrafoViaggi);
void StampaMete (GraphViaggi* GrafoViaggi);
int VerificaCitta(GraphViaggi* GrafoViaggi, char citta[]);

#endif /* USERPROGRAM_H_ */
