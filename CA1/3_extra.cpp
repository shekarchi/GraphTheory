#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
 
struct AdjListNode
{
    int dest;
    int weight;
    struct AdjListNode* next;
};
 
struct AdjList
{
    struct AdjListNode *head;  
};
 
struct Graph
{
    int V;
    struct AdjList* array;
};
 
struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
struct MinHeapNode
{
    int  v;
    int dist;
};
 
struct MinHeap
{
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array;
};
 
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];
 
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}
 
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    struct MinHeapNode* root = minHeap->array[0];
 
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    int i = minHeap->pos[v];
 
    minHeap->array[i]->dist = dist;
 
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 
        i = (i - 1) / 2;
    }
}
 
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
 
void printArr(vector<int> *dist, int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, (*dist)[i]);
}
 
int* dijkstra(struct Graph* graph, vector<int> *dist, int src)
{
    int V = graph->V;
    struct MinHeap* minHeap = createMinHeap(V);
    for (int v = 0; v < V; v++)
    {
        (*dist)[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, (*dist)[v]);
	minHeap->pos[v] = v;
    }
    minHeap->array[src] = newMinHeapNode(src, (*dist)[src]);
    minHeap->pos[src]   = src;
    (*dist)[src] = 0;
    decreaseKey(minHeap, src, (*dist)[src]);
    minHeap->size = V;
    while (!isEmpty(minHeap))
    {
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; 
 
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
 
            if (isInMinHeap(minHeap, v) && (*dist)[u] != INT_MAX && 
                                          pCrawl->weight + (*dist)[u] < (*dist)[v])
            {
                (*dist)[v] = (*dist)[u] + pCrawl->weight;
 
                decreaseKey(minHeap, v, (*dist)[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
}
 
class TempEdge {
public:
    int s;
    int t;
    int l;
    TempEdge(int si, int ti, int li);
};
TempEdge::TempEdge(int si, int ti, int li)
{
    s = si;
    t = ti;
    l = li;
}

void combination_util(vector<int> arr, int data[], int start, int end, int index, int r, vector< vector<int> > *combs)
{
    if (index == r)
    {
	vector<int> temp;
        for (int j=0; j<r; j++)
            temp.push_back(data[j]);
	(*combs).push_back(temp);
        return;
    }

    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combination_util(arr, data, i+1, end, index+1, r, combs);
    }
}

void all_combination(vector<int> arr, int n, int r, vector< vector<int> > *combs)
{
    int data[r];
    combination_util(arr, data, 0, n-1, 0, r, combs);
}
 
int main()
{
    int n;
    cin >> n;
    vector<int> arr;
    for(int i=0; i<n; i++)
	arr.push_back(i);
    vector< vector<int> > combs;
    all_combination(arr, n, 3, &combs);
    vector<TempEdge> edges;
    int si, ti, li;
    for(int i=0; i<n-1; i++)
    {
	cin >> si >> ti >> li;
	TempEdge te = TempEdge(si-1, ti-1, li);
	edges.push_back(te);
    }
    int q;
    cin >> q;
    int edge_num, new_l;
    for(int i=0; i<q; i++)
    {
	cin >> edge_num >> new_l;
	edges[edge_num-1].l = new_l;
	struct Graph* graph = createGraph(n);
	for(int j=0; j<edges.size(); j++)
		addEdge(graph, edges[j].s, edges[j].t, edges[j].l);
	double sum = 0;
	for(int c=0; c<combs.size(); c++)
	{
		vector<int> dist1(n);
		dijkstra(graph, &dist1, combs[c][0]);
		sum += dist1[combs[c][1]];
		sum += dist1[combs[c][2]];
		vector<int> dist2(n);
		dijkstra(graph, &dist2, combs[c][1]);
		sum += dist2[combs[c][2]];
	}
	
	cout << setiosflags(ios::fixed) << std::setprecision(6) << (double)((double)sum/(double)(combs.size())) <<endl;
    }
}
