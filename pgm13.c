/*

13. BINARY SEARCH TREE DICTIONARY

Construct a binary tree to efficiently implement a dictionary of <word, meaning> pairs.

Menu operations:

(a) Find the meaning of a given word.

(b) Insert a new <word, meaning> pair.

(c) Remove an existing <word, meaning> pair.


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char word[50];
    char meaning[100];
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(char *word, char *meaning)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *findNode(Node *root, char *word)
{
    Node *p = root;
    if (root == NULL)
    {
        return NULL;
    }
    while (p != NULL)
    {
        if (strcmp(word, p->word) > 0)
        {
            p = p->right;
        }
        else if (strcmp(word, p->word) < 0)
        {
            p = p->left;
        }
        else
        {
            return p;
        }
    }
    return NULL;
}

Node *insert(Node *root)
{
    char word[50], meaning[100];
    printf("Enter the word to insert: ");
    scanf("%s", word);
    printf("Enter the meaning: ");
    scanf("%s", meaning);

    Node *newNode = createNode(word, meaning);
    Node *p = root, *parent = NULL;

    if (root == NULL)
    {
        root = newNode;
        return root;
    }

    while (p != NULL)
    {
        parent = p;
        if (strcmp(word, p->word) < 0)
        {
            p = p->left;
            if (p == NULL)
            {
                parent->left = newNode;
                break;
            }
        }
        else if (strcmp(word, p->word) > 0)
        {
            p = p->right;
            if (p == NULL)
            {
                parent->right = newNode;
                break;
            }
        }
        else
        {
            printf("Word already exists in the dictionary!\n");
            free(newNode);
            break;
        }
    }

    return root;
}

void findMeaning(Node *root)
{
    char word[50];
    printf("\nEnter the word to find: ");
    scanf("%s", word);

    Node *requiredNode = findNode(root, word);

    if (requiredNode != NULL)
    {
        printf("Meaning: %s\n", requiredNode->meaning);
    }
    else
    {
        printf("Word not found!\n");
    }
}

Node *findParent(Node *root, char *word)
{
    Node *p = root;
    Node *parent = NULL;
    while (p != NULL)
    {
        if (strcmp(word, p->word) < 0)
        {
            parent = p;
            p = p->left;
        }
        else if (strcmp(word, p->word) > 0)
        {
            parent = p;
            p = p->right;
        }
        else
        {
            return parent;
        }
    }
    return NULL;
}

Node *findInorderSuccessor(Node *root, char *word)
{
    Node *NodeCorrespondsToWord = findNode(root, word);

    if (NodeCorrespondsToWord->right != NULL)
    {
        Node *successor = NodeCorrespondsToWord->right;
        while (successor->left != NULL)
        {
            successor = successor->left;
        }
        return successor;
    }
    else
    {
        Node *successor = findParent(root, word);
        Node *child = NodeCorrespondsToWord;
        while (successor != NULL && child == successor->right)
        {
            child = successor;
            successor = findParent(root, successor->word);
        }
        return successor;
    }
}
Node *deleteNode(Node *root)
{
    char word[50];
    printf("Enter the word to remove: ");
    scanf("%s", word);
    Node *nodeToDelete = findNode(root, word);
    Node *parent = findParent(root, word);
    if (nodeToDelete == NULL)
    {
        printf("Word not found in the dictionary!\n");
        return root;
    }

    if (nodeToDelete->left == NULL && nodeToDelete->right == NULL)
    {
        if (parent == NULL)
        {
            root = NULL;
            free(nodeToDelete);
            return root;
        }

        if (parent->left == nodeToDelete)
        {
            parent->left = NULL;
        }
        else if (parent->right == nodeToDelete)
        {
            parent->right = NULL;
        }
        free(nodeToDelete);
    }
    else if (nodeToDelete->left == NULL && nodeToDelete->right != NULL)
    {

        if (parent == NULL)
        {
            root = nodeToDelete->right;
            free(nodeToDelete);
            return root;
        }

        if (parent->left == nodeToDelete)
        {
            parent->left = nodeToDelete->right;
        }
        else if (parent->right == nodeToDelete)
        {
            parent->right = nodeToDelete->right;
        }
        free(nodeToDelete);
    }
    else if (nodeToDelete->left != NULL && nodeToDelete->right == NULL)
    {

        if (parent == NULL)
        {
            root = nodeToDelete->left;
            free(nodeToDelete);
            return root;
        }

        if (parent->left == nodeToDelete)
        {
            parent->left = nodeToDelete->left;
        }
        else if (parent->right == nodeToDelete)
        {
            parent->right = nodeToDelete->left;
        }
        free(nodeToDelete);
    }
    else if (nodeToDelete->left != NULL && nodeToDelete->right != NULL)
    {
        Node *successor = findInorderSuccessor(root, nodeToDelete->word);
        strcpy(nodeToDelete->word, successor->word);
        strcpy(nodeToDelete->meaning, successor->meaning);
        Node *successorParent = findParent(root, successor->word);

      
        if (successorParent->left == successor)
        {
            successorParent->left = successor->right;
        }
        else if (successorParent->right == successor)
        {
            successorParent->right = successor->right;
        }
        free(successor);
    }

    return root;
}

int main()
{
    Node *root = NULL; // Initialize the root of the binary search tree
    while (1)
    {

        printf("\nDictionary Operations:\n");
        printf("1. Find meaning of a word\n");
        printf("2. Insert a new <word, meaning> pair\n");
        printf("3. Remove an existing <word, meaning> pair\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        char word[50];
        char meaning[100];

        switch (choice)
        {
        case 1:
            findMeaning(root);
            break;
        case 2:
            root = insert(root);
            break;
        case 3:

            root = deleteNode(root);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    // The actual implementation of the binary search tree and its operations would go here.
    return 0;
}