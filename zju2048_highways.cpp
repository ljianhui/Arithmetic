/***
http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=1048

The island nation of Flatopia is perfectly flat. Unfortunately,
Flatopia has a very poor system of public highways. The Flatopian
government is aware of this problem and has already constructed
a number of highways connecting some of the most important towns.
However, there are still some towns that you can't reach via a highway.
It is necessary to build more highways so that it will be possible to
drive between any pair of towns without leaving the highway system.

Flatopian towns are numbered from 1 to N and town i has a position
given by the Cartesian coordinates (xi, yi). Each highway connects
exaclty two towns. All highways (both the original ones and the ones
that are to be built) follow straight lines, and thus their length
is equal to Cartesian distance between towns. All highways can
be used in both directions. Highways can freely cross each other,
but a driver can only switch between highways at a town that is
located at the end of both highways.

The Flatopian government wants to minimize the cost of building new
highways. However, they want to guarantee that every town is
highway-reachable from every other town. Since Flatopia is so flat,
the cost of a highway is always proportional to its length.
Thus, the least expensive highway system will be the one
that minimizes the total highways length.


Input

The input consists of two parts. The first part describes all towns
in the country, and the second part describes all of the highways
that have already been built.

The first line of the input contains a single integer N (1 <= N <= 750),
representing the number of towns. The next N lines each contain
two integers, xi and yi separated by a space. These values give the
coordinates of ith town (for i from 1 to N). Coordinates will have
an absolute value no greater than 10000. Every town has a unique location.

The next line contains a single integer M (0 <= M <= 1000),
representing the number of existing highways. The next M lines
each contain a pair of integers separated by a space.
These two integers give a pair of town numbers which are already
connected by a highway. Each pair of towns is connected by at most
one highway.


Output

Write to the output a single line for each new highway
that should be built in order to connect all towns with minimal
possible total length of new highways. Each highway should be presented
by printing town numbers that this highway connects, separated by a space.

If no new highways need to be built (all towns are already connected),
then the output should be created but it should be empty.


This problem contains multiple test cases!

The first line of a multiple input is an integer N, then a blank
line followed by N input blocks. Each input block is in the format
indicated in the problem description. There is a blank line between
input blocks.

The output format consists of N output blocks. There is a blank line
between output blocks.

Sample Input

1

9
1 5
0 0
3 2
4 5
5 1
0 4
5 2
1 2
5 3
3
1 3
9 7
1 2

Sample Output

1 6
3 7
4 9
5 7
8 3
***/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <queue>

#define MAX_TOWNS 751
#define MAX_WAYS 1001

using std::priority_queue;

struct Vertices//顶点
{
	int x;
	int y;
	int parent;//根结点
};

struct EdgeNode//两顶点和边。插入优先队列
{
	int index_1;
	int index_2;
	double edge;
};

Vertices vertices[MAX_TOWNS];
EdgeNode built[MAX_WAYS];
EdgeNode ways[MAX_TOWNS-1];

int n = 0;
int m = 0;

bool operator<(const EdgeNode &lhs, const EdgeNode &rhs);
int FindParent(int i);
void Merge(int x, int y);
void CountEdgeAndEnqueue(priority_queue<EdgeNode> &dege_queue);
void FindAMinPath(priority_queue<EdgeNode> &dege_queue, EdgeNode &node);

int main()
{
    int times = 1;
    int count = 0;
    //freopen("data.txt", "r", stdin);

    scanf("%d", &count);

    for(int i = 0; i < count; ++i)
    {
        scanf("%d", &n);
        for(int i = 1; i <=n; ++i)
        {
            scanf("%d %d", &vertices[i].x, &vertices[i].y);
            vertices[i].parent = -1;
        }
        scanf("%d", &m);
        for(int i = 0; i < m; ++i)
        {
            scanf("%d %d", &built[i].index_1, &built[i].index_2);
            built[i].edge = 0;
        }

        priority_queue<EdgeNode> dege_queue;

        CountEdgeAndEnqueue(dege_queue);

        int way_count = 0;

        for(int j = 0; j < m; ++j)
        {
            int x = FindParent(built[j].index_1);
            int y = FindParent(built[j].index_2);
            if(x != y)
            {
                Merge(x, y);
                ++way_count;
            }
        }

        int has_built = way_count;

        for(int j = 0; way_count < n-1; ++way_count, ++j)
        {
            FindAMinPath(dege_queue, ways[j]);
        }

        if(times++ > 1)
        {
            printf("\n");
        }

        for(int i = 0; i < n-has_built-1; ++i)
        {
            if(ways[i].edge > -1)
            {
                printf("%d %d\n", ways[i].index_1, ways[i].index_2);
            }
        }
    }
}

bool operator<(const EdgeNode &lhs, const EdgeNode &rhs)
{
    if(lhs.edge > rhs.edge)
        return true;
    return false;
}

int FindParent(int i)
{
    if(vertices[i].parent < 0)
        return i;
	int temp = i;
	while(vertices[i].parent >= 0)
	{
	    i = vertices[i].parent;
	}
	vertices[temp].parent = i;//坍塌算法
	return i;
}

void Merge(int i,int j)
{

	if(vertices[i].parent < vertices[j].parent)//i的元素比j的多,i做父亲
	{
	    vertices[j].parent = i;
	    vertices[i].parent = -1;
    }
	else
	{
	    vertices[i].parent = j;
	    vertices[j].parent = -1;
    }
}

void CountEdgeAndEnqueue(priority_queue<EdgeNode> &dege_queue)
{
    EdgeNode node;
    for(int i = 1; i < n; ++i)
    {
        for(int j = i+1; j <= n; ++j)
        {
            node.index_1 = i;
            node.index_2 = j;

            double dis_x = vertices[i].x - vertices[j].x;
            double dis_y = vertices[i].y - vertices[j].y;
            node.edge = sqrt(dis_x * dis_x + dis_y * dis_y);

            dege_queue.push(node);
        }
    }
}

void FindAMinPath(priority_queue<EdgeNode> &dege_queue, EdgeNode &node)
{
    while(dege_queue.size() != 0)
    {
        node = dege_queue.top();
        dege_queue.pop();

        int index_1_parent = FindParent(node.index_1);
        int index_2_parent = FindParent(node.index_2);

        if(index_1_parent != index_2_parent)
        {
            Merge(index_1_parent, index_2_parent);
            return;
        }
    }
}


