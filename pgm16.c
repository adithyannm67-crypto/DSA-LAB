#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define INFINITY 9999

typedef struct VERTEX
{
    int value;
    int d;
    struct VERTEX *pred;
} VERTEX;
typedef struct Edge
{
    int src;
    int dest;
    int weight;
} Edge;

typedef struct GRAPH
{
    VERTEX vertices[MAX];
    Edge edges[MAX];
    int numOfVertices;
    int numOfEdges;
} GRAPH;

GRAPH G = {
    .vertices = {
        {.value = 0,
         .d = INFINITY,
         .pred = NULL},
        {.value = 1,
         .d = INFINITY,
         .pred = NULL},
        {.value = 2,
         .d = INFINITY,
         .pred = NULL},
        {.value = 3,
         .d = INFINITY,
         .pred = NULL},
        {.value = 4,
         .d = INFINITY,
         .pred = NULL},
        {.value = 5,
         .d = INFINITY,
         .pred = NULL},
        {.value = 6,
         .d = INFINITY,
         .pred = NULL},
        {.value = 7,
         .d = INFINITY,
         .pred = NULL},
        {.value = 8,
         .d = INFINITY,
         .pred = NULL},
        {.value = 9,
         .d = INFINITY,
         .pred = NULL},
        {.value = 10,
         .d = INFINITY,
         .pred = NULL},
        {.value = 11,
         .d = INFINITY,
         .pred = NULL},
        {.value = 12,
         .d = INFINITY,
         .pred = NULL},
        {.value = 13,
         .d = INFINITY,
         .pred = NULL},
        {.value = 14,
         .d = INFINITY,
         .pred = NULL},
        {.value = 15,
         .d = INFINITY,
         .pred = NULL},
        {.value = 16,
         .d = INFINITY,
         .pred = NULL},
        {.value = 17,
         .d = INFINITY,
         .pred = NULL},
        {.value = 18,
         .d = INFINITY,
         .pred = NULL}},
    .edges = {{.src = 0, .dest = 1, .weight = 2}, {.src = 1, .dest = 6, .weight = 0}, {.src = 6, .dest = 7, .weight = 1}, {.src = 7, .dest = 2, .weight = 0}, {.src = 2, .dest = 3, .weight = 1}, {.src = 3, .dest = 9, .weight = 2}, {.src = 9, .dest = 10, .weight = 0}, {.src = 9, .dest = 11, .weight = 0}, {.src = 11, .dest = 12, .weight = 0}, {.src = 10, .dest = 12, .weight = 0}, {.src = 12, .dest = 13, .weight = 0}, {.src = 7, .dest = 8, .weight = 1}, {.src = 0, .dest = 4, .weight = 1}, {.src = 4, .dest = 5, .weight = 1}, {.src = 5, .dest = 16, .weight = 1}, {.src = 16, .dest = 17, .weight = 1}, {.src = 17, .dest = 18, .weight = 1}, {.src = 4, .dest = 14, .weight = 1}, {.src = 14, .dest = 15, .weight = 1}, {.src = 15, .dest = 16, .weight = 1}, {.src = 8, .dest = 10, .weight = 0}},
    .numOfVertices = 19,
    .numOfEdges = 21};

typedef struct HEAP
{
    VERTEX *vertices[MAX];
    int heapSize;
} HEAP;

HEAP PRIORITY_QUEUE;

VERTEX *EXTRACT_MIN();
void INSERT_TO_HEAP(VERTEX *v);
void MIN_HEAPIFY(int i);
void HEAP_DECREASE_KEY(int u_value, int v_value, int w);
int HEAP_SEARCH(int v);

VERTEX *VISITED_VERTICES[MAX];
int numOfVisitedVeritices = 0;

VERTEX *GETNODE(int value)
{
    for (int i = 0; i < G.numOfVertices; i++)
    {
        if (G.vertices[i].value == value)
        {
            return &G.vertices[i];
        }
    }
    return NULL;
}

void DIJKSTRA(int s)
{
    PRIORITY_QUEUE.heapSize = 0;
    VERTEX *START = NULL;
    for (int i = 0; i < G.numOfVertices; i++)
    {
        G.vertices[i].d = INFINITY;
        G.vertices[i].pred = NULL;
    }

    START = GETNODE(s);
    START = GETNODE(s);

    if (START == NULL)
    {
        printf("Source vertex not found.\n");
        return;
    }
    START->d = 0;
    START->pred = NULL;

    for (int i = 0; i < G.numOfVertices; i++)
    {
        INSERT_TO_HEAP(&G.vertices[i]);
    }

    numOfVisitedVeritices = 0;

    while (PRIORITY_QUEUE.heapSize != 0)
    {

        VERTEX *u = EXTRACT_MIN();
        VISITED_VERTICES[numOfVisitedVeritices++] = u;
        for (int i = 0; i < G.numOfEdges; i++)
        {
            if (G.edges[i].src == u->value)
            {
                HEAP_DECREASE_KEY(G.edges[i].src, G.edges[i].dest, G.edges[i].weight);
            }
        }
    }
}

