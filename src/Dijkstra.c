#include "standard_header.h"
#include "Dijkstra.h"
#include "Viaggi.h"

MinimumHeap* CreateMinHeap (int capacity){
	MinimumHeap* Heap = (MinimumHeap*)malloc(sizeof(MinimumHeap));
	Heap->capacity = capacity;
	Heap->current_size = 0;

	Heap->arr = (HeapNode**)malloc(capacity * sizeof(HeapNode*));

	return Heap;
}




void Dijkstra(GraphViaggi* Graph, char src[STRING_MAX]){

}
