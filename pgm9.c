#include <stdio.h>
#include <stdlib.h>

struct term
{
    int exp, coeff;
    struct term *next;
};

struct term *ALLOCATE_NODE()
{
    struct term *p = (struct term *)malloc(sizeof(struct term));
    if (p != NULL)
    {
        return p;
    }

    printf("\nMEMORY CANT BE ALLOCATED\n");
    return ALLOCATE_NODE();
}

struct term *CREATE_POLYNOMIAL()
{
    struct term *prev = NULL, *head = NULL;

    do
    {
       
        int exp, coeff;
        printf("\nENTER THE COEFF,EXP  :");
        scanf("%d %d", &coeff, &exp);
        if (coeff == 0)
        {
            break;
        }
         struct term *temp = ALLOCATE_NODE();
        temp->coeff = coeff;
        temp->exp = exp;
        temp->next = NULL;

        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            prev->next = temp;
        }
        prev = temp;
    } while (1);

    return head;
}

void PRINT_POLYNOMIAL(struct term *head)
{
    if (head == NULL)
    {
        printf("\nEMPTY LIST\n");
        return;
    }
    struct term *ptr = head;

    while (ptr != NULL)
    {
        printf("%dx^%d", ptr->coeff, ptr->exp);
        if (ptr->next != NULL)
        {
            printf(" + ");
        }
        ptr = ptr->next;
    }
}

struct term *POLINAMIAL_MULTIPLY(struct term *head1, struct term *head2)
{

    struct term *ptr1 = head1;
    struct term *ptr2 = head2;

    if (ptr1 == NULL || ptr2 == NULL)
    {
        return NULL;
    }

    struct term *headProd = NULL;
    struct term *prod = NULL;

    while (ptr1 != NULL)
    {
        ptr2 = head2;
        while (ptr2 != NULL)
        {

            struct term *temp = ALLOCATE_NODE();

            temp->coeff = ptr1->coeff * ptr2->coeff;
            temp->exp = ptr1->exp + ptr2->exp;
            temp->next = NULL;

            if (headProd == NULL)
            {
                headProd = temp;
                prod = temp;
            }
            else
            {
                struct term *p = headProd;
                int found = 0;
                while (p != NULL)
                {
                    if (p->exp == temp->exp)
                    {
                        found = 1;
                        break;
                    }
                    p = p->next;
                }
                if (found)
                {
                    p->coeff += temp->coeff;
                    free(temp);
                }
                else
                {
                    prod->next = temp;
                    prod = temp;
                }
            }

            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }

    return headProd;
}

int main()
{

    printf("\nPOLINAMIAL 1\n");
    struct term *headP1 = CREATE_POLYNOMIAL();
    PRINT_POLYNOMIAL(headP1);

    printf("\nPOLINAMIAL 2\n");
    struct term *headP2 = CREATE_POLYNOMIAL();
    PRINT_POLYNOMIAL(headP2);

    struct term *headProd = POLINAMIAL_MULTIPLY(headP1, headP2);
    printf("\nPRODUCT   =    ");
    PRINT_POLYNOMIAL(headProd);
    return 0;
}
