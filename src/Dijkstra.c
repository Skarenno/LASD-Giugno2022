#include "standard_header.h"
#include "Dijkstra.h"
#include "Viaggi.h"


// A utility function to create a
// new Min Heap Node
MinHeapNode* newMinHeapNode(int v, float dist, float prezzo)
{
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    minHeapNode->prezzo = prezzo;
    return minHeapNode;
}

// A utility function to create a Min Heap
MinHeap* createMinHeap(int capacity)
{
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(
            capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// A standard function to
// heapify at given idx
// This function also updates
// position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist <
         minHeap->array[smallest]->dist )
      smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist <
         minHeap->array[smallest]->dist )
      smallest = right;

    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode =
             minHeap->array[smallest];
        MinHeapNode *idxNode =
                 minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest],
                         &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// A utility function to check if
// the given minHeap is ampty or not
int isEmptyHeap(MinHeap* minHeap)
{
    return minHeap->size == 0;
}

// Standard function to extract
// minimum node from heap
MinHeapNode* extractMin(MinHeap* minHeap)
{
    if(isEmptyHeap(minHeap))
        return NULL;

    // Store the root node
    MinHeapNode* root = minHeap->array[0];

    // Replace root node with last node
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decreasy dist value
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void decreaseKey(MinHeap* minHeap, int v, float dist, float prezzo)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];

    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
    minHeap->array[i]->prezzo = prezzo;

    // Travel up while the complete
    // tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist <
           minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] =
                                      (i-1)/2;
        minHeap->pos[minHeap->array[
                             (i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],
                 &minHeap->array[(i - 1) / 2]);

        // move to parent index
        i = (i - 1) / 2;
    }
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}

// A utility function used to print the solution
void printArr(float dist[], float prezzo[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %.0f : %.2f\n", i, dist[i], prezzo[i]);
}

// The main function that calculates
// distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
float dijkstra(GraphViaggi* graph, int partenza, int arrivo, int tipoPeso, float *distanceReturned){

	//Flag to get price or distance
	int typology=0;

    // Get the number of vertices in graph
    int V = graph->numVertici;

    // dist values used to pick
    // minimum weight edge in cut
    float dist[V];
    float prezzo[V];

    // minHeap represents set E
    MinHeap* minHeap = createMinHeap(V);

    // Initialize min heap with all
    // vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        prezzo[V] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v],prezzo[v]);
        minHeap->pos[v] = v;
    }

    // Make dist value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[partenza] = newMinHeapNode(partenza, dist[partenza], prezzo[partenza]);
    minHeap->pos[partenza]   = partenza;
    dist[partenza] = 0;
    prezzo[partenza] = 0;
    decreaseKey(minHeap, partenza, dist[partenza], prezzo[partenza]);

    // Initially size of min heap is equal to V
    minHeap->size = V;

    // In the followin loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.
    while (!isEmptyHeap(minHeap))
    {
        // Extract the vertex with
        // minimum distance value
        MinHeapNode* minHeapNode =
                     extractMin(minHeap);

        // Store the extracted vertex number
        int u = minHeapNode->v;

			// Traverse through all adjacent
			// vertices of u (the extracted
        // vertex) and update
        // their distance values
        EdgeViaggi* pCrawl = graph->adj[u];
        while (pCrawl != NULL){
            int v = pCrawl->key;

            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance
            switch(tipoPeso){
				case 0: // prezzoAereo
					typology=0;
					if(pCrawl->prezzoAereo != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->prezzoAereo + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)pCrawl->prezzoAereo;
							prezzo[v] = prezzo[u] + (float)pCrawl->tempoAereo; //WARNING:Distanze!

							// update distance
							// value in min heap also
							decreaseKey(minHeap, v, dist[v],prezzo[v]);
						}
					}
					break;

				case 1: //tempoAereo
					typology=1;
					if(pCrawl->tempoAereo != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->tempoAereo + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)pCrawl->tempoAereo;
							prezzo[v] = prezzo[u] + (float)pCrawl->prezzoAereo;

							// update distance
							// value in min heap also
							decreaseKey(minHeap, v, dist[v],prezzo[v]);
						}
					}
            	break;

            	case 2:	//prezzoTreno
            		typology=0;
            		if(pCrawl->prezzoTreno != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->prezzoTreno + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)pCrawl->prezzoTreno;
							prezzo[v] = prezzo[u] + (float)pCrawl->tempoTreno; //WARNING:Distanze!

							// update distance
							// value in min heap also
							decreaseKey(minHeap, v, dist[v],prezzo[v]);
						}
					}
            	break;

            	case 3: //tempoTreno
            		typology=1;
					if(pCrawl->tempoTreno != 0){
						if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->tempoTreno + dist[u] < dist[v]){
							dist[v] = dist[u] + (float)pCrawl->tempoTreno;
							prezzo[v] = prezzo[u] + (float)pCrawl->prezzoTreno;

							// update distance
							// value in min heap also
							decreaseKey(minHeap, v, dist[v],prezzo[v]);
						}
					}
            	break;
            }

            pCrawl = pCrawl->next;
        }

    }
    // print the calculated shortest distances
    printArr(dist,prezzo, V);

    if (typology){
    	*distanceReturned = dist[arrivo];
    	return prezzo[arrivo];
    }
    *distanceReturned = prezzo[arrivo];
    return dist[arrivo];

}



float dijkstraAlberghi(GraphCitta* graph, int partenza, int arrivo){

    // Get the number of vertices in graph
    int V = graph->numVertici;

    // dist values used to pick
    // minimum weight edge in cut
    float dist[V];

    // minHeap represents set E
    MinHeap* minHeap = createMinHeap(V);

    // Initialize min heap with all
    // vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v],0);
        minHeap->pos[v] = v;
    }

    // Make dist value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[partenza] = newMinHeapNode(partenza, dist[partenza], 0);
    minHeap->pos[partenza]   = partenza;
    dist[partenza] = 0;
    decreaseKey(minHeap, partenza, dist[partenza], 0);

    // Initially size of min heap is equal to V
    minHeap->size = V;

    // In the followin loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.
    while (!isEmptyHeap(minHeap))
    {
        // Extract the vertex with
        // minimum distance value
        MinHeapNode* minHeapNode =
                     extractMin(minHeap);

        // Store the extracted vertex number
        int u = minHeapNode->v;

			// Traverse through all adjacent
			// vertices of u (the extracted
        // vertex) and update
        // their distance values
        EdgeCitta* pCrawl = graph->adj[u];
        while (pCrawl != NULL){
            int v = pCrawl->key;

            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance



			 if(pCrawl->tempo != 0){
				if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->tempo + dist[u] < dist[v]){
					dist[v] = dist[u] + (float)pCrawl->tempo;


					// update distance
					// value in min heap also
					decreaseKey(minHeap, v, dist[v],0);
				}
			}
			pCrawl = pCrawl->next;
        }

    }
    // print the calculated shortest distances
    printArr(dist,dist, V);

    return dist[arrivo];

}
