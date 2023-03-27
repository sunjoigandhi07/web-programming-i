#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"



struct tnode* GenerateFreqTable(const char* filename) {

  FILE* fp;
  fp = fopen(filename, "r");

  int ch;
  int count;
  struct tnode* freq = (struct tnode*)malloc(128 * sizeof(struct tnode));
  for(int i = 0; i < 128; i++) {
    freq[i].c = i;
    freq[i].weight = 0;
  }

  while(ch != EOF) {
    ch = fgetc(fp);
    freq[ch].weight += 1;
  }

  fclose(fp);
  
  return freq; 
}


struct tnode* CreateHuffmanTree(struct tnode* nodes) {
  
  LinkedList* list = llCreate();

  for(int i = 0; i < 128; i++) {
    list_add_in_order(&list, &nodes[i]); //add all characters in order to the linked list
    
  }

  for(int i = 0; i < 127; i++) {
    
   
    struct tnode* node1 = llRemoveFirst(&list); //take the two smallest values from the linked list
    struct tnode* node2 = llRemoveFirst(&list);

    struct tnode* tempNode = (struct tnode*)malloc(1 * sizeof(struct tnode));
    tempNode->left = node1;
    tempNode->right = node2;

    node1->parent = tempNode;
    node2->parent = tempNode;
    
    tempNode->weight = node1->weight + node2->weight;
    tempNode->c = '\0';

    list_add_in_order(&list, tempNode);
  
  }

  return llRemoveFirst(&list);
}


void EncodeFile(char* file, struct tnode* leaf) {

  struct tnode* current = leaf;

  int ch = 0;
  
  FILE* fp;
  fp = fopen(file, "r");

  FILE* fph; 
  char* filehuf = strcat(file, ".huf");
  fph = fopen(filehuf, "w");
  
  while(ch != EOF) {
    ch = fgetc(fp);

    unsigned int path; //path that maintains the 0s and 1s while we move up the tree
    char temp; //temp stores the 8 bits to be written out
    int pathCount; 
    int tempCount = 0;

    while(current[ch].parent != NULL) {
      pathCount = 0;

      path = path << 1; 

      struct tnode* tempLeft = current[ch].parent->left;
      struct tnode* tempRight = current[ch].parent->right;

      if(tempRight == &current[ch]) {
	path = path & 1;
      }
      
      pathCount++; 

      current = current->parent;
    }

    for(int i = 0; i < pathCount; i++) {
      temp = temp << 1; //open a space in temp
      temp = path & 1; //single out last bit of path and add it to temp
      path = path >> 1; //shift path right to get the next bit
      tempCount++;

      if(tempCount == 8) {
	fputc(temp, fph);
	tempCount = 0;
      } 
    }
  }
}

void DecodeFile(char* huffile, struct tnode* root) {

  int ch = 0;

  FILE* fph; 
  fph = fopen(huffile, "r");
  
  FILE* fp;
  char* file = strcat(huffile, ".dec");
  fp = fopen(file, "w");

  while(ch != EOF) { //runs until the file has no more elements

    struct tnode* current = root; //declare this inside the loop to start at the root every time

    ch = fgetc(fph);

    while(current->left != NULL && current->right != NULL) { //runs until current is a leaf node
    
      if(ch == 1) {
	current = current->right;
      } else if(ch == 0) {
	current = current->left;
      }
    }
    
    int temp = current->c;
    fputc(temp, fp);
  }
}


int main(int argc, char *argv[]) {

  // Check the make sure the input parameters are correct
   if (argc != 3) {
      printf("Error: The correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf\"\n"); fflush(stdout);

    exit(1);
  }


  // Create the frequency table by reading the generic file
   struct tnode* leafNodes = GenerateFreqTable("decind.txt");
  // Create the huffman tree from the frequency table
   struct tnode* treeRoot = CreateHuffmanTree(leafNodes);
   

  if (strcmp(argv[1], "-e") == 0) {
    // Pass the leafNodes since it will process bottom up
    EncodeFile(argv[2], leafNodes);
  } else {
    // Pass the tree root since it will process top down
    DecodeFile(argv[2], treeRoot);
  }

  for(int i = 0; i < 128; i++) {
    free(leafNodes);
    free(treeRoot); 
  }

  return 0;
	
}
