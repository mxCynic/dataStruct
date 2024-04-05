typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef int ElementType;

int IsEmpty(Stack S);
Stack CreateStack(void);
void MakeEmpty(Stack S);
void Pop(Stack S);
void Push(Stack S, ElementType x);
ElementType TopElement(Stack S);

struct Node {
  ElementType Element;
  PtrToNode Next;
};
