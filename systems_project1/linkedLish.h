#include <stdio.h>
#include <stdlib.h>

struct tnode {
  double weight;
  int c;
  struct tnode* left;
  struct tnode* right;
  struct tnode* parent;
};
 
typedef struct node {
  struct tnode* value;

  struct node* next;
} LinkedList;

LinkedList* llCreate();
int llIsEmpty(LinkedList* ll);
void llDisplay(LinkedList* ll);
void llAdd(LinkedList** ll, int newValue);
void llFree(struct tnode* f);
struct tnode* llRemoveFirst(LinkedList** ll);
void list_add_in_order(LinkedList** ll, struct tnode* newValue);


