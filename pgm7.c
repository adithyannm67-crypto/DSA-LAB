#include <stdio.h>
#include <string.h>

#define MAX 100

struct link
{
    char name[100];
};

struct link FORWARD_STACK[MAX], BACK_STACK[MAX];

int FORWARD_TOP = -1, BACK_TOP = -1;

void VISIT_NEW_PAGE()
{
    if (BACK_TOP > MAX - 1)
    {
        printf("STACK FULL");
        return;
    }

    BACK_TOP++;
    printf("ENTER THE LINK : ");
    scanf("%s", BACK_STACK[BACK_TOP].name);
    return;
}

void MOVE_FORWARD()
{
    if (FORWARD_TOP < 0)
    {
        printf("CANNNOT GO FORWARD");
        return;
    }

    BACK_TOP++;
    strcpy(BACK_STACK[BACK_TOP].name, FORWARD_STACK[BACK_TOP].name);
    FORWARD_TOP--;
    return;
}

void MOVE_BACK()
{
    if (BACK_TOP < 0)
    {
        printf("CANNNOT GO BACK");
        return;
    }

    FORWARD_TOP++;
    strcpy(FORWARD_STACK[BACK_TOP].name, BACK_STACK[BACK_TOP].name);
    BACK_TOP--;
    return;
}
void CURRENT_LINK()
{
    if (BACK_TOP < 0)
    {
        printf("NO LINK");
        return;
    }

    if(BACK_STACK[BACK_TOP].name)
        printf("CURRENT LINK    :    %s \n", BACK_STACK[BACK_TOP].name);
}

int main()
{
    int choice;
    char dir;
    int option;
    do
    {
        printf("WHAT DO YOU WANT   \n");

        printf("1====visit new page\n");
        printf("2===Move forward\n");
        printf("3===move backward\n");
        printf("4===CURRENT LINK");
        printf("ENTER OPTION");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            VISIT_NEW_PAGE();
            break;
        case 2:
            MOVE_FORWARD();
            break;
        case 3:
            MOVE_BACK();
            break;
        case 4:
            CURRENT_LINK();
            break;
        default:
            printf("EXITING........");
        }

    } while (choice >=1 && choice<=4);

    return 0;
}