int main()
{
    DIJKSTRA(0);

    VERTEX *destination = GETNODE(13);

    if (destination->d == INFINITY)
    {
        printf("There is no path from source vertex 0 to vertex 13.\n");
        return 0;
    }
    printf("Shortest distance from source vertex 0 to vertex 13: %d\n", destination->d);

    int pathLength = 0;
    VERTEX *PATH[MAX];

    printf("Shortest path from source vertex 0 to vertex 13: ");
    VERTEX *current = destination;
    while (current != NULL)
    {
        PATH[pathLength++] = current;
        current = current->pred;
    }
    for (int i = pathLength - 1; i >= 0; i--)
    {
        printf("%d", PATH[i]->value);
        if (i > 0)
        {
            printf(" -> ");
        }
    }
    printf("\n");
}

void MIN_HEAPIFY(int i)
{
    int l = 2 * i + 1, r = 2 * i + 2, smallest = i;

    if (l < PRIORITY_QUEUE.heapSize && PRIORITY_QUEUE.vertices[l]->d < PRIORITY_QUEUE.vertices[smallest]->d)
    {
        smallest = l;
    }

    if (r < PRIORITY_QUEUE.heapSize && PRIORITY_QUEUE.vertices[r]->d < PRIORITY_QUEUE.vertices[smallest]->d)
    {
        smallest = r;
    }

    if (smallest != i)
    {
        VERTEX *temp = PRIORITY_QUEUE.vertices[i];
        PRIORITY_QUEUE.vertices[i] = PRIORITY_QUEUE.vertices[smallest];
        PRIORITY_QUEUE.vertices[smallest] = temp;

        MIN_HEAPIFY(smallest);
    }
}

VERTEX *EXTRACT_MIN()
{
    if (PRIORITY_QUEUE.heapSize < 1)
    {
        printf("\nHEAP UNDERFLOW\n");
    }
    VERTEX *min = PRIORITY_QUEUE.vertices[0];

    PRIORITY_QUEUE.vertices[0] = PRIORITY_QUEUE.vertices[PRIORITY_QUEUE.heapSize - 1];
    PRIORITY_QUEUE.heapSize--;

    MIN_HEAPIFY(0);
    return min;
}
void INSERT_TO_HEAP(VERTEX *v)
{
    if (PRIORITY_QUEUE.heapSize == MAX)
    {
        printf("\nPRIORITY QUEUE FULL\n");
        return;
    }
    PRIORITY_QUEUE.vertices[PRIORITY_QUEUE.heapSize++] = v;
    int i = PRIORITY_QUEUE.heapSize - 1;
    int parent;

    while (i > 0)
    {
        parent = (i - 1) / 2;
        if (PRIORITY_QUEUE.vertices[parent]->d <= PRIORITY_QUEUE.vertices[i]->d)
        {
            break;
        }
        VERTEX *temp = PRIORITY_QUEUE.vertices[parent];
        PRIORITY_QUEUE.vertices[parent] = PRIORITY_QUEUE.vertices[i];
        PRIORITY_QUEUE.vertices[i] = temp;
        i = parent;
    }
}

int HEAP_SEARCH(int v)
{
    int i;
    for (i = 0; i < PRIORITY_QUEUE.heapSize; i++)
    {
        if (PRIORITY_QUEUE.vertices[i]->value == v)
        {
            return i;
        }
    }
    return -1;
}

void HEAP_DECREASE_KEY(int u_value, int v_value, int w)
{

    VERTEX *u = GETNODE(u_value);
    VERTEX *v = GETNODE(v_value);
    if (u == NULL || v == NULL)
        return;

    if (v->d > u->d + w)
    {
        v->d = u->d + w;
        v->pred = u;

        int i = HEAP_SEARCH(v_value);
        if (i == -1)
            return;

        int parent;
        while (i > 0)
        {
            parent = (i - 1) / 2;
            if (PRIORITY_QUEUE.vertices[parent]->d <= PRIORITY_QUEUE.vertices[i]->d)
            {
                break;
            }
            VERTEX *temp = PRIORITY_QUEUE.vertices[parent];
            PRIORITY_QUEUE.vertices[parent] = PRIORITY_QUEUE.vertices[i];
            PRIORITY_QUEUE.vertices[i] = temp;
            i = parent;
        }
    }
}
