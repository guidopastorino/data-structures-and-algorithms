// STACK IMPLEMENTATION IN C

#include <stdio.h>

#define MAX_SIZE 100 // The max length of elements that can be stored in the Stack

// Initial structure of a Stack
typedef struct {
    int top;
    int elements[MAX_SIZE];
} Stack;

// Initializing the Stack. The top will be -1
void initialize(Stack *stack){
    stack->top = -1;
}

// Check if the Stack is empty and returns 1, otherwise, returns 0
int isEmpty(Stack *stack){
    return stack->top == -1;
}

// Check if the Stack is full (no more elements can de stored) and returns 1, otherwise, returns 0
int isFull(Stack *stack){
    return stack->top == MAX_SIZE - 1;
}

// Given the Stack and a value, adds a new element at the top of the stack. The top now is the new value.
void push(Stack *stack, int data){
    if(isFull(stack)){
        printf("The stack is full\n");
        return;
    }
    stack->elements[++stack->top] = data; // Incrementing the top and then adding the new element
}

// Removes the last element added into the Stack. If the stack is empty, returns -1, otherwise, returns the popped element.
int pop(Stack *stack){
    if(isEmpty(stack)){
        printf("The stack is empty\n");
        return -1;
    }

    return stack->elements[stack->top--];
}

// Returns the top element, if the Stack is empty, returns -1.
int peek(Stack *stack){
    if(isEmpty(stack)){
        return -1;
    }
    return stack->elements[stack->top];
}

// Returns the length of the elements in the Stack.
int size(Stack *stack){
    return stack->top + 1;
}

// Prints all elements stored into the Stack
void display(Stack *stack){
    if(isEmpty(stack)){
        printf("The stack is empty\n");
        return;
    }
    printf("Stack: ");
    for(int i = 0; i<(stack->top + 1); i++){
        printf("%d ", stack->elements[i]);
    }
    printf("\n");
}


int main(){
    Stack stack;
    initialize(&stack);

    
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    printf("Top: %d\n", peek(&stack)); // Top: 30
    pop(&stack);
    pop(&stack);
    pop(&stack);
    display(&stack); // The stack is empty
    push(&stack, 100);
    push(&stack, 200);
    push(&stack, 300);
    push(&stack, 400);
    push(&stack, 500);
    display(&stack); // Stack: 100 200 300 400 500
    printf("Top: %d\n", peek(&stack)); // Top: 500
}