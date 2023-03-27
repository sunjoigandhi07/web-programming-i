#include <stdio.h>
#include <stdlib.h> // malloc
#include "linkedList.h"

LinkedList* llCreate() {
  return NULL;
}

int llIsEmpty(LinkedList* ll) {
  return (ll == NULL);
}

void llDisplay(LinkedList* ll) {
  
  LinkedList* p = ll;
  printf("[");

  
  while (p != NULL) {
    printf("%f, ", (*p).value->weight);
    p = p->next;
  }
  printf("]\n");
}

struct tnode* llRemoveFirst(LinkedList** ll) {

  struct node *tempLink = *ll;

  if(tempLink->next == NULL) {
    *ll = NULL;
    return tempLink->value;
  } else {
    *ll = tempLink->next;
    return tempLink->value;
  }
}

/*
void llFree(LinkedList* ll) {
  LinkedList* p = ll;
  while (p != NULL) {
    LinkedList* oldP = p;
    p = p->next;
    free(oldP);
  }
}
*/
void llFree(struct tnode* f) {
  free(f);
}


void list_add_in_order(LinkedList** ll, struct tnode* newValue) {
  LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
  newNode->value = newValue;
  newNode->next = NULL;

  LinkedList* p = *ll;
  if (p == NULL) {  // Add first element
    *ll = newNode;  // This is why we need ll to be a **
  }
  else {
 
    struct node *temp ,*prev; //sc
    struct node* l = *ll;
      
    if(newNode->value->weight < l->value->weight) {

      newNode->next = l;
      *ll = newNode;

    }

    else {

      temp = l;

      while(temp != NULL && temp->value->weight <= newValue->weight) {
	prev = temp; 
	temp = temp->next;
      }

      newNode->next = temp;
      prev->next = newNode;
    }
  }
}

/*
int main() {
  
  LinkedList* l = llCreate();
  struct tnode* a = (struct tnode*)malloc(sizeof(struct tnode));
  a->c = 97;
  a->weight = 3;
  
  struct tnode* b = (struct tnode*)malloc(sizeof(struct tnode));
  b->c = 98;
  b->weight = 2;
  
  struct tnode* c = (struct tnode*)malloc(sizeof(struct tnode));
  c->c = 99;
  c->weight = 4;
  
  struct tnode* d = (struct tnode*)malloc(sizeof(struct tnode));
  d->c = 100;
  d->weight = 1;

  
  llDisplay(l);
  list_add_in_order(&l, a);
  //llDisplay(l);
  list_add_in_order(&l, b);
  //llDisplay(l);
  list_add_in_order(&l, c);
  //llDisplay(l);
   list_add_in_order(&l, d);
   // llDisplay(l);

   
   llDisplay(l);
   
  llFree(l);
}

*/
