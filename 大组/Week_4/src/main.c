#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVL_tree.h"
#include "max_heap.h"
#include "min_heap.h"
#include "binary_sort_tree.h"
#include "red_black_tree.h"

void printBST(NodePtr node)
{
    if (node == NULL)
        return;
    printf("%d ", node->value);
}

void showBST(BinarySortTreePtr BST)
{
    void (*print)(NodePtr) = printBST;
    printf("\n前序遍历(非递归):\n");
    BST_preorderI(BST, print);
    printf("\n中序遍历(非递归):\n");
    BST_inorderI(BST, print);
    printf("\n后序遍历(非递归):\n");
    BST_postorderI(BST, print);
    printf("\n前序遍历(递归):\n");
    BST_preorderR(BST->root, print);
    printf("\n中序遍历(递归):\n");
    BST_inorderR(BST->root, print);
    printf("\n后序遍历(递归):\n");
    BST_postorderR(BST->root, print);
    printf("\n层次遍历:\n");
    BST_levelOrder(BST, print);
}

void printAVL(AVL_NodePtr node)
{
    if (node == NULL)
        return;
    printf("%d ", node->value);
}

void showAVL(AVLTreePtr AVL)
{
    void (*print)(AVL_NodePtr) = printAVL;
    printf("\n前序遍历(非递归):\n");
    AVLT_preorderI(AVL, print);
    printf("\n中序遍历(非递归):\n");
    AVLT_inorderI(AVL, print);
    printf("\n后序遍历(非递归):\n");
    AVLT_postorderI(AVL, print);
    printf("\n前序遍历(递归):\n");
    AVLT_preorderR(AVL->root, print);
    printf("\n中序遍历(递归):\n");
    AVLT_inorderR(AVL->root, print);
    printf("\n后序遍历(递归):\n");
    AVLT_postorderR(AVL->root, print);
    printf("\n层次遍历:\n");
    AVLT_levelOrder(AVL, print);
}

void showRBT(RedBlackTreePtr RBT)
{
    printf("红黑树层序遍历:\n");
    if (RBT != NULL && RBT->root != NULL)
    {
        RBT_NodePtr current[100], kids[100];
        current[0] = RBT->root;
        int currentNums = 1, kidsNums = 0;
        while (currentNums != 0)
        {
            for (int i = 0; i < currentNums; i++)
            {
                printf(" %d ", current[i]->value);
                if (current[i]->color == RED)
                    printf("RED\t");
                else
                    printf("BLACK\t");
                if (current[i]->left != NULL)
                    kids[kidsNums++] = current[i]->left;
                if (current[i]->right != NULL)
                    kids[kidsNums++] = current[i]->right;
            }
            printf("\n");
            currentNums = kidsNums;
            for (int i = 0; i < kidsNums; i++)
                current[i] = kids[i];
            kidsNums = 0;
        }
    }
    else
        printf("Empty tree\n");
}

int main()
{
    int nums[30];
    BinarySortTreePtr BST = BST_init();
    max_heap* max_heap = create_max_heap(30);
    min_heap* min_heap = create_min_heap(30);
    AVLTreePtr AVL = AVLT_init();
    RedBlackTreePtr RBT = RBT_init();
    srand((unsigned int)time(NULL));
    printf("随机生成20个数\n顺序为:\n");
    for (int i = 0; i < 20; i++)
    {
        nums[i] = rand() % 100;
        printf("%d ", nums[i]);
        BST_insert(BST, nums[i]);
        insert_max_heap(max_heap, nums[i]);
        insert_min_heap(min_heap, nums[i]);
        AVLT_insert(AVL, nums[i]);
        RBT_insert(RBT, nums[i]);
    }
    printf("\n二叉排序树:\n");
    showBST(BST);
    printf("\n大顶堆:\n");
    print_max_heap(max_heap);
    printf("\n小顶堆:\n");
    print_min_heap(min_heap);
    printf("\nAVL树:\n");
    showAVL(AVL);
    printf("\n红黑树:\n");
    showRBT(RBT);
    printf("\n随机删除原数组中某个数:\n");
    int id = rand() % 20;
    printf("删除第 %d 个数: %d \n", id + 1, nums[id]);
    BST_delete(BST, nums[id]);
    delete_max_heap(max_heap, nums[id]);
    delete_min_heap(min_heap, nums[id]);
    AVLT_delete(AVL, nums[id]);
    RBT_delete(RBT, nums[id]);
    printf("\n删除后:\n");
    printf("\n二叉排序树:\n");
    showBST(BST);
    printf("\n大顶堆:\n");
    print_max_heap(max_heap);
    printf("\n小顶堆:\n");
    print_min_heap(min_heap);
    printf("\nAVL树:\n");
    showAVL(AVL);
    printf("\n红黑树:\n");
    showRBT(RBT);
    system("pause");
    return 0;
}