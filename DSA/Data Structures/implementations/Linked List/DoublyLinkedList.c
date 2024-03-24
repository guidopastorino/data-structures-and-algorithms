#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _DNode {
  int data;
  struct _DNode* prev;
  struct _DNode* next;
} Node;

Node* create_node(int data){
  Node* newNode = (Node*)malloc(sizeof(Node));
  assert(newNode != NULL);
  newNode->data = data;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

void insert_begin(Node** head, int data){
  Node* newNode = create_node(data);
  if(*head == NULL){
    *head = newNode;
  } else {
    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
  }
}

void insert_end(Node** head, int data){
  Node* newNode = create_node(data);
  if(*head == NULL){
    *head = newNode;
  } else {
    Node* current = *head;
    while(current->next != NULL){
      current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
  }
}

void insert_position(Node** head, int pos, int data){
  assert(pos >= 0);
  if(pos == 0){
    insert_begin(head, data);
    return;
  }
  Node* newNode = create_node(data);
  Node* current = *head;
  for(int i = 0; i<pos-1 && current != NULL; i++){
    current = current->next;
  }
  assert(current != NULL);
  newNode->next = current->next;
  if(current->next != NULL){
    current->next->prev = newNode;
  }
  current->next = newNode;
  newNode->prev = current;
}

void delete_begin(Node** head){
  assert(*head != NULL);
  Node* temp = *head;
  *head = (*head)->next;
  if(*head != NULL){
    (*head)->prev = NULL;
  }
  free(temp);
}

void delete_end(Node** head){
  assert(*head != NULL);
  if((*head)->next == NULL){
    delete_begin(head);
    return;
  }
  Node* current = *head;
  while(current->next != NULL){
    current = current->next;
  }
  if(current->prev != NULL){
    current->prev->next = NULL;
  } else {
    *head = NULL;
  }
  free(current);
}

void delete_position(Node** head, int pos){
  assert(*head != NULL && pos >= 0);
  if(pos == 0){
    delete_begin(head);
    return;
  }
  Node* current = *head;
  for(int i = 0; i<pos && current != NULL; i++){
    current = current->next;
  }
  assert(current != NULL);
  if(current->next != NULL){
    current->next->prev = current->prev;
  }
  current->prev->next = current->next;
  free(current);
}

void display_forward(Node* head){
  Node* current = head;
  while(current != NULL){
    printf("%d -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

void display_backward(Node* head){
  Node* current = head;
  while(current != NULL && current->next != NULL){
    current = current->next;
  }
  while(current != NULL){
    printf("%d -> ", current->data);
    current = current->prev;
  }
  printf("NULL\n");
}

void free_list(Node* head){
  Node* current = head;
  while(current != NULL){
    Node* temp = current;
    current = current->next;
    free(temp);
  }
}

void empty_list(Node** head){
  while(*head != NULL){
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
  }
}

int main(){
  Node* head = NULL;
  
  for(int i = 10; i<=50; i+=10){
    insert_end(&head, i);
  }

  display_forward(head); // 10 -> 20 -> 30 -> 40 -> 50 -> NULL
  insert_end(&head, 60);
  display_forward(head); // 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> NULL
  insert_begin(&head, 5);
  display_forward(head); // 5 -> 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> NULL
  insert_position(&head, 7, 70);
  display_forward(head); // 5 -> 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70 -> NULL
  delete_begin(&head);
  display_forward(head); // 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> 70 -> NULL
  delete_end(&head);
  display_forward(head); // 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> NULL
  delete_position(&head, 3);
  display_forward(head); // 10 -> 20 -> 30 -> 50 -> 60 -> NULL
  delete_position(&head, 2);
  display_forward(head); // 10 -> 20 -> 50 -> 60 -> NULL
  display_backward(head); // 60 -> 50 -> 20 -> 10 -> NULL

  empty_list(&head);
  display_forward(head); // NULL

  free_list(head);

  return 0;
}