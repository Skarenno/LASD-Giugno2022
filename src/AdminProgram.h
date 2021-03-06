/*
 * UserProgram.h
 *
 *  Created on: 27 mag 2022
 */

#ifndef ADMINPROGRAM_H_
#define ADMINPROGRAM_H_

#include "standard_header.h"
#include "GestioneAdmin.h"
#include "Dijkstra.h"

void adminDashboard(Admin* admin, GraphViaggi* grafo);
GraphViaggi* menuAggiungiMeta(GraphViaggi* grafo);
GraphCitta* AggiungiAlbergo(GraphCitta* GrafoCitta, GraphViaggi* grafo, FILE* FileCitta, char* nomeFile);
GraphViaggi *menuEliminaArco(GraphViaggi *grafo);


#endif /* ADMINPROGRAM_H_ */
