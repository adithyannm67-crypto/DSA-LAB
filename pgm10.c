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

struct APP
{
    char name[100];
    struct APP *next, *prev;
};

struct APP *CREATE_NODE()
{
    struct APP *p = (struct APP *)malloc(sizeof(struct APP));

    if (p == NULL)
        return CREATE_NODE();

    return p;
}

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

    if (p == head)
    {
        printf("\nAPP IS ALREADY THE MOST FREQUENTLY USED APP\n");
        return head;
    }

    if (p->prev != NULL)
        p->prev->next = p->next;

    if (p->next != NULL)
        p->next->prev = p->prev;

    p->prev = NULL;
    p->next = head;

    head->prev = p;
    head = p;

    printf("\nAPP MOVED TO THE MOST FREQUENTLY USED POSITION\n");

    return head;
}

struct APP *REMOVE_LESS_FREQUENTLY_USED_APPS(struct APP *head)
{
    struct APP *p = head, *prev = NULL;

    if (p == NULL)
    {
        printf("\nAPP LIST IS EMPTY\n");
        return NULL;
    }

    int length = 0;

    while (p != NULL)
    {
        prev = p;
        p = p->next;
        length++;
    }

    int n;

    printf("\nHOW MANY LEAST FREQUENTLY USED APPS DO YOU WANT TO REMOVE : ");
    scanf("%d", &n);

    if (n > length || n <= 0)
    {
        printf("\nINVALID NUMBER OF APPS\n");
        return head;
    }

    int i = 1;

    while (prev != NULL && i <= n)
    {
        struct APP *temp = prev->prev;
        free(prev);
        prev = temp;
        i++;
    }

    if (prev != NULL)
        prev->next = NULL;
    else
        head = NULL;

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