#ifdef _AVLTREE_H
struct AVLNode;
typedef struct AVLNode *Position;
typedef Position Tree;
typedef int ElementType;
void MakeEmpty(Tree root);
Position Find(ElementType x, Tree root);
Position FindMin(Tree root);
Position FindMax(Tree root);
Tree Insert(ElementType x, Tree root);
Tree Delete(ElementType x, Tree root);
Tree SingleRatoteLeft(Position K2);
Tree DoubleRatoteLeft(Position K3);
Tree SingleRatoteRight(Position K2);
Tree DoubleRatoteRight(Position K3);
int Height(Position T);
void printTree(Tree root);

#endif // DEBUG
