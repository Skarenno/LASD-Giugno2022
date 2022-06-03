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
}HeapNode;

// Structure to represent a min heap
typedef struct minheap{

    // Number of heap nodes present currently
    int size;

    // Capacity of min heap
    int capacity;

    // This is needed for decreaseKey()
    int *pos;
    HeapNode **array;
}Heap;

HeapNode* NuovoHeapNode(int v, float dist, float prezzo);
Heap* CreazioneHeap(int capacity);
void ScambiaNodi(HeapNode** a, HeapNode** b);
void Heapify(Heap* minHeap, int idx);
int isEmptyHeap(Heap* minHeap);
HeapNode* TrovaMinimo(Heap* minHeap);
void RiduciDistanza(Heap* minHeap, int v, float dist, float prezzo);
bool isInMinHeap(Heap *minHeap, int v);
void StampaDijkstra(float dist[], float prezzo[], int n);
float DijkstraViaggi(GraphViaggi* graph, int partenza, int arrivo, int tipoPeso, float *distanceReturned);
float DijkstraAlberghi(GraphCitta* graph, int partenza, int arrivo);
void printPath(GraphCitta* grafo, int parent[], int j);
int minDistance(int dist[], bool sptSet[], int V);

#endif
