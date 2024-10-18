#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

struct Stack {
    int top;
    int items[MAX];
};

// Function to create a stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

// Function to push an item onto the stack
void push(struct Stack* stack, int item) {
    if (stack->top < MAX - 1) {
        stack->items[++stack->top] = item;
    }
}

// Function to pop an item from the stack
int pop(struct Stack* stack) {
    if (stack->top >= 0) {
        return stack->items[stack->top--];
    }
    return -1; // Error code
}

// Function to peek the top item of the stack
int peek(struct Stack* stack) {
    if (stack->top >= 0) {
        return stack->items[stack->top];
    }
    return -1; // Error code
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to get the precedence of operators
int precedence(char op) 
{
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return 0;
}

// Function to perform arithmetic operations
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char* exp, char* postfix) {
    struct Stack* ops = createStack();
    int k = 0;
    for (int i = 0; exp[i]; i++) {
        if (isdigit(exp[i])) {
            postfix[k++] = exp[i];
        } else if (exp[i] == '(') {
            push(ops, exp[i]);
        } else if (exp[i] == ')') {
            while (!isEmpty(ops) && peek(ops) != '(') {
                postfix[k++] = pop(ops);
            }
            pop(ops); // Pop '('
        } else {
            while (!isEmpty(ops) && precedence(peek(ops)) >= precedence(exp[i])) {
                postfix[k++] = pop(ops);
            }
            push(ops, exp[i]);
        }
    }
    while (!isEmpty(ops)) {
        postfix[k++] = pop(ops);
    }
    postfix[k] = '\0';
    free(ops);
}

// Function to evaluate the postfix expression
int evaluatePostfix(char* postfix) {
    struct Stack* values = createStack();
    for (int i = 0; postfix[i]; i++) {
        if (isdigit(postfix[i])) {
            push(values, postfix[i] - '0');
        } else {
            int val2 = pop(values);
            int val1 = pop(values);
            push(values, applyOp(val1, val2, postfix[i]));
        }
    }
    return pop(values);
}

int main() {
    char infix[MAX], postfix[MAX];
    
    printf("Enter infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = 0; // Remove newline character

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}
