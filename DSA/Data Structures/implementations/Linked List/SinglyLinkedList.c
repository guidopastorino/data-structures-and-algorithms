#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _SNode {
  int data;
  struct _SNode* next;
} Node;

Node* create_node(int data){
  Node* newNode = (Node*)malloc(sizeof(Node));
  assert(newNode != NULL);
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void insert_begin(Node** head, int data){
  Node* newNode = create_node(data);
  newNode->next = *head;
  *head = newNode;
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
  current->next = newNode;
}

void delete_begin(Node** head){
  assert(*head != NULL);
  Node* temp = *head;
  *head = (*head)->next;
  free(temp);
}

void delete_end(Node** head){
  assert(*head != NULL);
  if((*head)->next == NULL){
    delete_begin(head);
    return;
  }
  Node* current = *head;
  while(current->next->next != NULL){
    current = current->next;
  }
  free(current->next);
  current->next = NULL;
}

void delete_position(Node** head, int pos){
  assert(*head != NULL && pos >= 0);
  if(pos == 0){
    delete_begin(head);
    return;
  }
  Node* current = *head;
  Node* temp;
  for(int i = 0; i<pos-1 && current != NULL; i++){
    current = current->next;
  }
  temp = current->next;
  current->next = current->next->next;
  free(temp);
}

int list_length(Node* head){
  Node* current = head;
  int len = 0;
  while(current != NULL){
    current = current->next;
    len++;
  }
  return len;
}

void display_list(Node* head){
  Node* current = head;
  while(current != NULL){
    printf("%d -> ", current->data);
    current = current->next;
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

int main(){
  Node* head = NULL;

  for(int i = 10; i<=50; i+=10){
    insert_end(&head, i);
  }

  display_list(head); // 10 -> 20 -> 30 -> 40 -> 50 -> NULL
  delete_begin(&head);
  display_list(head); // 20 -> 30 -> 40 -> 50 -> NULL
  delete_end(&head);
  display_list(head); // 20 -> 30 -> 40 -> NULL
  delete_position(&head, 1);
  display_list(head); // 20 -> 40 -> NULL
  insert_begin(&head, 10);
  display_list(head); // 10 -> 20 -> 40 -> NULL
  insert_end(&head, 50);
  display_list(head); // 10 -> 20 -> 40 -> 50 -> NULL
  insert_position(&head, 2, 30);
  display_list(head); // 10 -> 20 -> 30 -> 40 -> 50 -> NULL

  printf("List length: %d\n", list_length(head));

  free_list(head);

  return 0;
}