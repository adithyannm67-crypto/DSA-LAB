#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct Node
{
    int data;
    int visited;
    struct Node **neighbours;
    int neighbourCount;
    struct Node *pred;
    int distance;
} Node;

struct Queue
{
    Node *arr[MAX];
    int front;
    int rear;
};

struct Queue Q = {.front = -1, .rear = -1};
int isEmpty()
{
    return Q.front == -1 || Q.front > Q.rear;
}

void enqueue(Node *value)
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

Node *dequeue()
{
    if (Q.front == -1 || Q.front > Q.rear)
    {
        printf("Queue Underflow\n");
        return NULL;
    }

    Node *value = Q.arr[Q.front];
    Q.front++;

    return value;
}

Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->visited = 0;
    newNode->neighbours = NULL;
    newNode->neighbourCount = 0;
    newNode->pred = NULL;
    newNode->distance = 0;
    return newNode;
}

void addNeighbour(Node *node, Node *neighbour)
{
    node->neighbourCount++;
    node->neighbours = (Node **)realloc(node->neighbours, node->neighbourCount * sizeof(Node *));
    node->neighbours[node->neighbourCount - 1] = neighbour;
}

void CreateGraph(Node **nodes)
{
    addNeighbour(nodes[1], nodes[6]);
    addNeighbour(nodes[7], nodes[2]);
    addNeighbour(nodes[9], nodes[10]);
    addNeighbour(nodes[9], nodes[11]);
    addNeighbour(nodes[11], nodes[12]);
    addNeighbour(nodes[8], nodes[10]);
    addNeighbour(nodes[10], nodes[12]);
    addNeighbour(nodes[12], nodes[13]);

    addNeighbour(nodes[15], nodes[16]);

    addNeighbour(nodes[17], nodes[18]);

    addNeighbour(nodes[0], nodes[19]);
    addNeighbour(nodes[19], nodes[20]);
    addNeighbour(nodes[20], nodes[1]);

    addNeighbour(nodes[0], nodes[22]);
    addNeighbour(nodes[22], nodes[4]);

    addNeighbour(nodes[6], nodes[23]);
    addNeighbour(nodes[23], nodes[7]);

    addNeighbour(nodes[7], nodes[26]);
    addNeighbour(nodes[26], nodes[8]);

    addNeighbour(nodes[2], nodes[21]);
    addNeighbour(nodes[21], nodes[3]);

    addNeighbour(nodes[3], nodes[24]);
    addNeighbour(nodes[24], nodes[27]);
    addNeighbour(nodes[27], nodes[9]);

    addNeighbour(nodes[4], nodes[25]);
    addNeighbour(nodes[25], nodes[5]);

    addNeighbour(nodes[4], nodes[28]);
    addNeighbour(nodes[28], nodes[30]);
    addNeighbour(nodes[30], nodes[14]);

    addNeighbour(nodes[14], nodes[32]);
    addNeighbour(nodes[32], nodes[15]);

    addNeighbour(nodes[5], nodes[29]);
    addNeighbour(nodes[29], nodes[30]);

    addNeighbour(nodes[16], nodes[31]);
    addNeighbour(nodes[31], nodes[17]);
}

void printGraph(Node **nodes, int n)
{
    printf("\nGraph:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d -> ", nodes[i]->data);

        for (int j = 0; j < nodes[i]->neighbourCount; j++)
        {
            printf("%d ", nodes[i]->neighbours[j]->data);
        }

        printf("\n");
    }
}

Node *BFS(Node **nodes, int n, int start)
{
    Q.front = -1;
    Q.rear = -1;

    Node *START = NULL;

    for (int i = 0; i < n; i++)
    {
        if (nodes[i]->data == start)
        {
            START = nodes[i];
        }
        nodes[i]->visited = 0;
        nodes[i]->pred = NULL;
        nodes[i]->distance = 0;
    }
    START->visited = 1;
    enqueue(START);
    while (!isEmpty())
    {
        Node *v = dequeue();
        for (int i = 0; i < v->neighbourCount; i++)
        {
            Node *u = v->neighbours[i];
            if (!u->visited)
            {

                u->pred = v;
                u->visited = 1;
                u->distance = v->distance + 1;
                if (u->data == 13)
                {
                    return u;
                }

                enqueue(u);
            }
        }
    }

    return NULL;
}

int main()
{
    Node *nodes[100];
    int MAX_NODES = 33;

    for (int i = 0; i < MAX_NODES; i++)
    {
        nodes[i] = createNode(i);
    }

    CreateGraph(nodes);

    Node *end = BFS(nodes, MAX_NODES, 0);
    if (end != NULL)
    {
        Node PATH[100];
        int pathLength = 0;
        Node *p = end;
        printf("PATH\n");

        while (p != NULL)
        {
            PATH[pathLength++] = *p;
            p = p->pred;
        }

        for (int i = pathLength - 1; i >= 0; i--)
        {
            printf("%d ", PATH[i].data);
            if (i > 0)
            {
                printf("-> ");
            }
        }

        printf("\n\nDistance from 0 to 13: %d\n", end->distance);
    }
    else
    {
        printf("No path found.\n");
    }
}
