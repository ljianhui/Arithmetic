/***
http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=610

Painting some colored segments on a line, some previously painted
segments may be covered by some the subsequent ones.
Your task is counting the segments of different colors you can
see at last.


Input

The first line of each data set contains exactly one integer n,
1 <= n <= 8000, equal to the number of colored segments.

Each of the following n lines consists of exactly 3 nonnegative integers
separated by single spaces:

x1 x2 c

x1 and x2 indicate the left endpoint and right endpoint of the segment,
c indicates the color of the segment.

All the numbers are in the range [0, 8000], and they are all integers.

Input may contain several data set, process to the end of file.


Output

Each line of the output should contain a color index that can be seen
from the top, following the count of the segments of this color,
they should be printed according to the color index.

If some color can't be seen, you shouldn't print it.

Print a blank line after every dataset.


Sample Input

5
0 4 4
0 3 1
3 4 2
0 2 2
0 2 3
4
0 1 1
3 4 1
1 3 2
1 3 1
6
0 1 0
1 2 1
2 3 1
1 2 0
2 3 0
1 2 1


Sample Output

1 1
2 1
3 1

1 1

0 2
1 1
***/

#include<stdio.h>
#include<memory.h>

struct Node
{
	int begin;
	int end;
	int color;
	Node *lc;
	Node *rc;
};

struct Segment
{
	int x1;
	int x2;
	int c;
};

Node* CreatTree(int begin, int end);
void DeleteTree(Node *root);
void Insert(Node *root, const Segment *seg);
void CleanTree(Node *root);
void ChangeColors(const Node *root, int *colors);
void CountColors(const int *colors, int *count, int colors_len);
void PrintResult(const int *count, int count_len);

int main()
{
	const int max_size = 8001;
	int M = 0;

	Node *root = CreatTree(0, max_size);

    //freopen("input_data.txt", "r", stdin);
	while( scanf("%d",&M) != EOF )
	{
		if(M == 0)
            continue;

        CleanTree(root);

		for(int i = 0; i < M; ++i)
		{
			Segment seg;
			scanf("%d %d %d", &seg.x1, &seg.x2, &seg.c);
			Insert(root, &seg);
		}

		int colors[max_size] = {0};
		memset(colors, -1, sizeof(colors));
		ChangeColors(root, colors);

        int count[max_size] = {0};
        CountColors(colors, count, max_size);

        PrintResult(count, max_size);
        printf("\n");
	}
	DeleteTree(root);
	return 0;
}

Node* CreatTree(int begin, int end)//[a,b]为区间的线段树
{
	Node* root = new Node();
	root->begin = begin;
	root->end = end;
	root->color = -1;//初始化为无颜色

	if(end - begin == 1)
	{
	    root->lc = root->rc = NULL;
	    return root;
    }

	root->lc = CreatTree(begin, (begin+end)/2);
	root->rc = CreatTree((begin+end)/2, end);

	return root;
}

void DeleteTree(Node *root)
{
    if(root == NULL)
        return;
    DeleteTree(root->lc);
    DeleteTree(root->rc);
    delete root;
}

void Insert(Node *root, const Segment *seg)
{
    //原本已覆盖
    if(root->color == seg->c)
        return;

	if(seg->x1 <= root->begin && root->end <= seg->x2)
	{
	    root->color=seg->c;
	    return;
    }

    //root原本有其他颜色，则拆分
	if(root->color != -1 && root->color != seg->c)
	{
		root->lc->color = root->color;
		root->rc->color = root->color;
		root->color = -1;
	}
	if( seg->x1 < (root->begin + root->end)/2 )
        Insert(root->lc,seg);
	if( seg->x2 > (root->begin + root->end)/2 )
        Insert(root->rc,seg);

    //根据左右孩子的值处理temp->color
	if(root->lc->color == root->rc->color)
	{
		root->color = root->lc->color;
		//合并后孩子改为无颜色
		root->lc->color = -1; root->rc->color = -1;
	}
}

void CleanTree(Node *root)
{
    /*
     *功能：把树root的所有颜色清空为-1
     */
    if(root == NULL)
        return;

    root->color = -1;

    CleanTree(root->lc);
    CleanTree(root->rc);
}

void ChangeColors(const Node *root, int *colors)
{
    /*
     *函数功能：使用先序遍历来统计颜色的分布情况
     */
    if(root == NULL)
        return;

    if(root->color != -1)
    {
        for(int i = root->begin; i < root->end; ++i)
        {
            colors[i] = root->color;
        }
    }
    else
    {
        ChangeColors(root->lc, colors);
        ChangeColors(root->rc, colors);
    }
}

void CountColors(const int *colors, int *count, int colors_len)
{
    int this_col = -1;
    int col_value  = -1;

    for(int i = 0; i < colors_len; ++i)
    {
        col_value = colors[i];
        if(col_value != -1 && col_value != this_col)
        {
            ++count[col_value];
        }
        this_col = col_value;
    }
}

void PrintResult(const int *count, int count_len)
{
    for(int i = 0; i < count_len; ++i)
    {
        if(count[i] != 0)
        {
            printf("%d %d\n", i, count[i]);
        }
    }
}


