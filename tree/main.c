#include "tree.c"
#include <stdio.h>

#define _ADT_TREE_H

int main() {
  Tree peaches = NULL;
  MakeEmpty(peaches);

  printf("yes\n");

  // for (int i = 10; i > 5; i--) {
  //   peaches = Insert(i, peaches);
  // }
  for (int i = 10; i < 21; i += 2) {
    peaches = Insert(i, peaches);
  }
  for (int i = 11; i < 21; i += 2) {
    peaches = Insert(i, peaches);
  }
  printTree(peaches);

  printf("\n\nFind the mininal node\n");
  Tree min = NULL;
  min = FindMin(peaches);
  printTree(min);

  printf("\n\nFind the maximum node\n");
  Tree max = NULL;
  max = FindMax(peaches);
  printTree(max);

  printf("\n\nFind the x note(x equal to 16)\n");
  Tree x = NULL;
  x = Find(16, peaches);
  printTree(x);

  printf("\n\ndelete the x note(x equal to 13)\n");
  Tree afterDelete = NULL;
  peaches = Delete(12, peaches);
  printf("%d", peaches->Right->Element);
  printf("yes\n");
  printf("%d\n", peaches->Right->Right->Left->Element);
  printTree(peaches);

  return 0;
}
