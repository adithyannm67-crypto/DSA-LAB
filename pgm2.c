#include <stdio.h>

struct Term
{
    int coeff;
    int exp;
};

int addPolynomials(struct Term msg[], int m, struct Term key[], int k, struct Term c[])
{
    int apos = 0, bpos = 0, cpos = 0;

    while (apos < m && bpos < k)
    {
        if (msg[apos].exp > key[bpos].exp)
        {
            c[cpos++] = msg[apos++];
        }
        else if (msg[apos].exp < key[bpos].exp)
        {
            c[cpos++] = key[bpos++];
        }
        else
        {
            int sum = (msg[apos].coeff + key[bpos].coeff) % 3;
            if (sum != 0)
            {
                c[cpos].coeff = sum;
                c[cpos].exp = msg[apos].exp;
                cpos++;
            }
            apos++;
            bpos++;
        }
    }
    while (apos < m)
        c[cpos++] = msg[apos++];
    while (bpos < k)
        c[cpos++] = key[bpos++];

    return cpos;
}

void printPoly(struct Term p[], int n)
{
    if (n == 0)
    {
        printf("0\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d", p[i].coeff);
        if (p[i].exp != 0)
            printf("x^%d", p[i].exp);
        if (i != n - 1)
            printf(" + ");
    }
    printf("\n");
}

int main()
{
    struct Term msg[10], key[10], c[20];
    int m, k;

    printf("Enter no. of terms in message poly m(x): ");
    scanf("%d", &m);
    printf("Enter coeff and exp for each term (descending exponent order):\n");
    for (int i = 0; i < m; i++)
        scanf("%d %d", &msg[i].coeff, &msg[i].exp);

    printf("\nEnter no. of terms in key poly k(x): ");
    scanf("%d", &k);
    printf("Enter coeff and exp for each term (descending exponent order):\n");
    for (int i = 0; i < k; i++)
        scanf("%d %d", &key[i].coeff, &key[i].exp);

    int n = addPolynomials(msg, m, key, k, c);

    printf("\nm(x) = ");
    printPoly(msg, m);
    printf("k(x) = ");
    printPoly(key, k);
    printf("c(x) = ");
    printPoly(c, n);

    return 0;
}