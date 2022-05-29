#include "standard_header.h"

typedef struct heapnode{
	char citta[STRING_MAX];
	int distance;
}HeapNode;

typedef struct heap{
	int current_size;
	int capacity;


	int *pos;
	HeapNode** arr;
}MinimumHeap;



