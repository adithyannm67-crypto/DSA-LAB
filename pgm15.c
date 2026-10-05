/*
15. MERGE K SORTED LISTS USING A HEAP

Merge K sorted lists into a single sorted list using a heap.

Use a min-heap to keep track of the smallest element from each list.

Repeatedly:

1. Extract the smallest element.
2. Insert the next element from the corresponding list into the heap.
3. Continue until all lists are merged.


16. ROBOT MAZE — MINIMUM-COST PATH

Our department owns a robot DotSlash and you arrange a “Robo-show” to showcase its maze-solving capability.

At one instant of the show, the robot is currently at a point as shown in Figure 3.

The robot wants to reach the charging source.

Since the robot has only a few units of charge left in its battery, the goal is to make sure that it consumes the least amount of charge in its journey.

Assumption:
The charge consumed is directly proportional to the distance traversed.

Task:
Help DotSlash find a path to the charging point while minimizing battery power consumed.

*/
#include <stdio.h>

#define MAX 100

typedef struct HEAP
{
    int A[MAX];
    int size, length;

} HEAP;

HEAP MIN_HEAPIFY(HEAP H, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (left < H.size && H.A[left] < H.A[smallest])
        smallest = left;
    if (right < H.size && H.A[right] < H.A[smallest])
        smallest = right;

    if (smallest != i)
    {
        int temp = H.A[i];
        H.A[i] = H.A[smallest];
        H.A[smallest] = temp;
        return MIN_HEAPIFY(H, smallest);
    }
    else
    {
        return H;
    }
}

int main()
{
    int k, size, full = 0;
    HEAP ARRAYS[100];
    printf("\nK    =   ");
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        printf("\nSIZE OF LIST    %d   =   ", i + 1);
        scanf("%d", &size);
        full += size;
        printf("\nENTER THE ELEMENTS IN ARRAY \n");
        ARRAYS[i].size = 0;
        ARRAYS[i].length = size;
        for (int j = 0; j < size; j++)
        {
            scanf("%d", &ARRAYS[i].A[ARRAYS[i].size++]);
        }
    }

    HEAP MERGED;
    MERGED.size = 0;

    for (int i = 0; i < full; i++)
    {
        int min = 999999;
        int minArrayIndex = -1;

        for (int j = 0; j < k; j++)
        {
            if (ARRAYS[j].size > 0 && ARRAYS[j].A[0] < min)
            {
                min = ARRAYS[j].A[0];
                minArrayIndex = j;
            }
        }
        int temp = ARRAYS[minArrayIndex].A[0];
        ARRAYS[minArrayIndex].A[0] = ARRAYS[minArrayIndex].A[ARRAYS[minArrayIndex].size - 1];
        ARRAYS[minArrayIndex].size--;

        MERGED.A[MERGED.size++] = temp;
        if (ARRAYS[minArrayIndex].size > 0)
            ARRAYS[minArrayIndex] = MIN_HEAPIFY(ARRAYS[minArrayIndex], 0);
    }

    printf("\nMERGED ARRAY:\n");

    for (int i = 0; i < MERGED.size; i++)
    {
        printf("%d ", MERGED.A[i]);
    }
}
