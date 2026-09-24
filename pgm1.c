#include <stdio.h>

void allocateBooks(int *books, int n, int s, int *result)
{
    int sum = 0;

    for (int i = 0; i < n; i++)
        sum += books[i];

    int low = books[n - 1], high = sum;
    int mid, ans = -1;

    while (low <= high)
    {
        mid = (low + high) / 2;

        int students = 1;
        int currentSum = 0;

        for (int i = 0; i < n; i++)
        {
            if (currentSum + books[i] > mid)
            {
                students++;
                currentSum = books[i];
            }
            else
            {
                currentSum += books[i];
            }
        }

        if (students <= s)
        {
            ans = mid;
            high = mid - 1;
        }
        else
            low = mid + 1;
    }

    /* Store allocation */
    int student = 0, currentSum = 0;

    for (int i = 0; i < n; i++)
    {
        if (currentSum + books[i] > ans)
        {
            result[student++] = currentSum;
            currentSum = books[i];
        }
        else
        {
            currentSum += books[i];
        }
    }

    result[student++] = currentSum;

    printf("\nAllocation:\n");

    for (int i = 0; i < student; i++)
        printf("Student %d: %d pages\n", i + 1, result[i]);
}

int main()
{
    int n, s;

    printf("Enter number of books: ");
    scanf("%d", &n);

    int books[100];
    int result[100];

    printf("Enter pages of books in sorted order:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &books[i]);

    printf("Enter number of students: ");
    scanf("%d", &s);

    allocateBooks(books, n, s, result);

    return 0;
}