#include <stdio.h>
#include <string.h>

#define MAX 50
#define SPEED 30.0

struct Document {
    char teacher[50];
    char file[100];
    int pages;
};

struct Document q[MAX];
int front = 0, rear = -1;

void bookDocument(){
    if (rear == MAX - 1) {
        printf("Spool is full.\n");
        return;
    }

    rear++;

    printf("Enter teacher name: ");
    scanf(" %[^\n]", q[rear].teacher);

    printf("Enter PDF name: ");
    scanf(" %[^\n]", q[rear].file);

    printf("Enter number of pages: ");
    scanf("%d", &q[rear].pages);

    printf("Document addedjaya successfully.\n");
}

void currentPrinting(){
    if (front > rear) {
        printf("No document is being printed.\n");
        return;
    }

    printf("Currently printing: %s\n", q[front].teacher);
}

void waitingTime(){
    int i, pages = 0;

    for (i = front; i <= rear; i++) {
        if (strcmp(q[i].file, "PCCSL307 Lab cycle.pdf") == 0) {
            printf("Waiting time: %.2f minutes\n", pages / SPEED);
            return;
        }

        pages += q[i].pages;
    }

    printf("Document not found.\n");
}

void maximumWaiting(){
    int i, pages = 0;
    int maxPages = -1, maxIndex = -1;

    for (i = front; i <= rear; i++) {
        if (pages > maxPages) {
            maxPages = pages;
            maxIndex = i;
        }

        pages += q[i].pages;
    }

    if (maxIndex != -1)
        printf("Teacher who waits the most: %s\n",
               q[maxIndex].teacher);
    else
        printf("Queue is empty.\n");
}

int main()
{
    int choice;

    do {
        printf("\n----- PRINTER SPOOL -----\n");
        printf("1. Book Document\n");
        printf("2. Current Document\n");
        printf("3. Waiting Time\n");
        printf("4. Maximum Waiting Teacher\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookDocument();
                break;
            case 2:
                currentPrinting();
                break;
            case 3:
                waitingTime();
                break;

            case 4:
                maximumWaiting();
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 5);

    return 0;
}
