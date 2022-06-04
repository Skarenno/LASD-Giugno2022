#include "standard_header.h"
#include "Dijkstra.h"
#include "Viaggi.h"


// A utility function to create a
// new Min Heap Node
HeapNode* NuovoHeapNode(int v, float dist, float prezzo)
{
    HeapNode* minHeapNode = (HeapNode*)malloc(sizeof(HeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    minHeapNode->prezzo = prezzo;
    return minHeapNode;
}

// A utility function to create a Min Heap
Heap* CreazioneHeap(int max_size){

    Heap* minHeap = (Heap*)malloc(sizeof(Heap));
    minHeap->pos = (int *)malloc(max_size * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = max_size;
    minHeap->array = (HeapNode**)malloc(max_size * sizeof(HeapNode*));
    return minHeap;
}

// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void ScambiaNodi(HeapNode** a, HeapNode** b)
{
    HeapNode* t = *a;
    *a = *b;
    *b = t;
}


void Heapify(Heap* MinimumHeap, int idx){

    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < MinimumHeap->size && MinimumHeap->array[left]->dist <MinimumHeap->array[smallest]->dist)
      smallest = left;

    if (right < MinimumHeap->size && MinimumHeap->array[right]->dist < MinimumHeap->array[smallest]->dist)
      smallest = right;

    if (smallest != idx){
        // Prendiamo i nodi da scambiare
        HeapNode *smallestNode = MinimumHeap->array[smallest];
        HeapNode *idxNode = MinimumHeap->array[idx];

        // Scambiamo le posizioni
        MinimumHeap->pos[smallestNode->v] = idx;
        MinimumHeap->pos[idxNode->v] = smallest;

        // Scambiamo i nodi
        ScambiaNodi(&MinimumHeap->array[smallest], &MinimumHeap->array[idx]);
        Heapify(MinimumHeap, smallest);

    }
}

int isEmptyHeap(Heap* minHeap)
{
    return minHeap->size == 0;
}


HeapNode* TrovaMinimo(Heap* minHeap){

    if(isEmptyHeap(minHeap))
        return NULL;

    HeapNode* root = minHeap->array[0];
    HeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    Heapify(minHeap, 0);

    return root;
}


// Funzione per la riduzione nel calcolo della distanza
void RiduciDistanza(Heap* minHeap, int v, float dist, float prezzo){

    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;
    minHeap->array[i]->prezzo = prezzo;


    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist){

        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        ScambiaNodi(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}


bool isInMinHeap(Heap *minHeap, int v){
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}

// Debug per la Stampa
void StampaDijkstra(float dist[], float prezzo[], int n){
    printf("Vertice   Distanza da Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %.0f : %.2f\n", i, dist[i], prezzo[i]);
}


float DijkstraViaggi(GraphViaggi* graph, int partenza, int arrivo, int tipoPeso, float *distanceReturned){

	//Flag per la tipologia di peso
	int typology=0;
    int V = graph->numVertici;

    // Valori per lo storing delle distanze
    float dist[V];
    float prezzo[V];

    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[V];

    // Parent array to store shortest path tree
    int parent[V];

    Heap* minHeap = CreazioneHeap(V);

    // Inizializziamo l'Heap con le distanze a "Infinito"
    for (int v = 0; v < V; ++v){
        dist[v] = INT_MAX;
        prezzo[V] = INT_MAX;
        parent[v] = -1;
        sptSet[v] = false;
        minHeap->array[v] = NuovoHeapNode(v, dist[v],prezzo[v]);
        minHeap->pos[v] = v;
    }

    // Distanza da se stesso = 0
    minHeap->array[partenza] = NuovoHeapNode(partenza, dist[partenza], prezzo[partenza]);
    minHeap->pos[partenza]   = partenza;
    dist[partenza] = 0;
    prezzo[partenza] = 0;
    RiduciDistanza(minHeap, partenza, dist[partenza], prezzo[partenza]);

    // Inizialmente la  grandezza dell'Heap � V (VERTICI)
    minHeap->size = V;


    // Inizio loop principale
    while (!isEmptyHeap(minHeap))
    {
        // Troviamo il vertice della distanza minima e estraiamone l'indice
        HeapNode* minHeapNode = TrovaMinimo(minHeap);
        int u = minHeapNode->v;

        int uu = minDistance((int*)dist, sptSet, V);
        sptSet[uu] = true;


        // Temp per attraversare i Vertici adiacenti
        EdgeViaggi* TempNode = graph->adj[u];


        // Attraversiamo i vertici adiacenti
        while (TempNode != NULL){
            int v = TempNode->key;

            // Effettuiamo il calcolo rispetto al tipo di peso da considerare
            // Dopo effettuiamo i controlli sull'update del valore delle distanze
            switch(tipoPeso){
				case 0: // prezzoAereo
					typology=0;
					if(TempNode->prezzoAereo != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && TempNode->prezzoAereo + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)TempNode->prezzoAereo;
							prezzo[v] = prezzo[u] + (float)TempNode->tempoAereo; //WARNING:Distanze!
							parent[v]  = u;

							// update distance
							// value in min heap also
							RiduciDistanza(minHeap, v, dist[v],prezzo[v]);
						}
					}
					break;

				case 1: //tempoAereo
					typology=1;
					if(TempNode->tempoAereo != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && TempNode->tempoAereo + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)TempNode->tempoAereo;
							prezzo[v] = prezzo[u] + (float)TempNode->prezzoAereo;
							parent[v]  = u;

							// update distance
							// value in min heap also
							RiduciDistanza(minHeap, v, dist[v],prezzo[v]);
						}
					}
            	break;

            	case 2:	//prezzoTreno
            		typology=0;
            		if(TempNode->prezzoTreno != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && TempNode->prezzoTreno + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)TempNode->prezzoTreno;
							prezzo[v] = prezzo[u] + (float)TempNode->tempoTreno; //WARNING:Distanze!
							parent[v]  = u;

							// update distance
							// value in min heap also
							RiduciDistanza(minHeap, v, dist[v],prezzo[v]);
						}
					}
            	break;

            	case 3: //tempoTreno
            		typology=1;
					if(TempNode->tempoTreno != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && TempNode->tempoTreno + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)TempNode->tempoTreno;
							prezzo[v] = prezzo[u] + (float)TempNode->prezzoTreno;
							parent[v]  = u;

							// update distance
							// value in min heap also
							RiduciDistanza(minHeap, v, dist[v],prezzo[v]);
						}
					}
            	break;
            }

            TempNode = TempNode->next;
        }

    }

    //StampaDijkstra(dist,prezzo, V); //Per debug
    printf("\nPercorso: \n|%s -> ",graph->adj[partenza]->citta);
    printPathV(graph, parent,arrivo);
    printf("|\n");

    // Ritorno
    if (typology){
    	*distanceReturned = dist[arrivo];
    	return prezzo[arrivo];
    }
    *distanceReturned = prezzo[arrivo];
    return dist[arrivo];

}

