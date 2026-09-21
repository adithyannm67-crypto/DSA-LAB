
#include <stdio.h>

int main()
{
    int A[10][10], B[10][10], C[10][10], T[10][10];
    int r, c, i, j;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &r, &c);

    printf("Enter elements of Matrix A:\n");
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of Matrix B:\n");
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
             scanf("%d", &B[i][j]);


    
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            C[i][j] = A[i][j] + B[i][j];

    printf("\nSum of the matrices:\n");
    for (i = 0; i < r; i++){
        for (j = 0; j < c; j++)
            printf("%d\t", C[i][j]);
        printf("\n");
    }


    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            T[j][i] = C[i][j];


    printf("\nTranspose of the sum:\n");
    for (i = 0; i < c; i++){
        for (j = 0; j < r; j++)
             printf("%d\t", T[i][j]);
        printf("\n");
    }

    return 0;
}


/*

Enter number of rows and columns: 3 3

Enter elements of Matrix A:
1 0 2
0 3 0
4 0 5

Enter elements of Matrix B:
0 6 0
7 0 8
0 9 0

Sum of the matrices:
1       6       2
7       3       8
4       9       5

Transpose of the sum:
1       7       4
6       3       9
2       8       5


*/

