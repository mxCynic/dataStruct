#include "Stack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int IsEmpty(Stack S) { return S->Next == NULL; }

Stack CreateStack(void) {
  Stack S;

  S = (PtrToNode)malloc(sizeof(struct Node));

  if (S == NULL) {
    perror("OUT OF SPACE!");
  }
  MakeEmpty(S);
  return S;
}

void MakeEmpty(Stack S) {
  if (S == NULL) {
    perror("Must use CreateStack first!");
  }
  while (!IsEmpty(S)) {
    Pop(S);
  }
}

void Pop(Stack S) {
  // tmp useed to store top Node
  PtrToNode tmp;

  if (S == NULL) {
    perror("Must use CreateStack first!");
  } else {
    // free the top of Stack
    tmp = S->Next;
    S->Next = S->Next->Next;
    free(tmp);
  }
}

void Push(Stack S, ElementType x) {
  PtrToNode newNode;
  newNode = (PtrToNode)malloc(sizeof(struct Node));

  if (S == NULL || newNode == NULL) {
    perror("Must use CreateStack first Or failed to create new node!");
  } else {
    newNode->Element = x;
    newNode->Next = S->Next;
    S->Next = newNode;
  }
}

ElementType TopElement(Stack S) {
  if (!IsEmpty(S)) {
    return S->Next->Element;
  } else {
    perror("Emepty Stack!");
    return 0;
  }
}
