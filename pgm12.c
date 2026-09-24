
/*

12. EXPRESSION TREE

An expression tree is a tree that represents an arithmetic expression.

The leaves of the tree are operands such as constants or variables, whereas the internal nodes are all operators.

The children of an operator node are its operands.

Example expression:

(A + B * C) − ((D * E + F) / G)

Task:

(a) Construct an expression tree for the input.

(b) Display the input expression’s prefix and postfix notations.

Hint:
Think in terms of traversals!

You may assume that the expression has only binary operands.

Two stacks are used:

1. operatorStack — to hold the operators.
2. nodeStack — to hold the tree nodes.

Build-Subtree(operatorStack, nodeStack):

1. root = Pop(operatorStack)
2. rightChild = Pop(nodeStack)
3. leftChild = Pop(nodeStack)
4. root.left = leftChild
5. root.right = rightChild
6. Push(nodeStack, root)

Construct-Expression-Tree(expression):

1. operatorStack = a new empty stack
2. nodeStack = a new empty stack
3. For each character in expression:
4. If IsOperand(char):
5.     newNode = Create-Leaf-Node(char)
6.     Push(nodeStack, newNode)
7. Else if char == '(':
8.     Push(operatorStack, char)
9. Else if char == ')':
10.    While Top(operatorStack) != '(':
11.        Build-Subtree(operatorStack, nodeStack)
12.    Pop(operatorStack)
13. Else:
14.    While (!IsEmpty(operatorStack) AND
        Top(operatorStack) != '(' AND
        Precedence(Top(operatorStack)) >= Precedence(char)):
15.        Build-Subtree(operatorStack, nodeStack)
16.    Push(operatorStack, char)
17. While !IsEmpty(operatorStack):
18.    Build-Subtree(operatorStack, nodeStack)
19. Return Pop(nodeStack)


*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

int IS_OPEARAND(char c)
{
    return isalnum(c);
}

int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

struct NODE
{
    char item;
    struct NODE *left, *right;
};

struct NODE *CREATE_LEAF_NODE(char c)
{
    struct NODE *p = (struct NODE *)malloc(sizeof(struct NODE));

    if (p == NULL)
        return CREATE_LEAF_NODE(c);

    p->item = c;
    p->left = NULL;
    p->right = NULL;
    return p;
}

struct NODE_STACK
{
    struct NODE *A[MAX];
    int tos;
};
struct STACK
{
    char A[MAX];
    int tos;
};

struct STACK OPERATOR_STACK;
struct NODE_STACK NODE_STACK;

void NODE_STACK_PUSH(struct NODE *c);
struct NODE *NODE_STACK_POP();

void STACK_PUSH(char c);
char STACK_POP();

void BUILD_SUB_TREE()
{

    struct NODE *p = CREATE_LEAF_NODE(STACK_POP());
    p->right = NODE_STACK_POP();
    p->left = NODE_STACK_POP();
    NODE_STACK_PUSH(p);
}

struct NODE* CONSTRUCT_EXPRESSION_TREE(char *expression)
{

    OPERATOR_STACK.tos = -1;
    NODE_STACK.tos = -1;

    for (int i = 0; expression[i] != '\0'; i++)
    {
        char c = expression[i];

        if (isspace(c))
            continue;

        if (IS_OPEARAND(c))
        {
            struct NODE *newNode = CREATE_LEAF_NODE(c);
            NODE_STACK_PUSH(newNode);
        }
        else if (c == '(')
        {
            STACK_PUSH(c);
        }
        else if (c == ')')
        {
            while (OPERATOR_STACK.A[OPERATOR_STACK.tos] != '(')
            {
                BUILD_SUB_TREE();
            }
            STACK_POP();
        }
        else
        {
            while (OPERATOR_STACK.tos != -1 && OPERATOR_STACK.A[OPERATOR_STACK.tos] != '(' && precedence(OPERATOR_STACK.A[OPERATOR_STACK.tos]) >= precedence(c))
            {
                BUILD_SUB_TREE();
            }
            STACK_PUSH(c);
        }
    }

    while (OPERATOR_STACK.tos != -1)
    {
        BUILD_SUB_TREE();
    }

    return NODE_STACK_POP();
}

/* PREFIX - PREORDER */

void PREFIX(struct NODE *root)
{
    if (root == NULL)
        return;

    printf("%c ", root->item);

    PREFIX(root->left);
    PREFIX(root->right);
}


/* POSTFIX - POSTORDER */

void POSTFIX(struct NODE *root)
{
    if (root == NULL)
        return;

    POSTFIX(root->left);
    POSTFIX(root->right);

    printf("%c ", root->item);
}


int main()
{
    char expression[200];
    printf("\nENTER AN ARITHMETIC EXPRESSION     :     ");
    fgets(expression, sizeof(expression), stdin);

    CONSTRUCT_EXPRESSION_TREE(expression);
}

void STACK_PUSH(char c)
{
    if (OPERATOR_STACK.tos > MAX - 1)
    {
        printf("\nSTACK FULL");
    }
    else
    {
        OPERATOR_STACK.tos++;
        OPERATOR_STACK.A[OPERATOR_STACK.tos] = c;
    }
}

char STACK_POP()
{
    if (OPERATOR_STACK.tos < 0)
    {
        printf("\nSTACK EMPTY");
    }
    else
    {
        char c = OPERATOR_STACK.A[OPERATOR_STACK.tos];
        OPERATOR_STACK.tos--;
        return c;
    }
}

void NODE_STACK_PUSH(struct NODE *c)
{
    if (NODE_STACK.tos > MAX - 1)
    {
        printf("\nSTACK FULL");
    }
    else
    {
        NODE_STACK.tos++;
        NODE_STACK.A[NODE_STACK.tos] = c;
    }
}

struct NODE *NODE_STACK_POP()
{
    if (NODE_STACK.tos < 0)
    {
        printf("\nSTACK EMPTY");
    }
    else
    {
        struct NODE *node = NODE_STACK.A[NODE_STACK.tos];
        NODE_STACK.tos--;
        return node;
    }
}
