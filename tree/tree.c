#include "tree.h"

#include <stdio.h>
#include <stdlib.h>

// 用于清空（初始化）树结构。
void MakeEmpty(Tree root) {
  if (root != NULL) {
    MakeEmpty(root->Left);
    MakeEmpty(root->Right);
    free(root);
    root = NULL;
  }
}

// 实现查找功能，根据给定元素`x`找到其在树`root`中的位置（Position）。
Position Find(Elementype x, Tree root) {
  if (root == NULL) {
    printf("this tree is NULL OR there is no %d in this tree\n", x);
    return NULL;
  }

  if (root->Element < x) {
    return Find(x, root->Right);
  } else if (root->Element > x) {
    return Find(x, root->Left);
  } else {
    return root;
  }
}

// 查找树`root`中的最小值节点的位置。
Position FindMin(Tree root) {
  if (root == NULL) {
    printf("this tree is NULL");
    return NULL;
  }

  Position minPos = root;
  while (root->Left != NULL) {
    root = root->Left;
    minPos = root;
  }
  return minPos;
}

// 查找树`root`中的最大值节点的位置。
Position FindMax(Tree root) {
  if (root == NULL) {
    printf("this tree is NULL");
    return NULL;
  }

  Position maxPos = root;
  while (root->Right != NULL) {
    root = root->Right;
    maxPos = root;
  }
  return maxPos;
}

// 实现了将元素`x`插入到二叉搜索树`root`中的功能。
Tree Insert(Elementype x, Tree root) {
  if (root == NULL) {
    root = (Tree)malloc(sizeof(Tree));
    if (root == NULL) {
      printf("OUT OF SPACE!");
      exit(1);
    } else {
      root->Element = x;
      root->Right = root->Left = NULL;
    }
  }

  else if (x < root->Element) {
    root->Left = Insert(x, root->Left);

  } else if (x > root->Element) {
    root->Right = Insert(x, root->Right);
  }

  return root;
}

// 实现删除操作，从树`root`中移除指定元素`x`的节点
Tree Delete(Elementype X, Tree T) {
  Position TmpCell;

  if (T == NULL)
    printf("Element not found");
  else if (X < T->Element) /* Go left */
    T->Left = Delete(X, T->Left);
  else if (X > T->Element) /* Go right */
    T->Right = Delete(X, T->Right);
  /* Found element to be deleted */
  else if (T->Left && T->Right) /* Two children */
  {
    /* Replace with smallest in right subtree */
    TmpCell = FindMin(T->Right);
    T->Element = TmpCell->Element;
    T->Right = Delete(T->Element, T->Right);
  } else /* One or zero children */
  {
    TmpCell = T;
    if (T->Left == NULL) /* Also handles 0 children */
      T = T->Right;
    else if (T->Right == NULL)
      T = T->Left;
    free(TmpCell);
  }

  return T;
}
// 实现删除操作，从树`root`中移除指定元素`x`的节点
// Tree Delete(Elementype x, Tree root) {
//   Position tmp = Find(x, root);
//   Position tmpbeFree;
//   if (tmp == NULL) {
//     return root;
//   }
//
//   // tmp's child is full
//   if (tmp->Left != NULL && tmp->Right != NULL) {
//     // find the min note at left tree
//     Position LeftMin = FindMin(tmp->Right);
//
//     tmp->Element = LeftMin->Element;
//     tmp->Right = Delete(LeftMin->Element, tmp->Right);
//   } else {
//     tmpbeFree = tmp;
//
//     // left child is NULL (right child NULL or exist is ok)
//     if (tmp->Left == NULL) {
//       tmp = tmp->Right;
//     } else if (tmp->Right == NULL) {
//       tmp = tmp->Left;
//     }
//     free(tmpbeFree);
//   }
//
//   return root;
// }
//
// 以中序遍历的方式打印二叉搜索树的所有节点值。
void printTree(Tree root) {
  if (root == NULL) {
    return;
  }
  printf("%d ", root->Element);
  printTree(root->Left);
  printTree(root->Right);
}
