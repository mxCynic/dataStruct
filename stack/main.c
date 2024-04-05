#include "Stack.c"
#include <stdio.h>

int main() {
  printf("hello world!\n");
  Stack Head = CreateStack();
  int status = IsEmpty(Head);
  printf("status is %d!\n", status);

  Push(Head, 1);
  int top = TopElement(Head);
  printf("top element is %d!\n", top);
  status = IsEmpty(Head);
  printf("status is %d!\n", status);

  Push(Head, 2);
  top = TopElement(Head);
  printf("top element is %d now!\n", top);

  Pop(Head);
  top = TopElement(Head);
  printf("top element is %d now!\n", top);

  MakeEmpty(Head);
  status = IsEmpty(Head);
  printf("status is %d!\n", status);
}
