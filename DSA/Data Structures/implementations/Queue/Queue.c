#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int arr[MAX_SIZE];
    int front, rear;
} Queue;

void initialize(Queue *queue){
    queue->front = -1;
    queue->rear = -1;
}

int isEmpty(Queue *queue){
    return queue->front == -1;
}

int isFull(Queue *queue){
    return (queue->rear + 1) % MAX_SIZE == queue->front;
}

void enqueue(Queue *queue, int data){
    if(isFull(queue)){
        printf("Cannot enqueue. Queue is full\n");
        return;
    }

    if(isEmpty(queue)){
        queue->front = 0;
        queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % MAX_SIZE;
    }

    queue->arr[queue->rear] = data;
}

int dequeue(Queue *queue){
    if(isEmpty(queue)){
        printf("Cannot dequeue. Queue if empty\n");
        return -1;
    }

    int data = queue->arr[queue->front];

    if(queue->front == queue->rear){
        // Last element in the queue
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % MAX_SIZE;
    }

    return data;
}

int front(Queue *queue){
    if(isEmpty(queue)){
        printf("Queue is empty\n");
        return -1;
    }

    return queue->arr[queue->front];
}

int rear(Queue *queue){
    if(isEmpty(queue)){
        printf("Queue is empty\n");
        return -1;
    }

    return queue->arr[queue->rear];
}

void display(Queue *queue){
    if(isEmpty(queue)){
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");

    int i = queue->front;
    while(i != queue->rear){
        printf("%d ", queue->arr[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("%d\n", queue->arr[i]);
}

int main(){
    Queue queue;
    initialize(&queue);
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    display(&queue); // Queue: 10 20 30
    printf("Element removed: %d\n", dequeue(&queue)); // Element removed: 10
    printf("Element removed: %d\n", dequeue(&queue)); // Element removed: 20
    display(&queue); // Queue: 30
    printf("Element removed: %d\n", dequeue(&queue)); // Element removed: 30
    display(&queue); // Queue is empty

    return 0;
}