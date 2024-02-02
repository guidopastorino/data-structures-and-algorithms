// SINGLY LINKED LIST IMPLEMENTATION IN C

#include <stdio.h>
#include <stdlib.h>

// struct of a Node
// data: The data that the Node will storage
// next: A pointer to the next Node

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Operations

// CREATE A NODE
// Given a data, the function returns a new node with the data and a pointer to the next (NULL)
// The new node will always be added at the end of the Linked List (new node is the tail)
Node *createNode(int data){
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        printf("Error to assign memory for the new node\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
}

// COUNT ELEMENTS WITHIN THE LINKED LIST
int getListLength(Node *head){
    Node *current = head;
    int len = 0;
    while(current != NULL){
        len++;
        current = current->next;
    }
    return len;
}

// INSERT AT THE BEGIN
// Inserts a new node at the beginning of the linked list, making the newly inserted node the new head of the linked list.
void insertAtBegin(Node **head, int data){
    Node *newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// INSERT AT THE END
// Inserts a new node at the end of the linked list, making the newly inserted node the new tail of the linked list
void insertAtEnd(Node **head, int data){
    Node *newNode = createNode(data);
    if(*head == NULL){
        *head = newNode;
    } else {
        Node *current = *head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
}

// INSERT IN A POSITION
// Inserts a new node at a specified position within the linked list.
void insertAtPosition(Node **head, int data, int pos){
    if(pos <= 0){
        printf("Invalid position number.\n");
        return;
    }

    Node *newNode = createNode(data);

    if(pos == 1){
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node *current = *head;
    int i = 1;

    while(i < pos - 1 && current != NULL){
        current = current->next;
        i++;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// DELETE THE BEGIN
// Removes the first node from the linked list, making the next node the new head of the list.
void deleteAtBegin(Node **head){
    if(*head == NULL){
        printf("La lista está vacía.\n");
        return;
    }
    Node *temp = *head;
    *head = (*head)->next;
    free(temp);
}

// DELETE THE END
// Removes the last node from the linked list, making the previous node the new tail of the list.
void deleteAtEnd(Node **head){
    if(*head == NULL){
        printf("The list is empty.\n");
        return;
    }

    if((*head)->next == NULL){
        free(*head);
        *head = NULL;
        return;
    }

    Node *current = *head;

    while(current->next->next != NULL){
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
}

// DELETE A POSITION
// Removes a node from a specified position within the linked list. 
void deleteAtPosition(Node **head, int pos){
    if(pos <= 0){
        printf("Invalid position number.\n");
        return;
    }

    if(pos == 1){
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    Node *current = *head;
    int i = 1;

    while(i < pos - 1 && current != NULL){
        current = current->next;
        i++;
    }

    if(current == NULL || current->next == NULL){
        printf("Position index out of range.\n");
        return;
    }

    Node *temp = current->next;
    current->next = current->next->next;
    free(temp);
}

// SEARCH
// Returns 1 if node (target) exists, otherwise returns 0
int search(Node *head, int target){
    Node *current = head;
    while(current != NULL){
        if(current->data == target){
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// DISPLAY
// Displays the contents of the linked list by traversing the nodes from the head to the tail, using "->" to indicate the connections between nodes in the list.
void display(Node *head){
    Node *current = head;
    while(current != NULL){
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main(){
    Node *head = NULL; // Initializing the linked list

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtBegin(&head, 30);
    display(head); // 30 -> 10 -> 20 -> NUL
    printf("Linked List length: %d\n", getListLength(head)); // Linked List length: 3
    deleteAtBegin(&head);
    display(head); // 10 -> 20 -> NULL
    deleteAtPosition(&head, 2);
    display(head); // 10 -> NULL
    insertAtPosition(&head, 20, 2);
    display(head); // 10 -> 20 -> NULL
    deleteAtEnd(&head);
    display(head); // 10 -> NULL
    deleteAtBegin(&head);
    display(head); // NULL
    deleteAtBegin(&head); // La lista está vacía.


    free(head);
}