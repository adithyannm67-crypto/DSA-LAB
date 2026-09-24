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
    if (BACK_TOP >= MAX - 1)
    {
        printf("\nBack stack is full.\n");
        return;
    }

    printf("\nEnter URL: ");
    scanf("%s", BACK_STACK[++BACK_TOP].name);

    FORWARD_TOP = -1;

    printf("Page visited successfully.\n");
}

void MOVE_FORWARD()
{
    if (FORWARD_TOP < 0)
    {
        printf("\nNo forward page available.\n");
        return;
    }

    BACK_TOP++;

    strcpy(BACK_STACK[BACK_TOP].name,
           FORWARD_STACK[FORWARD_TOP].name);

    FORWARD_TOP--;

    printf("\nMoved forward successfully.\n");
}

void MOVE_BACK()
{
    if (BACK_TOP < 0)
    {
        printf("\nNo previous page available.\n");
        return;
    }

    FORWARD_TOP++;

    strcpy(FORWARD_STACK[FORWARD_TOP].name,
           BACK_STACK[BACK_TOP].name);

    BACK_TOP--;

    printf("\nMoved backward successfully.\n");
}

void CURRENT_LINK()
{
    if (BACK_TOP < 0)
    {
        printf("\nNo page is currently open.\n");
        return;
    }

    printf("\nCurrent URL: %s\n",
           BACK_STACK[BACK_TOP].name);
}

int main()
{
    int choice;

    do
    {
        printf("\n========== BROWSER NAVIGATION ==========\n");
        printf("1. Visit New Page\n");
        printf("2. Move Forward\n");
        printf("3. Move Backward\n");
        printf("4. Display Current URL\n");
        printf("5. Exit\n");
        printf("========================================\n");

        printf("Enter choice: ");
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

        case 5:
            printf("\nProgram terminated.\n");
            break;

        default:
            printf("\nInvalid choice.\n");
        }

    } while (choice != 5);

    return 0;
}