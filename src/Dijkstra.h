#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "standard_header.h"
#include "Viaggi.h"

// Structure to represent a min heap node
typedef struct minheapnode{
    int  v;
    float dist;
}MinHeapNode;

// Structure to represent a min heap
typedef struct minheap{

    // Number of heap nodes present currently
    int size;

    // Capacity of min heap
    int capacity;

    // This is needed for decreaseKey()
    int *pos;
    MinHeapNode **array;
}MinHeap;

MinHeapNode* newMinHeapNode(int v, float dist);
MinHeap* createMinHeap(int capacity);
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int idx);
int isEmptyHeap(MinHeap* minHeap);
MinHeapNode* extractMin(MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int v, float dist);
bool isInMinHeap(MinHeap *minHeap, int v);
void printArr(float dist[], int n);
float dijkstra(GraphViaggi* graph, int partenza, int arrivo, int tipoPeso);


#endif
