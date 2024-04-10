#include "AVLtree.c"
#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("hello!\n");

  Tree num;
  MakeEmpty(num);

  num = Insert(4, num);
  num = Insert(2, num);
  for (int i = 1; i < 100; i += 2) {
    num = Insert(i, num);
  }
  for (int i = 2; i < 100; i += 2) {
    num = Insert(i, num);
  }
  num = Delete(54, num);

  printTree1(num, 0);

  // printTree(num);
  printf("\n");
  printf("root: %d height: %d", num->Element, num->height);

  return 0;
}
