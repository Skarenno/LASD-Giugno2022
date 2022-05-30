#include "VerificheFile.h"

int VerificaFile(FILE* fp, char message[]){
	int size;

	if((fp=fopen(message, "r"))==NULL) {
			printf("Impossibile aprire il file\n");
			exit(1);
		}

	if (fp!=NULL) { /*Controlla che il file non sia vuoto*/
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);

	}

	return size;
}
