/*
18. Write a menu-driven program to read numerical data stored in a file and implement the
following algorithms for sorting the numbers in descending order. Implement each algorithm as a
separate function.
(a) Bubble sort
(b) Insertion Sort
(c) Radix Sort
(d) Merge Sort
(e) Quick Sort
Compare the number of steps involved in each method.
*/

#include <stdio.h>

int COUNTS[5] = {0};
int q_ar[100];
int b_ar[100];
int m_ar[100];

void swap(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void printArray(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void BUBBLE_SORT(int len)
{

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            COUNTS[0]++;
            if (b_ar[j] < b_ar[j + 1])
            {
                swap(b_ar, j, j + 1);
            }
        }
    }
}

int PARTISION(int p, int r)
{
    int pivot = q_ar[p];
    int left = p + 1;
    int right = r;

    while (left <= right)
    {

        while(left<=r){
            COUNTS[4]++;
            if(q_ar[left]<pivot){
                break;
            }
            left++;
        }
        while(right>p){
            COUNTS[4]++;
            if(q_ar[right]>=pivot){
                break;
            }
            right--;
        }
        
        if (left < right)
        {
            swap(q_ar, left, right);
        }
    }
    swap(q_ar, p, right);
    return right;
}

void QUICK_SORT(int p, int r)
{

    if (p < r)
    {
        int q = PARTISION(p, r);
        QUICK_SORT(p, q - 1);
        QUICK_SORT(q + 1, r);
    }
}

void merge(int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = 0;
    int temp[100];

    while (i <= mid && j <= right)
    {
        COUNTS[3]++;
        if (m_ar[i] >= m_ar[j])
        {
            temp[k++] = m_ar[i++];
        }
        else
        {
            temp[k++] = m_ar[j++];
        }
    }

    while (i <= mid)
    {

        temp[k++] = m_ar[i++];
    }

    while (j <= right)
    {

        temp[k++] = m_ar[j++];
    }

    for (int i = left, k = 0; i <= right; i++, k++)
    {
        m_ar[i] = temp[k];
    }
}

void merge_sort(int left, int right)
{

    if (left < right)
    {
        int mid = (left + right) / 2;

        merge_sort(left, mid);
        merge_sort(mid + 1, right);
        merge(left, mid, right);
    }
}
void insertion_sort(int len){
    for(int i=1; i<len; i++){
        int item = in_ar[i];
        int j = i-1;

        while(j>=0 && item>in_ar[j]){
            COUNTS[1]++;
            in_ar[j+1] = in_ar[j];
            j--;
        }
        if(j>=0){
                COUNTS[1]++;
        }

        in_ar[j+1] = item;
    }
}




int main()
{
    FILE *fp;

    fp = fopen("file.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    int num, len, i = 0;
    printf("NUMBERS READ FROM FILE : ");
    while (fscanf(fp, "%d", &num) != EOF)
    {
        q_ar[i] = num;
        b_ar[i] = num;
        m_ar[i] = num;
        i++;
        printf("%d ", num);
    }

    fclose(fp);
    len = i;

    printf("\nlength of array is %d\n", len);

    while (1)
    {
        printf("\n========= MENU ==========\n");
        printf("\n1. Bubble Sort");
        printf("\n2. Insertion Sort");
        printf("\n3. Radix Sort");
        printf("\n4. Merge Sort");
        printf("\n5. Quick Sort");
        printf("\n6. Counts");
        printf("\n7. Exit");
        printf("\nEnter your choice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        COUNTS[0]=0;
            BUBBLE_SORT(len);
            printf("BUBBLE SORT\n");
            printArray(b_ar, len);

            break;
        case 2:
        case 3:
            break;
        case 4:
            COUNTS[3]=0;
            merge_sort(0, len - 1);
            printf("MERGE SORT\n");
            printArray(m_ar, len);
            break;
        case 5:
            COUNTS[4]=0;
            QUICK_SORT(0, len - 1);
            printf("QUICK SORT \n");
            printArray(q_ar, len);
            break;
        case 6:
            printf("\n=========COUNTS========\n");
            printf("Bubble Sort     : %d\n", COUNTS[0]);
            printf("Insertion Sort  : %d\n", COUNTS[1]);
            printf("Radix Sort      : %d\n", COUNTS[2]);
            printf("Merge Sort      : %d\n", COUNTS[3]);
            printf("Quick Sort      : %d\n", COUNTS[4]);
            break;
        case 7:
            printf("Exiting...");
            break;
        default:
            printf("Invalid choice");
            break;
        }
        if (choice > 6)
        {
            break;
        }
    }

    return 0;
}
