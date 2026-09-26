#include <stdio.h>

int isPossible(int pages[], int n, int s, int mid)
{
    int students = 1, currentPages = 0;
    for (int i = 0; i < n; i++)
    {
        if (pages[i] > mid)
            return 0;
        if (currentPages + pages[i] <= mid)
        {
            currentPages += pages[i];
        }
        else
        {
            students++;
            currentPages = pages[i];
            if (students > s)
                return 0;
        }
    }
    return 1;
}

int allocateBooks(int pages[], int n, int s)
{
    int low = pages[0], high = 0;
    for (int i = 0; i < n; i++)
    {
        if (pages[i] > low)
            low = pages[i];
        high += pages[i];
    }

    int answer = high;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (isPossible(pages, n, s, mid))
        {
            answer = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return answer;
}

void printAllocation(int pages[], int n, int maxPages)
{
    int studentNo = 1, curr = 0, start = 0;
    
    for (int i = 0; i < n; i++)
    {
        if (curr + pages[i] > maxPages)
        {
            printf("Student %d: [", studentNo);
            for (int j = start; j < i; j++)
            {
                printf("%d", pages[j]);
                if (j != i - 1)
                    printf(", ");
            }
            printf("] -> %d pages\n", curr);
            studentNo++;
            start = i;
            curr = pages[i];
        }
        else
        {
            curr += pages[i];
        }
    }
    printf("Student %d: [", studentNo);
    for (int j = start; j < n; j++)
    {
        printf("%d", pages[j]);
        if (j != n - 1)
            printf(", ");
    }
    printf("] -> %d pages\n", curr);
}

int main()
{
    int n;
    int s;

    printf("Enter the number of books: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of books\n");
        return 1;
    }

    int pages[100];
    printf("Enter the pages in each book: ");
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &pages[i]) != 1 || pages[i] <= 0)
        {
            printf("Invalid page count\n");
            return 1;
        }
    }

    printf("\n\nEnter the no. of students: ");
    if (scanf("%d", &s) != 1 || s <= 0)
    {
        printf("Invalid number of students\n");
        return 1;
    }

    if (s > n)
    {
        printf("Allocation not possible (more students than books)\n");
        return 0;
    }

    int answer = allocateBooks(pages, n, s);

    printf("\n");
  
    printAllocation(pages, n, answer);

    return 0;
}