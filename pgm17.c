#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct STATE
{
    int v10, v7, v4;
    struct STATE *prev;

} STATE;

STATE *visitedStates[MAX];
int visitedStatesCount = 0;

int isStatePresent(STATE state)
{
    for (int i = 0; i < visitedStatesCount; i++)
    {
        if (visitedStates[i] != NULL && visitedStates[i]->v10 == state.v10 && visitedStates[i]->v7 == state.v7 && visitedStates[i]->v4 == state.v4)
        {
            return 1;
        }
    }
    return 0;
}

struct Queue
{
    STATE *arr[MAX];
    int front;
    int rear;
};

struct Queue Q = {.front = -1, .rear = -1};
int isEmpty();
void enqueue(STATE *value);
STATE *dequeue();

void updateLists(STATE *state)
{
    if (visitedStatesCount < MAX)
    {
        visitedStates[visitedStatesCount++] = state;
        enqueue(state);
    }
    else
    {
        printf("Visited states list is full. Cannot add new state.\n");
    }
}

int *getDestination(STATE *current, STATE *New, int *destination);
int getCapacity(int *destination, STATE *current);
int *getSource(STATE *current, STATE *New, int *source);
int isPouringPossible(int *source, int *destination, STATE *current);

STATE *POUR(int *source, int *destination, STATE *current)
{
    if (!isPouringPossible(source, destination, current))
    {
        return NULL;
    }
    STATE *New = malloc(sizeof(STATE));
    if (New == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    New->v10 = current->v10;
    New->v7 = current->v7;
    New->v4 = current->v4;
    New->prev = current;

    int *ogDestination = getDestination(current, New, destination);
    int capacityOfDestination = getCapacity(destination, current);
    int *ogSource = getSource(current, New, source);

    if (ogDestination == NULL || ogSource == NULL || capacityOfDestination == 0)
    {
        printf("Invalid source or destination \n");
        free(New);
        return NULL;
    }

    *ogDestination += *ogSource;

    if (*ogDestination > capacityOfDestination)
    {
        int excess = *ogDestination - capacityOfDestination;
        *ogDestination = capacityOfDestination;
        *ogSource = excess;
    }
    else
    {
        *ogSource = 0;
    }

    return New;
}

void validateNewState(STATE *newState)
{
    if (newState != NULL)
    {
        if (!isStatePresent(*newState))
        {
            updateLists(newState);
        }
        else
            free(newState);
    }
}

STATE *MakeAMove(STATE *current)
{

    updateLists(current);

    while (!isEmpty())
    {
        STATE *temp = dequeue();
        if (temp != NULL)
        {
            if (temp->v7 == 2 || temp->v4 == 2)
            {

                return temp;
            }

            int *vessels[] = {&temp->v10, &temp->v7, &temp->v4};

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (i != j)
                    {
                        STATE *newState = POUR(vessels[i], vessels[j], temp);
                        validateNewState(newState);
                    }
                }
            }
        }
    }

    return NULL;
}

int main()
{
    STATE initialState = {0, 7, 4, NULL};

    STATE *finalState = MakeAMove(&initialState);

    if (finalState == NULL)
    {
        printf("No solution found.\n");
        return 0;
    }

    printf("Final State: v10=%d, v7=%d, v4=%d\n", finalState->v10, finalState->v7, finalState->v4);

    int pathLength = 0;
    STATE PATH[MAX];
    STATE *p = finalState;

    printf("Path to solution:\n");

    while (p != NULL)
    {
        PATH[pathLength++] = *p;
        p = p->prev;
    }

    for (int i = pathLength - 1; i >= 0; i--)
    {
        printf("(%d, %d, %d) ", PATH[i].v10, PATH[i].v7, PATH[i].v4);
        if (i > 0)
        {
            printf("-> ");
        }
    }

    return 0;
}

int *getDestination(STATE *current, STATE *New, int *destination)
{

    if (destination == &current->v10)
    {
        return &New->v10;
    }
    else if (destination == &current->v7)
    {
        return &New->v7;
    }
    else if (destination == &current->v4)
    {
        return &New->v4;
    }
    else
    {
        return NULL;
    }
}

int getCapacity(int *destination, STATE *current)
{
    if (destination == &current->v10)
    {
        return 10;
    }
    else if (destination == &current->v7)
    {
        return 7;
    }
    else if (destination == &current->v4)
    {
        return 4;
    }
    return 0;
}

int *getSource(STATE *current, STATE *New, int *source)
{
    if (source == &current->v10)
    {
        return &New->v10;
    }
    else if (source == &current->v7)
    {
        return &New->v7;
    }
    else if (source == &current->v4)
    {
        return &New->v4;
    }
    else
    {
        return NULL;
    }
}

int isPouringPossible(int *source, int *destination, STATE *current)
{
    if (*source == 0)
    {
        return 0;
    }
    if (*destination == 10 && destination == &current->v10)
    {
        return 0;
    }
    if (*destination == 7 && destination == &current->v7)
    {
        return 0;
    }
    if (*destination == 4 && destination == &current->v4)
    {
        return 0;
    }
    return 1;
}

int isEmpty()
{
    return Q.front == -1 || Q.front > Q.rear;
}

void enqueue(STATE *value)
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

STATE *dequeue()
{
    if (Q.front == -1 || Q.front > Q.rear)
    {
        printf("Queue Underflow\n");
        return NULL;
    }

    STATE *value = Q.arr[Q.front];
    Q.front++;

    return value;
}
