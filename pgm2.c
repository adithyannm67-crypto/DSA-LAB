#include <stdio.h>
#include <string.h>

#define MAX 50

struct Document {
    char teacher[50];
    char filename[100];
    int pages;
    float waitingTime;
};

struct Document queue[MAX];
int front = 0, rear = -1;

/* Add document to printer queue */
void enqueue() {
    if (rear == MAX - 1) {
        printf("Printer queue is full!\n");
        return;
    }

    rear++;

    printf("Enter teacher name: ");
    scanf(" %[^\n]", queue[rear].teacher);

    printf("Enter PDF file name: ");
    scanf(" %[^\n]", queue[rear].filename);

    printf("Enter number of pages: ");
    scanf("%d", &queue[rear].pages);

    /* Calculate waiting time */
    if (rear == 0)
        queue[rear].waitingTime = 0;
    else
        queue[rear].waitingTime =
            queue[rear - 1].waitingTime +
            (queue[rear - 1].pages / 30.0);

    printf("Document added to printer queue.\n");
}

/* Display currently printing document */
void currentDocument() {
    if (front > rear) {
        printf("Printer queue is empty.\n");
        return;
    }

    printf("\nCurrently being printed:\n");
    printf("Teacher : %s\n", queue[front].teacher);
    printf("PDF     : %s\n", queue[front].filename);
}

/* Find waiting time of PCCSL307 Lab cycle.pdf */
void findWaitingTime() {
    int i;
    char target[] = "PCCSL307 Lab cycle.pdf";

    for (i = front; i <= rear; i++) {
        if (strcmp(queue[i].filename, target) == 0) {
            printf("\nWaiting time for %s = %.2f minutes\n",
                   target, queue[i].waitingTime);
            return;
        }
    }

    printf("\nDocument not found in printer queue.\n");
}

/* Find teacher with maximum waiting time */
void maximumWaiting() {
    int i, maxIndex;

    if (front > rear) {
        printf("Printer queue is empty.\n");
        return;
    }

    maxIndex = front;

    for (i = front + 1; i <= rear; i++) {
        if (queue[i].waitingTime > queue[maxIndex].waitingTime)
            maxIndex = i;
    }

    printf("\nTeacher who has to wait the most:\n");
    printf("Teacher : %s\n", queue[maxIndex].teacher);
    printf("Waiting time : %.2f minutes\n",
           queue[maxIndex].waitingTime);
}

/* Print the current document and remove it */
void printDocument() {
    if (front > rear) {
        printf("Printer queue is empty.\n");
        return;
    }

    printf("\nPrinting: %s (%s)\n",
           queue[front].filename,
           queue[front].teacher);

    printf("Printing completed.\n");

    front++;
}

int main() {
    int choice;

    do {
        printf("\n===== PRINTER QUEUE =====\n");
        printf("1. Add PDF to printer queue\n");
        printf("2. Display currently printing teacher\n");
        printf("3. Find waiting time of PCCSL307 Lab cycle.pdf\n");
        printf("4. Display teacher with maximum waiting time\n");
        printf("5. Print current document\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enqueue();
                break;

            case 2:
                currentDocument();
                break;

            case 3:
                findWaitingTime();
                break;

            case 4:
                maximumWaiting();
                break;

            case 5:
                printDocument();
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}