/*
11. MEMORY ALLOCATION STRATEGIES

At one instant, the memory map of a 4 MB (4000 KB) RAM looks as in Figure 1.

Processes (P1, P2, etc.) request the operating system for memory and also release the allocated memory after completing execution.

Sample execution trace:

P7 requests for 115 KB
P10 requests for 650 KB
P3 completes execution
P1 completes execution
P6 completes execution
P8 requests for 200 KB
P5 completes execution
P2 completes execution
P9 requests for 37 KB
P10 completes execution
P9 completes execution
P4 completes execution

Task:
Which strategy among the following performs the best here?

- First Fit
- Best Fit
- Worst Fit

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
FIRST_FIT,
BEST_FIT,
WORST_FIT
} Strategy;

typedef struct Block {
int start;
int size;
int free;
char process[10];
struct Block *prev;
struct Block *next;
} Block;

Block *createBlock(int start, int size, int free, const char *process)
{
Block *newBlock = malloc(sizeof(Block));

newBlock->start = start;
newBlock->size = size;
newBlock->free = free;
strcpy(newBlock->process, process);
newBlock->prev = NULL;
newBlock->next = NULL;

return newBlock;
}

Block *initializeMemory()
{
Block *head = NULL;
Block *tail = NULL;

int start[] = {
0, 10, 310, 400, 1000, 1500,
1850, 2000, 2200, 2300, 3150, 3500
};

int size[] = {
10, 300, 90, 600, 500, 350,
150, 200, 100, 850, 350, 500
};

char *process[] = {
"P5", "FREE", "P6", "FREE", "P1", "FREE",
"P2", "FREE", "P4", "FREE", "P3", "FREE"
};

for (int i = 0; i < 12; i++) {
int isFree = strcmp(process[i], "FREE") == 0;

Block *node = createBlock(
start[i],
size[i],
isFree,
process[i]
);

if (head == NULL) {
head = node;
tail = node;
} else {
tail->next = node;
node->prev = tail;
tail = node;
}
}

return head;
}

Block *findBlock(Block *head, int size, Strategy strategy)
{
Block *current = head;
Block *selected = NULL;

while (current != NULL) {

if (current->free && current->size >= size) {

if (strategy == FIRST_FIT)
return current;

if (strategy == BEST_FIT) {
if (selected == NULL ||
current->size < selected->size)
selected = current;
}

if (strategy == WORST_FIT) {
if (selected == NULL ||
current->size > selected->size)
selected = current;
}
}

current = current->next;
}

return selected;
}

int allocate(Block *head, const char *process, int size, Strategy strategy)
{
Block *hole = findBlock(head, size, strategy);

printf("%s requests for %d KB", process, size);

if (hole == NULL) {
printf(" -> allocation failed\n");
return 0;
}

int start = hole->start;

if (hole->size > size) {
Block *newFree = createBlock(
hole->start + size,
hole->size - size,
1,
"FREE"
);

newFree->next = hole->next;
newFree->prev = hole;

if (hole->next != NULL)
hole->next->prev = newFree;

hole->next = newFree;
hole->size = size;
}

hole->free = 0;
strcpy(hole->process, process);

printf(" -> allocated at (%d,%d)\n",
start, start + size);

return 1;
}

void merge(Block *left, Block *right)
{
left->size += right->size;
left->next = right->next;

if (right->next != NULL)
right->next->prev = left;

free(right);
}

void release(Block *head, const char *process)
{
Block *current = head;

printf("%s completes execution\n", process);

while (current != NULL) {

if (!current->free &&
strcmp(current->process, process) == 0) {

current->free = 1;
strcpy(current->process, "FREE");

if (current->prev != NULL &&
current->prev->free) {

current = current->prev;
merge(current, current->next);
}

if (current->next != NULL &&
current->next->free) {

merge(current, current->next);
}

return;
}

current = current->next;
}
}

void printMemory(Block *head)
{
Block *current = head;

while (current != NULL) {

printf("(%d,%d,%s)",
current->start,
current->start + current->size,
current->process);

if (current->next != NULL)
printf(" ");

current = current->next;
}

printf("\n");
}

int largestFree(Block *head)
{
int largest = 0;
Block *current = head;

while (current != NULL) {

if (current->free && current->size > largest)
largest = current->size;

current = current->next;
}

return largest;
}

void destroyList(Block *head)
{
Block *current = head;

while (current != NULL) {
Block *next = current->next;
free(current);
current = next;
}
}

const char *strategyName(Strategy strategy)
{
if (strategy == FIRST_FIT)
return "FIRST FIT";

if (strategy == BEST_FIT)
return "BEST FIT";

return "WORST FIT";
}

void simulate(Strategy strategy)
{
Block *head = initializeMemory();
int allocations = 0;

printf("\n%s:\n", strategyName(strategy));

allocations += allocate(head, "P7", 115, strategy);
allocations += allocate(head, "P10", 650, strategy);

release(head, "P3");
release(head, "P1");
release(head, "P6");

allocations += allocate(head, "P8", 200, strategy);

release(head, "P5");
release(head, "P2");

allocations += allocate(head, "P9", 37, strategy);

release(head, "P10");
release(head, "P9");
release(head, "P4");

printf("\nFinal memory map:\n");
printMemory(head);

printf("\nSuccessful allocations: %d\n", allocations);
printf("Largest free block: %d KB\n", largestFree(head));

destroyList(head);
}

int main()
{
simulate(FIRST_FIT);
simulate(BEST_FIT);
simulate(WORST_FIT);

return 0;
}
