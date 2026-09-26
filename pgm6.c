#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Customer {
    int token;
    int forms; // Number of tickets/forms remaining
};

struct Queue {
    struct Customer data[MAX];
    int front;
    int rear;
};

void initialize(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(struct Queue *q) {
    return q->front == -1;
}

int isFull(struct Queue *q) {
    return q->rear == MAX - 1;
}

void enqueue(struct Queue *q, int token, int forms) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }

    if (q->front == -1)
        q->front = 0;

    q->rear++;

    q->data[q->rear].token = token;
    q->data[q->rear].forms = forms;
}

struct Customer dequeue(struct Queue *q) {
    struct Customer temp = {-1, -1};

    if (isEmpty(q))
        return temp;

    temp = q->data[q->front];

    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }

    return temp;
}

void displayCurrent(struct Queue *q) {
    if (isEmpty(q)) {
        printf("No customer is waiting.\n");
        return;
    }

    printf("Current customer: Token %d\n", q->data[q->front].token);
    printf("Forms remaining: %d\n", q->data[q->front].forms);
}

void displayWaiting(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Number of customers waiting: 0\n");
        return;
    }

    printf("Number of customers waiting: %d\n",
           q->rear - q->front + 1);
}

void displayQueue(struct Queue *q) {
    int i;

    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("\n--- Customers in Queue ---\n");

    for (i = q->front; i <= q->rear; i++) {
        printf("Token %d : %d form(s)\n",
               q->data[i].token,
               q->data[i].forms);
    }
}

void serveCustomer(struct Queue *q) {
    struct Customer c;

    if (isEmpty(q)) {
        printf("No customers waiting.\n");
        return;
    }

    c = dequeue(q);

    printf("Serving Token %d\n", c.token);

    c.forms--;

    if (c.forms > 0) {
        /* Customer has more tickets to book.
           Send them to the tail of the queue. */
        enqueue(q, c.token, c.forms);

        printf("Token %d has %d form(s) remaining.\n",
               c.token, c.forms);
        printf("Customer moved to the tail of the queue.\n");
    } else {
        printf("Token %d has completed all bookings.\n", c.token);
    }
}

int main() {
    struct Queue q;
    int choice;
    int token = 1;
    int tickets;

    initialize(&q);

    while (1) {
        printf("\n========== RAILWAY RESERVATION ==========\n");
        printf("1. Take Token\n");
        printf("2. Serve Current Customer\n");
        printf("3. Display Current Customer\n");
        printf("4. Display Number of Customers Waiting\n");
        printf("5. Display All Customers\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter number of tickets to be booked: ");
            scanf("%d", &tickets);

            if (tickets <= 0) {
                printf("Invalid number of tickets.\n");
            } else {
                enqueue(&q, token, tickets);

                printf("Token issued: %d\n", token);
                printf("Number of forms: %d\n", tickets);

                token++;
            }
            break;

        case 2:
            serveCustomer(&q);
            break;

        case 3:
            displayCurrent(&q);
            break;

        case 4:
            displayWaiting(&q);
            break;

        case 5:
            displayQueue(&q);
            break;

        case 6:
            printf("Program terminated.\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
