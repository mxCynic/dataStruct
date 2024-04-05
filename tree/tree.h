#ifndef _ADT_TREE_H

struct TreeNode;
typedef struct TreeNode *Position;
typedef Position Tree;
typedef int Elementype;

void MakeEmpty(Tree root);
Position Find(Elementype x, Tree root);
Position FindMin(Tree root);
Position FindMax(Tree root);
Tree Insert(Elementype x, Tree root);
Tree Delete(Elementype x, Tree root);
void printTree(Tree root);

#endif

struct TreeNode {
  Elementype Element;
  Tree Right;
  Tree Left;
};
