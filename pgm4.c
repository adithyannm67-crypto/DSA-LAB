#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

int push(char x)
{
    if (top == MAX - 1)
    {
        printf("Stack Overflow!\n");
        return 0;
    }

    stack[++top] = x;
    return 1;
}

char pop()
{
    if (top == -1)
    {
        printf("Stack Underflow!\n");
        return '\0';
    }

    return stack[top--];
}

char peek()
{
    if (top == -1)
        return '\0';

    return stack[top];
}

int precedence(char x)
{
    if (x == '^')
        return 3;
    if (x == '*' || x == '/')
        return 2;
    if (x == '+' || x == '-')
        return 1;

    return 0;
}

int infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char ch;

    top = -1;

    if (strlen(infix) == 0)
    {
        printf("Empty expression!\n");
        return 0;
    }

    for (i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        if (isdigit(ch))
            postfix[j++] = ch;

        else if (ch == '(')
        {
            if (!push(ch))
                return 0;
        }

        else if (ch == ')')
        {
            while (top != -1 && peek() != '(')
                postfix[j++] = pop();

            if (top == -1)
            {
                printf("Mismatched parentheses!\n");
                return 0;
            }

            pop();
        }

        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/' || ch == '^')
        {
            while (top != -1 &&
                   peek() != '(' &&
                   precedence(peek()) >= precedence(ch))
            {
                postfix[j++] = pop();
            }

            if (!push(ch))
                return 0;
        }

        else
        {
            printf("Invalid character: %c\n", ch);
            return 0;
        }
    }

    while (top != -1)
    {
        if (peek() == '(')
        {
            printf("Mismatched parentheses!\n");
            return 0;
        }

        postfix[j++] = pop();
    }

    postfix[j] = '\0';

    return 1;
}

int evaluatePostfix(char postfix[], int *valid)
{
    int s[MAX];
    int t = -1;
    int i;
    int a, b;

    *valid = 0;

    if (strlen(postfix) == 0)
    {
        printf("Empty postfix expression!\n");
        return 0;
    }

    for (i = 0; postfix[i] != '\0'; i++)
    {
        if (isdigit(postfix[i]))
        {
            if (t == MAX - 1)
            {
                printf("Evaluation stack overflow!\n");
                return 0;
            }

            s[++t] = postfix[i] - '0';
        }

        else
        {
            if (t < 1)
            {
                printf("Invalid postfix expression!\n");
                return 0;
            }

            b = s[t--];
            a = s[t--];

            switch (postfix[i])
            {
                case '+':
                    s[++t] = a + b;
                    break;

                case '-':
                    s[++t] = a - b;
                    break;

                case '*':
                    s[++t] = a * b;
                    break;

                case '/':
                    if (b == 0)
                    {
                        printf("Division by zero!\n");
                        return 0;
                    }

                    s[++t] = a / b;
                    break;

                default:
                    printf("Invalid character: %c\n", postfix[i]);
                    return 0;
            }
        }
    }

    if (t != 0)
    {
        printf("Invalid postfix expression!\n");
        return 0;
    }

    *valid = 1;
    return s[t];
}

int main()
{
    int choice;
    int result;
    int valid;

    char infix[MAX];
    char postfix[MAX];

    while (1)
    {
        printf("\n========== STACK APPLICATIONS ==========\n");
        printf("1. Infix to Postfix\n");
        printf("2. Evaluate Postfix\n");
        printf("3. Exit\n");
        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\nEnter infix expression: ");
                scanf("%99s", infix);

                if (infixToPostfix(infix, postfix))
                    printf("Postfix expression: %s\n", postfix);

                break;

            case 2:
                printf("\nEnter postfix expression: ");
                scanf("%99s", postfix);

                result = evaluatePostfix(postfix, &valid);

                if (valid)
                    printf("Result = %d\n", result);

                break;

            case 3:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
