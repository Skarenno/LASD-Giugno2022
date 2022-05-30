/*
 * UserProgram.h
 *
 *  Created on: 27 mag 2022
 */

#ifndef ADMINPROGRAM_H_
#define ADMINPROGRAM_H_

#ifndef STD_HEAD
#define STD_HEAD "standard_header.h"
#include STD_HEAD
#endif

#include "GestioneAdmin.h"

void adminDashboard(Admin* admin, GraphViaggi* grafo);
GraphViaggi* menuAggiungiMeta(GraphViaggi* grafo);

#endif /* ADMINPROGRAM_H_ */
