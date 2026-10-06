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
    .edges = {{.src = 0, .dest = 1, .weight = 2}, {.src = 1, .dest = 6, .weight = 0}, {.src = 6, .dest = 7, .weight = 1}, {.src = 7, .dest = 2, .weight = 0}, {.src = 2, .dest = 3, .weight = 1}, {.src = 3, .dest = 9, .weight = 2}, {.src = 9, .dest = 10, .weight = 0}, {.src = 9, .dest = 11, .weight = 0}, {.src = 11, .dest = 12, .weight = 0}, {.src = 10, .dest = 12, .weight = 0}, {.src = 12, .dest = 13, .weight = 0}, {.src = 7, .dest = 8, .weight = 1}, {.src = 0, .dest = 4, .weight = 1}, {.src = 4, .dest = 5, .weight = 1}, {.src = 5, .dest = 16, .weight = 1}, {.src = 16, .dest = 17, .weight = 1}, {.src = 17, .dest = 18, .weight = 1}, {.src = 4, .dest = 14, .weight = 1}, {.src = 14, .dest = 15, .weight = 1}, {.src = 15, .dest = 16, .weight = 1}},
    .numOfVertices = 19};


typedef struct HEAP{
    VERTEX *vertices[MAX];
    int heapSize;
}HEAP;

HEAP PRIORITY_QUEUE={.heapSize=0};

VERTEX* EXTRACT_MIN();
void INSERT_TO_HEAP(VERTEX *v);
void MIN_HEAPIFY();

typedef struct Queue
{
    VERTEX *arr[MAX];
    int front;
    int rear;
}Queue;

Queue Q = {.front = -1, .rear = -1};
int isEmpty();
void enqueue(VERTEX *value);
VERTEX *dequeue();

void RELAX(VERTEX *u, VERTEX *v, int w)
{
    if (v->d > u->d + w)
    {
        v->d = u->d + w;
        v->pred = u;
    }
}

VERTEX *DIJKSTRA(int s)
{
    VERTEX *START = NULL;
    for (int i = 0; i < G.numOfVertices; i++)
    {
        if (G.vertices[i].value == s)
        {
            START = &G.vertices[i];
        }
        enqueue(&G.vertices[i]);
    }
    START->d = 0;
    START->pred = NULL;
}

int main()
{
}


VERTEX* EXTRACT_MIN();
void INSERT_TO_HEAP(VERTEX *v);
void MIN_HEAPIFY();




int isEmpty()
{
    return Q.front == -1 || Q.front > Q.rear;
}

void enqueue(VERTEX *value)
{
    if (Q.rear == MAX - 1)
    {
        printf("Queue Overflow\n");
        return;
    }

    if (Q.front == -1)
        Q.front = 0;

    Q.rear++;
    Q.arr[Q.rear] = value;
}

VERTEX *dequeue()
{
    if (Q.front == -1 || Q.front > Q.rear)
    {
        printf("Queue Underflow\n");
        return NULL;
    }

    VERTEX *value = Q.arr[Q.front];
    Q.front++;

    return value;
}
