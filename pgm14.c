/*

14. PRIORITY QUEUE — GENERAL POST OFFICE

The General Post Office wishes to give preferential treatment to its customers.

There are four categories of customers:

1. Defence personnel
2. Differently abled persons
3. Senior citizens
4. Normal persons

Customers come to the post office, get their job done, and leave.

As a customer enters the post office, they proceed to a token machine which prompts for their category and then issues a token bearing a number in increasing order of arrival time.

Customers are served according to decreasing priority:

1. Differently abled persons
2. Senior citizens
3. Defence personnel
4. Normal persons

Customers within the same category are served in order of arrival.

Implement this scenario for N customers.

Assumption:
There is only one service counter in the post office.


*/

#include <stdio.h>

#define MAX 100

typedef struct Customer
{
    int category;
    int token;
    int priority;
} Customer;

Customer A[MAX];
int size = 0;

#define PRIORITY_FOR_DIFFERNTLY_ABLED 4
#define PRIORITY_FOR_SENIOR_CITIZENS 3
#define PRIORITY_FOR_DEFENCE_PERSONNEL 2
#define PRIORITY_FOR_NORMAL_PERSONS 1

int hasPriority(Customer a, Customer b)
{
    if (b.category < a.category)
        return 1;
    if (b.category == a.category && a.token < b.token)
        return 1;
    else
        return 0;
}

void HEAP_INSERT(int token)
{

    if (size >= MAX)
    {
        printf("Queue is full\n");
        return;
    }
    A[size].token = token;

    printf("\n4. Differently Abled Persons");
    printf("\n3. Senior Citizens");
    printf("\n2. Defence Personnel");
    printf("\n1. Normal Persons");

    int category;
    printf("\nEnter the category of customer: ");
    scanf("%d", &category);

    if (category > 4 || category < 1)
    {
        printf("\nInvalid category\n");
        return;
    }

    A[size].category = category;

    A[size].priority = A[size].category * A[size].token;

    int i = size;
    int p = (i - 1) / 2;
    while (i > 0 && hasPriority(A[i], A[p]))
    {
        Customer temp = A[i];
        A[i] = A[p];
        A[p] = temp;
        i = p;
        p = (i - 1) / 2;
    }
    size++;
}

void HEAP_DELETE()
{
    Customer c;
    if (size < 0)
    {
        printf("Queue is empty\n");
        c.token = -1;
    }
    else
    {
        c = A[0];

        A[0] = A[--size];
        int i = 0;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        while (l < size)
        {
            int min = l;
            if (r < size && hasPriority(A[r], A[l]))
                min = r;
            if (!hasPriority(A[min], A[i]))
                break;
            Customer temp = A[i];
            A[i] = A[min];
            A[min] = temp;
            i = min;
            l = 2 * i + 1;
            r = 2 * i + 2;
        }
    }
    if (c.token != -1)
    {
        printf("\nCustomer served:\n");
        printf("Token    : %d\n", c.token);
        printf("Category : %d\n", c.category);
    }
    return;
}
void PRINT_HEAP()
{

    for (int i = 0; i < size; i++)
    {
        printf("%d ", A[i].token);
    }
    printf("\n");
}
void PRINT_TREE1()
{
    int level = 0;
    int index = 0;
    int nodes = 1;

    while (index < size)
    {
        printf("Level %d: ", level);

        for (int i = 0; i < nodes && index < size; i++)
        {
            printf("%d ", A[index].token);
            index++;
        }

        printf("\n");

        nodes = nodes * 2;
        level++;
    }
}
void PRINT_TREE()
{
    int index = 0;
    int level = 0;
    int nodes = 1;

    while (index < size)
    {
        printf("\nLevel %d: ", level);

        for (int i = 0; i < nodes && index < size; i++)
        {
            printf("(%d,%d) ",
                   A[index].token,
                   A[index].category);

            index++;
        }

        level++;
        nodes = nodes * 2;
    }

    printf("\n");
}
int main()
{
    int N, choice;
    printf("Enter the number of customers: ");
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
    {
        HEAP_INSERT(i);
    }
    printf("\n======MAX HEAP======\n");
    PRINT_HEAP();
    PRINT_TREE();
    while (1)
    {
        printf("\n\n===== GENERAL POST OFFICE =====\n");
        printf("1. Serve customer\n");
        printf("2. Current customer\n");
        printf("3. Number of customers waiting\n");
        printf("4. Display queue\n");
        printf("5. Display heap\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            if (size == 0)
            {
                printf("\nNo customers waiting.\n");
            }
            else
            {
                HEAP_DELETE();
            }

            break;
        }

        case 2:
        {
            if (size == 0)
            {
                printf("\nNo customers waiting.\n");
            }
            else
            {
                printf("\nCurrent customer:\n");
                printf("Token    : %d\n", A[0].token);
                printf("Category : %d\n", A[0].category);
            }

            break;
        }

        case 3:
            printf("\nCustomers waiting: %d\n", size);
            break;

        case 5:
            printf("\n--- MAX HEAP ---\n");
            PRINT_TREE();
            break;

        case 6:
            printf("\nExiting...\n");
            break;

        default:
            printf("\nInvalid choice.\n");
        }
    }
    return 0;
}