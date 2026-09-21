/*
10. APP CLEANER

App Cleaner is a utility that helps remove unwanted applications
when the mobile device is running out of storage.

The utility identifies applications based on their frequency of use.
Frequently used applications are kept at the beginning of the list,
while less frequently used applications are placed towards the end.

When an application is opened, it becomes the most frequently used
application and is moved to the beginning of the list.

Task:
Identify a suitable data structure to implement the App Cleaner.

Also, implement the utility using the operations supported by
the chosen data structure.

Chosen Data Structure:
Doubly Linked List

Implementation:
The first node represents the most frequently used application,
while the last node represents the least frequently used application.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure representing an application */
struct APP
{
    char name[100];
    struct APP *next, *prev;
};

/* Creates and allocates memory for a new application node */
struct APP *CREATE_NODE()
{
    struct APP *p = (struct APP *)malloc(sizeof(struct APP));

    if (p == NULL)
        return CREATE_NODE();

    return p;
}

/* Adds a new application at the beginning of the list */
struct APP *ADD_NEW_APP(struct APP *head)
{
    struct APP *curr = CREATE_NODE();

    printf("\nENTER APP NAME : ");
    scanf("%99s", curr->name);

    curr->prev = NULL;
    curr->next = head;

    if (head != NULL)
        head->prev = curr;

    return curr;
}

/* Displays the application list in both forward and reverse order */
void PRINT_APP_LIST(struct APP *p)
{
    struct APP *prev = NULL;

    if (p == NULL)
    {
        printf("\nAPP LIST IS EMPTY\n");
        return;
    }

    printf("\n----- APP LIST -----\n");

    while (p != NULL)
    {
        printf("\n%s", p->name);
        prev = p;
        p = p->next;
    }

    printf("\n\n----- REVERSE ORDER -----\n");

    while (prev != NULL)
    {
        printf("\n%s", prev->name);
        prev = prev->prev;
    }

    return;
}

/*
Moves the selected application to the beginning of the list.

An application becomes the most frequently used application
when it is opened.
*/
struct APP *USE_AN_APP(struct APP *head)
{
    struct APP *p = head;

    if (p == NULL)
    {
        printf("\nAPP LIST IS EMPTY\n");
        return head;
    }

    PRINT_APP_LIST(head);

    char appname[100];

    printf("\nENTER THE APP YOU WANT TO USE : ");
    scanf("%99s", appname);

    while (p != NULL)
    {
        if (strcmp(p->name, appname) == 0)
            break;

        p = p->next;
    }

    if (p == NULL)
    {
        printf("\nAPP NOT FOUND\n");
        return head;
    }

    /* App is already the most frequently used app */
    if (p == head)
    {
        printf("\nAPP IS ALREADY THE MOST FREQUENTLY USED APP\n");
        return head;
    }

    /* Remove the app from its current position */
    if (p->prev != NULL)
        p->prev->next = p->next;

    if (p->next != NULL)
        p->next->prev = p->prev;

    /* Move the app to the beginning */
    p->prev = NULL;
    p->next = head;

    head->prev = p;
    head = p;

    printf("\nAPP MOVED TO THE MOST FREQUENTLY USED POSITION\n");

    return head;
}

/* Returns the total number of applications in the list */
int LENGTH_OF_LIST(struct APP *p)
{
    int n = 0;

    if (p == NULL)
        return n;

    while (p != NULL)
    {
        p = p->next;
        n++;
    }

    return n;
}

/*
Removes applications from the end of the list.

The applications at the end of the list are considered
the least frequently used applications.
*/
struct APP *REMOVE_LESS_FREQUENTLY_USED_APPS(struct APP *head)
{
    struct APP *p = head, *cut;

    if (p == NULL)
    {
        printf("\nAPP LIST IS EMPTY\n");
        return NULL;
    }

    int n, length = LENGTH_OF_LIST(head);

    printf("\nHOW MANY LEAST FREQUENTLY USED APPS DO YOU WANT TO REMOVE : ");
    scanf("%d", &n);

    if (n > length || n <= 0)
    {
        printf("\nINVALID NUMBER OF APPS\n");
        return head;
    }
    if (n < length)
    {
        for (int i = 0; i < length - n - 1; i++)
            p = p->next;
        cut = p->next;
        p->next = NULL;
    }
    if (n == length)
    {
        cut = head;
        head = NULL;
    }

    while (cut != NULL)
    {
        struct APP *next = cut->next;
        free(cut);
        cut = next;
    }

    printf("\nLEAST FREQUENTLY USED APPS REMOVED SUCCESSFULLY\n");

    return head;
}

int main()
{
    struct APP *head = NULL;

    while (1)
    {
        printf("\n\n========== APP CLEANER ==========\n");
        printf("1. ADD NEW APP\n");
        printf("2. DISPLAY APP LIST\n");
        printf("3. USE AN APP\n");
        printf("4. REMOVE LEAST FREQUENTLY USED APPS\n");
        printf("=================================\n");

        int choice;

        printf("\nENTER YOUR CHOICE : ");
        scanf("%d", &choice);

        if (choice == 1)
            head = ADD_NEW_APP(head);

        else if (choice == 2)
            PRINT_APP_LIST(head);

        else if (choice == 3)
            head = USE_AN_APP(head);

        else if (choice == 4)
            head = REMOVE_LESS_FREQUENTLY_USED_APPS(head);

        else
        {
            printf("\nEXITING APP CLEANER...\n");
            break;
        }
    }
}