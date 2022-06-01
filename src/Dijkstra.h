#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "standard_header.h"
#include "Viaggi.h"
#include "Citta.h"

// Structure to represent a min heap node
typedef struct minheapnode{
    int  v;
    float dist;
    float prezzo;
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

MinHeapNode* newMinHeapNode(int v, float dist, float prezzo);
MinHeap* createMinHeap(int capacity);
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int idx);
int isEmptyHeap(MinHeap* minHeap);
MinHeapNode* extractMin(MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int v, float dist, float prezzo);
bool isInMinHeap(MinHeap *minHeap, int v);
void printArr(float dist[], float prezzo[], int n);
float dijkstra(GraphViaggi* graph, int partenza, int arrivo, int tipoPeso, float *distanceReturned);
float dijkstraAlberghi(GraphCitta* graph, int partenza, int arrivo);


#endif
