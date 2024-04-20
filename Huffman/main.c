#include <stdio.h>
#include <stdlib.h>

typedef struct Hnode {
  int weight;
  struct Hnode *lchild, *rchild;
} *Htree;

Htree CreateHuffmanTree(int arr[], int n);
void midprintree(Htree root);
void frontprintree(Htree root);

int main(int argc, char *argv[]) {
  int array[8] = {19, 17, 13, 11, 7, 5, 3, 1};
  printf("array is : ");

  for (int *i = array; i < (array + 8); i++) {
    printf("%d ", *i);
  }

  Htree a;
  a = CreateHuffmanTree(array, 8);

  printf("\n 中序：");
  midprintree(a);
  printf("\n 先序：");
  frontprintree(a);

  return 0;
}

// 接受一个数组，代表不同的权重，和数组大小n
// 返回一个huffman树
Htree CreateHuffmanTree(int arr[], int n) {
  // 最后要返回的树
  Htree root = NULL;
  // 储存权重的森林
  Htree forest[n];

  // 初始化森林
  for (int i = 0; i < n; i++) {
    Htree tmp;
    tmp = malloc(sizeof(*tmp));
    tmp->weight = arr[i];
    tmp->lchild = tmp->rchild = NULL;
    forest[i] = tmp;
  }

  // 找到权重最小的两个树的下标,然后循环n-1次创建huffman树
  for (int i = 0; i < n - 1; i++) {
    int minn = -1; // minn 是最小树下标
    int minsub;    // minsub是次小树下标

    // 在森林中找到两棵非空树
    for (int j = 0; j < n; j++) {
      // 首先在森林中找到第一个非空树,将这颗树的下标赋值给minn
      if (forest[j] != NULL && minn == -1) {
        minn = j;
      }

      // 再找到第二课非空树,将这颗树的下标赋值给mjnsub
      else if (forest[j] != NULL) {
        minsub = j;
        break;
      }
    }

    // 然后再更新这两个下标，使得他们对应权重最小的两棵树
    // TODO:为什么这里的j不能从0开始，我能理解可以从minsub开始，但是为什么不能从0开始
    for (int j = minsub; j < n; j++) {
      // 循环到第j课树，但是这颗树为空，跳过
      if (forest[j] == NULL)
        continue;

      // 更新最小权重的下标
      if (forest[j]->weight < forest[minn]->weight) {
        minsub = minn;
        minn = j;
      } else if (forest[j]->weight < forest[minsub]->weight) {
        minsub = j;
      }
    }

    // 构建本次循环的huffman树
    root = malloc(sizeof(*root));
    root->weight = forest[minn]->weight + forest[minsub]->weight;
    // 权重较小的在左边，较大的在右边
    root->lchild = forest[minn];
    root->rchild = forest[minsub];

    // 更新森林
    forest[minn] = root;
    forest[minsub] = NULL;
  }

  return root;
}

void midprintree(Htree root) {
  if (root == NULL) {
    return;
  }
  midprintree(root->lchild);
  printf("%d ", root->weight);
  midprintree(root->rchild);
}
void frontprintree(Htree root) {
  if (root == NULL) {
    return;
  }
  printf("%d ", root->weight);
  frontprintree(root->lchild);
  frontprintree(root->rchild);
}
