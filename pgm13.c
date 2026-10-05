#include <stdio.h>

#define MAX 100
int N;

typedef struct Customer
{
    int category;
    int token;
    int priority;
} Customer;

Customer A[MAX];
int size = 0;

typedef struct Heap
{
        Customer A[MAX];
        int size;
        int Max;
} Heap;

Heap Customers;

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

    if (Customers.size >= Customers.Max)
    {
        printf("Queue is full\n");
        return;
    }
    Customers.A[Customers.size].token = token;

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

    Customers.A[Customers.size].category = category;

    
    int i = Customers.size;
    int p = (i - 1) / 2;
    while (i > 0 && hasPriority(Customers.A[i], Customers.A[p]))
    {
        Customer temp = Customers.A[i];
        Customers.A[i] = Customers.A[p];
        Customers.A[p] = temp;
        i = p;
        p = (i - 1) / 2;
    }
    Customers.size++;
}

void HEAP_DELETE()
{
    Customer c;
    if (size < 0)
    {
       printf("Queue is empty\n");
        c.token = -1;
    }    else
    {
        c = Customers.A[0];

        Customers.A[0] = Customers.A[--Customers.size];
        int i = 0;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        while (l < Customers.size)
        {
            int min = l;
            if (r < size && hasPriority(Customers.A[r], Customers.A[l]))
                min = r;
            if (!hasPriority(Customers.A[min], Customers.A[i]))
                break;
            Customer temp = Customers.A[i];
            Customers.A[i] = Customers.A[min];
            Customers.A[min] = temp;
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
}void PRINT_TREE()
{
    int index = 0;
    int level = 0;
    int nodes = 1;

    while (index < Customers.size)
    {
        printf("\nLevel %d: ", level);

        for (int i = 0; i < nodes && index < Customers.size; i++)
        {
            printf("(%d,%d) ",
                   Customers.A[index].token,
                   Customers.A[index].category);

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
    Customers.Max=N;
    Customers.size=0;
    
    int token=1;
    while (1)
    {
        printf("\n\n===== GENERAL POST OFFICE =====\n");
        printf("1. Serve customer\n");
        printf("2. Current customer\n");
        printf("3. Number of customers waiting\n");
        printf("4. Display heap\n");
        printf("5. Exit\n");
        printf("6. Add Customer to heap\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            if (Customers.size == 0)
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
            if (Customers.size == 0)
            {
                printf("\nNo customers waiting.\n");
            }
            else
            {
                printf("\nCurrent customer:\n");
                printf("Token    : %d\n", Customers.A[0].token);
                printf("Category : %d\n", Customers.A[0].category);
            }

            break;
        }

        case 3:
            printf("\nCustomers waiting: %d\n", Customers.size);
            break;

        case 4:
            printf("\n--- MAX HEAP ---\n");
            PRINT_TREE();
            break;

        case 5:
            printf("\nExiting...\n");
            return 0;
        case 6:
            HEAP_INSERT(++token);
            break;
        default:
            printf("\nInvalid choice.\n");
        }
    }
    return 0;
}


