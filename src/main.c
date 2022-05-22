#include <stdio.h>
#include <stdlib.h>

#include "Viaggi.h"

/*
 * main.c
 *
 *  Created on: 20 mag 2022
 *      Author: valerio, giovanni, salvatore
 */


int main(){
	printf("Ciao");
	GraphViaggi* G = AllocaGrafo();
	InserisciVertice(G, "Napoli");
	addArco(G, 0, "Bologna", 23 ,57, 7, 2);
	addArco(G, 0, "Firenze", 23 ,45 ,67 ,54);

	stampaGrafo(G);
	return 0;
}
