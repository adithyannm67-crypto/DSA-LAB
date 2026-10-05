#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct STATE
{
    int v10, v7, v4;
    struct STATE *prev;
} STATE;

STATE *States[MAX];

int isStatePresent(STATE state)
{
    for (int i = 0; i < MAX; i++)
    {
        if (States[i] != NULL && States[i]->v10 == state.v10 && States[i]->v7 == state.v7 && States[i]->v4 == state.v4)
        {
            return 1;
        }
    }
    return 0;
}

STATE *POUR(int *source, int *destination, STATE *current)
{
    if (*source == 0)
    {
        return NULL;
    }
    if (*destination == 10 && destination == &current->v10)
    {
        return NULL;
    }
    if (*destination == 7 && destination == &current->v7)
    {
        return NULL;
    }
    if (*destination == 4 && destination == &current->v4)
    {
        return NULL;
    }
    struct STATE *New = (STATE *)malloc(sizeof(STATE));
    New->v10 = current->v10;
    New->v7 = current->v7;
    New->v4 = current->v4;
    New->prev = current;
    if (destination == &current->v10)
    {

        New->v10 += *source;

        if (New->v10 > 10)
        {
            int excess = New->v10 - 10;
            New->v10 = 10;
            if (&current->v7 == source)
            {
                New->v7 = excess;
            }
            else if (&current->v4 == source)
            {
                New->v4 = excess;
            }
        }
        else
        {
            if (&current->v7 == source)
            {
                New->v7 = 0;
            }
            else if (&current->v4 == source)
            {
                New->v4 = 0;
            }
        }
    }
    else if (destination == &current->v7)
    {

        New->v7 += *source;

        if (New->v7 > 7)
        {
            int excess = New->v7 - 7;
            New->v7 = 7;
            if (&current->v10 == source)
            {
                New->v10 = excess;
            }
            else if (&current->v4 == source)
            {
                New->v4 = excess;
            }
        }
        else
        {
            if (&current->v10 == source)
            {
                New->v10 = 0;
            }
            else if (&current->v4 == source)
            {
                New->v4 = 0;
            }
        }
    }
    else if (destination == &current->v4)
    {

        New->v4 += *source;

        if (New->v4 > 4)
        {
            int excess = New->v4 - 4;
            New->v4 = 4;
            if (&current->v10 == source)
            {
                New->v10 = excess;
            }
            else if (&current->v7 == source)
            {
                New->v7 = excess;
            }
        }
        else
        {
            if (&current->v10 == source)
            {
                New->v10 = 0;
            }
            else if (&current->v7 == source)
            {
                New->v7 = 0;
            }
        }
    }

    if (!isStatePresent(*New))
    {
        for (int i = 0; i < MAX; i++)
        {
            if (States[i] == NULL)
            {
                States[i] = New;
                break;
            }
        }
    }
    else
    {
        free(New);
        return NULL;
    }
    return New;
}

STATE *MakeAMove(STATE *current)
{


    if (current->v7 == 2 || current->v4 == 2)
    {
        printf("Solution Found\n");
        return current;
    }

    if (current->v10 > 0)
    {
        STATE *newState = POUR(&current->v10, &current->v7, current);
        if (newState != NULL)
        {
            return MakeAMove(newState);
        }
        newState = POUR(&current->v10, &current->v4, current);
        if (newState != NULL)
        {
            return MakeAMove(newState);
        }
    }

    if (current->v7 > 0)
    {
        STATE *newState = POUR(&current->v7, &current->v10, current);
        if (newState != NULL)
        {
            return MakeAMove(newState);
        }
        newState = POUR(&current->v7, &current->v4, current);
        if (newState != NULL)
        {
            return MakeAMove(newState);
        }
    }

    if (current->v4 > 0)
    {
        STATE *newState = POUR(&current->v4, &current->v10, current);
        if (newState != NULL)
        {
            return MakeAMove(newState);
        }
        newState = POUR(&current->v4, &current->v7, current);
        if (newState != NULL)
        {
            return MakeAMove(newState);
        }
    }

    return NULL;
}

int main()
{
    STATE initialState = {0, 7, 4, NULL};
        States[0] = &initialState;

    STATE *finalState = MakeAMove(&initialState);

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
