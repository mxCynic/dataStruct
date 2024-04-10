#define _AVLTREE_H
#include "AVLtree.h"
#include <stdio.h>
#include <stdlib.h>

// 定义AVLtree的节点
struct AVLNode {
  ElementType Element;
  Position Right;
  Position Left;
  int height;
};

// 返回两数中的较大值
int max(int a, int b) { return (a > b) ? a : b; }

// 定义函数，清空树
void MakeEmpty(Tree root) {
  // 实现代码，将二叉树置为空
  if (root != NULL) {
    MakeEmpty(root->Left);
    MakeEmpty(root->Right);
    free(root);
    root = NULL;
  }
}

// 定义函数，查找元素x在树中的位置
Position Find(ElementType x, Tree root) {
  // 实现代码，在二叉搜索树中查找指定元素x的节点位置
  // x 小于当前节点的元素
  while (root != NULL) {
    if (x < root->Element) {
      root = root->Left;
    }
    // x 大于当前节点的元素
    else if (x > root->Element) {
      root = root->Right;
    }
    // x 等于当前节点，返回当前节点
    else {
      return root;
    }
  }
  // 查找完毕，要么树为空，要么树中不存在元素x
  printf("Tree is Empty or there is no %d", x);
  return NULL;
}

// 定义函数，查找树中最小值的位置
Position FindMin(Tree root) {
  // 实现代码，返回二叉搜索树中的最小元素所在节点的位置
  // 测试树是否为空
  if (root == NULL) {
    printf("Tree is Empty!");
    return NULL;
  }
  // 最小值在树的最左端
  while (root->Left != NULL) {
    root = root->Left;
  }

  return root;
}

// 定义函数，查找树中最大值的位置
Position FindMax(Tree root) {
  // 实现代码，返回二叉搜索树中的最大元素所在节点的位置
  // 测试树是否为空
  if (root == NULL) {
    printf("Tree is Empty!");
    return NULL;
  }
  // 最小值在树的最右端
  while (root->Right != NULL) {
    root = root->Right;
  }

  return root;
}

// 定义函数，重心在外，故对以K2为根节点的左子树进行单旋右转操作
Tree SingleRotateLeft(Position K2) {
  // 实现代码，进行一次左旋平衡调整操作
  //        K2           K1
  //       /            /  \
  //      K1    ->    New   K2
  //     /
  //   New
  Position K1;

  K1 = K2->Left;
  K2->Left = K1->Right;
  K1->Right = K2;

  K1->height = max(Height(K1->Left), Height(K1->Right)) + 1;
  K2->height = max(Height(K2->Left), Height(K2->Right)) + 1;

  return K1;
}

// 定义函数，重心在外，故对以K2为根节点的右子树进行单旋左转操作
Tree SingleRotateRight(Position K2) {
  // 实现代码，进行一次右旋平衡调整操作
  //   root                root
  //   / \                 /  \
  //  n   K2              n    K1
  //        \                 /  \
  //         K1       ->     K2  New
  //          \
  //           New

  Position K1;

  K1 = K2->Right;
  K2->Right = K1->Left;
  K1->Left = K2;

  K1->height = max(Height(K1->Left), Height(K1->Right)) + 1;
  K2->height = max(Height(K2->Left), Height(K2->Right)) + 1;

  return K1;
}

// 定义函数，重心在内，对以K3为根节点的左子树进行双旋转操作
Tree DoubleRotateLeft(Position K3) {
  // 实现代码，进行两次连续的左旋平衡调整操作
  // 对K3的左子树做一次右旋(SRL)，使得左子树重心在外
  //        m1 and m2 是老节点  K1-3 是被调整的节点
  //
  //        K3                    K3                 K2
  //       /  \                  /  \               /  \
  //     K1    m2     ->       K2    m2  ->       K1    K3
  //    /  \                  /  \               /     /  \
  //   m1   K2              K1    New           m1   New   m2
  //         |             /
  //         New          m1
  //
  K3->Left = SingleRotateRight(K3->Left);

  // 再调整后只需要对K3的左子树进行一次右旋转,即让K2成为新的根节点
  return SingleRotateLeft(K3);
}

// 定义函数，重心在内，对以K3为根节点的右子树进行双旋右转操作
Tree DoubleRotateRight(Position K3) {
  // 实现代码，进行两次连续的右旋平衡调整操作
  // 对K3的右子树做一次左旋(SRR)，使得右子树重心在外
  K3->Right = SingleRotateLeft(K3->Right);

  // 再调整后只需要对K3的右子树进行一次左旋转,即让K2成为新的根节点
  return SingleRotateRight(K3);
}

// 定义函数，返回树的高度,空树高度为-1
int Height(Position T) {
  if (T == NULL) {
    return -1;
  }
  return T->height;
}