float DijkstraViaggiNoPrint(GraphViaggi* graph, int partenza, int arrivo, int tipoPeso, float *distanceReturned){

	//Flag per la tipologia di peso
	int typology=0;
    int V = graph->numVertici;

    // Valori per lo storing delle distanze
    float dist[V];
    float prezzo[V];

    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[V];

    // Parent array to store shortest path tree
    int parent[V];

    Heap* minHeap = CreazioneHeap(V);

    // Inizializziamo l'Heap con le distanze a "Infinito"
    for (int v = 0; v < V; ++v){
        dist[v] = INT_MAX;
        prezzo[V] = INT_MAX;
        parent[v] = -1;
        sptSet[v] = false;
        minHeap->array[v] = NuovoHeapNode(v, dist[v],prezzo[v]);
        minHeap->pos[v] = v;
    }

    // Distanza da se stesso = 0
    minHeap->array[partenza] = NuovoHeapNode(partenza, dist[partenza], prezzo[partenza]);
    minHeap->pos[partenza]   = partenza;
    dist[partenza] = 0;
    prezzo[partenza] = 0;
    RiduciDistanza(minHeap, partenza, dist[partenza], prezzo[partenza]);

    // Inizialmente la  grandezza dell'Heap � V (VERTICI)
    minHeap->size = V;


    // Inizio loop principale
    while (!isEmptyHeap(minHeap))
    {
        // Troviamo il vertice della distanza minima e estraiamone l'indice
        HeapNode* minHeapNode = TrovaMinimo(minHeap);
        int u = minHeapNode->v;

        int uu = minDistance((int*)dist, sptSet, V);
        sptSet[uu] = true;


        // Temp per attraversare i Vertici adiacenti
        EdgeViaggi* TempNode = graph->adj[u];


        // Attraversiamo i vertici adiacenti
        while (TempNode != NULL){
            int v = TempNode->key;

            // Effettuiamo il calcolo rispetto al tipo di peso da considerare
            // Dopo effettuiamo i controlli sull'update del valore delle distanze
            switch(tipoPeso){
				case 0: // prezzoAereo
					typology=0;
					if(TempNode->prezzoAereo != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && TempNode->prezzoAereo + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)TempNode->prezzoAereo;
							prezzo[v] = prezzo[u] + (float)TempNode->tempoAereo; //WARNING:Distanze!
							parent[v]  = u;

							// update distance
							// value in min heap also
							RiduciDistanza(minHeap, v, dist[v],prezzo[v]);
						}
					}
					break;

				case 1: //tempoAereo
					typology=1;
					if(TempNode->tempoAereo != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && TempNode->tempoAereo + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)TempNode->tempoAereo;
							prezzo[v] = prezzo[u] + (float)TempNode->prezzoAereo;
							parent[v]  = u;

							// update distance
							// value in min heap also
							RiduciDistanza(minHeap, v, dist[v],prezzo[v]);
						}
					}
            	break;

            	case 2:	//prezzoTreno
            		typology=0;
            		if(TempNode->prezzoTreno != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && TempNode->prezzoTreno + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)TempNode->prezzoTreno;
							prezzo[v] = prezzo[u] + (float)TempNode->tempoTreno; //WARNING:Distanze!
							parent[v]  = u;

							// update distance
							// value in min heap also
							RiduciDistanza(minHeap, v, dist[v],prezzo[v]);
						}
					}
            	break;

            	case 3: //tempoTreno
            		typology=1;
					if(TempNode->tempoTreno != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && TempNode->tempoTreno + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)TempNode->tempoTreno;
							prezzo[v] = prezzo[u] + (float)TempNode->prezzoTreno;
							parent[v]  = u;

							// update distance
							// value in min heap also
							RiduciDistanza(minHeap, v, dist[v],prezzo[v]);
						}
					}
            	break;
            }

            TempNode = TempNode->next;
        }

    }

    // Ritorno
    if (typology){
    	*distanceReturned = dist[arrivo];
    	return prezzo[arrivo];
    }
    *distanceReturned = prezzo[arrivo];
    return dist[arrivo];

}

