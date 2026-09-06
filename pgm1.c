#include <stdio.h>

void allocateBooks(int *books, int n, int s, int *result)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += books[i];
    }
    int low = books[n - 1],high = sum, mid, ans = -1;

    

    while (low <= high)
    {
        int i=0;
        mid = (low + high) / 2;
        int requiredStudents = 1, currentSum = 0;

        for (int i = 0; i < n; i++)
        {
            if (currentSum + books[i] > mid)
            {
                requiredStudents++;
                currentSum = books[i];
            }
            else
            {
                currentSum += books[i];
            }
            result[i++]=currentSum;
        }

        if (requiredStudents <= s)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
}

int main()
{
    int books[6] = {10, 20, 30, 40, 50, 60};

    int s = 4;

    int result[4];

    allocateBooks(books, 6, s, result);

    for(int i=0;i<4;i++){
        printf("%d  ",result[i]);
    }

    return 0;
}