// 定义函数，向树中插入元素x
Tree Insert(ElementType x, Tree root) {
  // 实现代码，在二叉搜索树中插入一个新元素x，并返回更新后的树结构
  // 当前位置为空，初始化当前节点为储存ElementType x的位置
  if (root == NULL) {
    root = malloc(sizeof(*root));
    if (root == NULL) {
      printf("111");
      printf("Out of Space!\n");
      return 0;
    }
    // 成功分配空间，给root初始化
    else {
      root->Element = x;
      root->Left = root->Right = NULL;
      root->height = 0;
    }
  }

  // x bi当前节点元素小，向左树找位置插入

  if (x < root->Element) {
    root->Left = Insert(x, root->Left);
    // 验证当前节点在插入新元素后，是否满足AVLtree条件，
    // 由于root->Left = Insert(x, root->Left);是向左子树插入
    // 因此只有可能左子树比右子树高
    if (Height(root->Left) - Height(root->Right) == 2) {
      // x 被插入的roo左子树的左边，用一次单旋转即可平衡
      if (x < root->Left->Element) {
        root = SingleRotateLeft(root);
      }
      // x 被插入的roo左子树的右边，需要使用双旋转才能平衡
      else {
        root = DoubleRotateLeft(root);
      }
    }
  }

  // x 比当前节点元素大，向右树找位置插入
  else if (x > root->Element) {
    root->Right = Insert(x, root->Right);
    // 验证当前节点在插入新元素后，是否满足AVLtree条件，
    // 由于root->Right = Insert(x, root->Right);是向右子树插入
    // 因此只有可能右子树比左子树高
    if (Height(root->Right) - Height(root->Left) == 2) {
      // x 被插入的root右子树的右边，用一次单旋转即可平衡
      if (x > root->Right->Element) {

        root = SingleRotateRight(root);
      }
      // x 被插入的roo右子树的左边，需要使用双旋转才能平衡
      else {
        root = DoubleRotateRight(root);
      }
    }
  }

  root->height = max(Height(root->Left), Height(root->Right)) + 1;
  // 完成插入后更新父树(两种插入条件的第一行)或返回根节点
  return root;
}

// 定义函数，从树中删除元素x
Tree Delete(ElementType x, Tree root) {
  // 实现代码，从二叉搜索树中删除指定元素x，并返回更新后的树结构
  if (root == NULL) {
    printf("element not found!");
    return NULL;
  }

  // fo left tree
  if (x < root->Element) {
    root->Left = Delete(x, root->Left);
    // 验证当前节点在插入新元素后，是否满足AVLtree条件，
    // 由于root->Left = Insert(x, root->Left);是向左子树插入
    // 因此只有可能左子树比右子树高
    if (Height(root->Left) - Height(root->Right) == 2) {
      // x 被插入的roo左子树的左边，用一次单旋转即可平衡
      if (x < root->Left->Element) {
        SingleRotateLeft(root->Left);
      }
      // x 被插入的roo左子树的右边，需要使用双旋转才能平衡
      else {
        DoubleRotateLeft(root->Left);
      }
    }
  }
  // go right tree
  else if (x > root->Element) {
    root->Right = Delete(x, root->Right);
    // 验证当前节点在插入新元素后，是否满足AVLtree条件，
    // 由于root->Right = Insert(x, root->Right);是向右子树插入
    // 因此只有可能右子树比左子树高
    if (Height(root->Right) - Height(root->Left) == 2) {
      // x 被插入的root右子树的右边，用一次单旋转即可平衡
      if (x > root->Right->Element) {
        SingleRotateRight(root->Right);
      }
      // x 被插入的roo右子树的左边，需要使用双旋转才能平衡
      else {
        DoubleRotateRight(root->Right);
      }
    }
  }
  // find the deleted element
  else {
    if (root->Left && root->Right) {
      Position tmpnode;

      tmpnode = FindMin(root->Right);
      root->Element = tmpnode->Element;
      root->Right = Delete(tmpnode->Element, root->Right);
    } else {
      Position tmpnode;
      tmpnode = root;
      // also handles 0 child
      if (root->Left == NULL) {
        root = root->Right;
      } else {
        root = root->Left;
      }
      free(tmpnode);
      tmpnode = NULL;
    }
  }

  return root;
}

// 定义函数，打印树结构
// void printTree(Tree root) {
//   // 实现代码，按先序遍历并打印二叉树的所有节点信息
//   if (root == NULL) {
//     return;
//   }
//   printTree(root->Left);
//   printf("%d ", root->Element);
//   printTree(root->Right);
// }
void printTree1(Tree root, int space) {
  // 基本情况，根为空
  if (root == NULL)
    return;

  // 增加间隔，以区分不同深度的节点
  space += 10;

  // 先处理右子树（在控制台中，右子树在上方）
  printTree1(root->Right, space);

  // 打印当前节点
  printf("\n");
  for (int i = 10; i < space; i++)
    printf(" ");
  printf("%d\n", root->Element);

  // 处理左子树（在控制台中，左子树在下方）
  printTree1(root->Left, space);
}
// 如何用树状结构打印出一个带height的Tree,请用c语言实现