/*****************************************************************/


float DijkstraAlberghi(GraphCitta* graph, int partenza, int arrivo){

    int V = graph->numVertici;

    // Valori per lo storing delle distanze
    float dist[V];

    // sptSet[i] will true if vertex i is included / in shortest
       // path tree or shortest distance from src to i is finalized
       bool sptSet[V];

       // Parent array to store shortest path tree
       int parent[V];

    Heap* minHeap = CreazioneHeap(V);

    // Inizializziamo l'Heap con le distanze a "Infinito"
    for (int v = 0; v < V; ++v){
        dist[v] = INT_MAX;
        parent[v] = -1;
        sptSet[v] = false;
        minHeap->array[v] = NuovoHeapNode(v, dist[v],0);
        minHeap->pos[v] = v;
    }

    // Distanza da se stesso = 0
    minHeap->array[partenza] = NuovoHeapNode(partenza, dist[partenza], 0);
    minHeap->pos[partenza]   = partenza;
    dist[partenza] = 0;
    RiduciDistanza(minHeap, partenza, dist[partenza], 0);

    // Inizialmente la  grandezza dell'Heap � V (VERTICI)
    minHeap->size = V;


    // Inizio loop principale
    while (!isEmptyHeap(minHeap))
    {
        // Troviamo il vertice della distanza minima e estraiamone l'indice
        HeapNode* minHeapNode = TrovaMinimo(minHeap);

        int u = minHeapNode->v;

        int uu = minDistance((int*)dist, sptSet, V);
        sptSet[uu] = true;


        // Temp per attraversare i Vertici adiacenti
        EdgeCitta* TempNode = graph->adj[u];


        // Attraversiamo i vertici adiacenti
        while (TempNode != NULL){
            int v = TempNode->key;

            // Effettuiamo il calcolo rispetto al tipo di peso da considerare
            // Dopo effettuiamo i controlli sull'update del valore delle distanze
					if(TempNode->tempo != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && TempNode->tempo + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)TempNode->tempo;
							parent[v]  = u;

							// update distance
							// value in min heap also
							RiduciDistanza(minHeap, v, dist[v], 0);
						}
					}

            TempNode = TempNode->next;
        }

    }

    //StampaDijkstra(dist,dist, V); //Per Debug
    printf("\nPercorso: \n|%s -> ",graph->adj[partenza]->albergo);
    printPath(graph, parent,arrivo);
    printf("|\n");
    return dist[arrivo];

}

// Function to print shortest path from source to j
// using parent array
void printPath(GraphCitta* grafo, int parent[], int j) {
    // Base Case : If j is source
    if (parent[j]==-1)
        return;

    printPath(grafo, parent, parent[j]);

    printf("%s -> ", grafo->adj[j]->albergo);
}

// Function to print shortest path from source to j
// using parent array
void printPathV(GraphViaggi* grafo, int parent[], int j) {
    // Base Case : If j is source
    if (parent[j]==-1)
        return;

    printPathV(grafo, parent, parent[j]);

    printf("%s -> ", grafo->adj[j]->citta);
}

// A utility function to find the vertex with minimum distance
// value, from the set of vertices not yet included in shortest
// path tree
int minDistance(int dist[], bool sptSet[], int V) {
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
