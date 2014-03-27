#include <iostream>
#include <stdlib.h>
#include <time.h>
/***
问题描述：
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
要求不能创建任何新的结点，只能调整树中结点指针的指向。
***/
using std::cout;
using std::cin;
using std::endl;

struct BSNode
{
    //定义二叉搜索树的结点结构
    BSNode *left;
    BSNode *right;
    int data;
};
//定义各种用到数据类型
typedef BSNode* BSTree;
typedef BSNode* DList;
typedef BSNode DLNode;

//往二叉搜索树tree中插入值为data的结点
BSTree InsertNode(BSTree tree, int data);

//把二叉搜索树tree转化成双向链表，返回头结点
DList BSTreeToList(BSTree tree);

//遍历二叉搜索树tree的各个结点,并进行指针调整
void ConvertNode(BSTree tree, BSNode **last_node);

//查找二叉搜索树tree的最左结点
BSNode* FindLeftmostNode(BSTree tree);

//以中序输出二叉搜索树tree
void PrintBiTree(BSTree tree);

//输出链表
void PrintList(DList list);

BSTree InsertNode(BSTree tree, int data)
{
    if(tree == NULL)
    {
        //找到插入点，则插入
        tree = new BSNode;
        tree->left = NULL;
        tree->right = NULL;
        tree->data = data;
    }
    //插入在其右子树中
    else if(tree->data < data)
        tree->right = InsertNode(tree->right, data);
    //插入在其左子树中
    else if(tree->data > data)
        tree->left = InsertNode(tree->left, data);

    return tree;
}

DList BSTreeToList(BSTree tree)
{
    if(tree == NULL)
        return NULL;
    //找到最左边的结点，即转换后链表的头结点
    DLNode *head = FindLeftmostNode(tree);
    BSNode *last_node = NULL;
    //进行转换
    ConvertNode(tree, &last_node);
    return head;
}

BSNode* FindLeftmostNode(BSTree tree)
{
    if(tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

void ConvertNode(BSTree tree, BSNode **last_node)
{
    if(tree == NULL)
        return;

    //对tree的左子树进行转换，last_node是转换后链表最后一个结点的指针
    if(tree->left != NULL)
        ConvertNode(tree->left, last_node);
    //调整tree的left指针，指向上一个结点
    tree->left = *last_node;
    //调整指向最后一个结点，right指向下一个结点
    if(*last_node != NULL)
        (*last_node)->right = tree;
    //调整指向最后链表一个结点的指针
    *last_node = tree;
    //对tree的右子树进行转换，last_node是转换后链表最后一个结点的指针
    if(tree->right != NULL)
        ConvertNode(tree->right, last_node);
}

void PrintBSTree(BSTree tree)
{
    if(tree == NULL)
        return;
    PrintBSTree(tree->left);
    cout << tree->data << " ";
    PrintBSTree(tree->right);
}

void PrintList(DList list)
{
    DLNode *node = list;
    while(node != NULL)
    {
        cout << node->data << " ";
        node = node->right;
    }
}

int main()
{
    BSTree tree = NULL;
    srand(time(NULL));
    cout << "Insert Data Order is:" << endl;

    for(int i = 0; i < 10; ++i)
    {
        int data = rand()%100;
        cout << data << " ";
        tree = InsertNode(tree, data);
    }

    cout << "\nThe BSTree is: " << endl;
    PrintBSTree(tree);

    tree = BSTreeToList(tree);
    cout << "\nBiTree To List: "<< endl;
    PrintList(tree);
    return 0;
}

