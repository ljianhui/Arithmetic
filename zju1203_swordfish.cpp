/***
http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=203

We all remember that in the movie Swordfish, Gabriel broke into the
World Bank Investors Group in West Los Angeles, to rob $9.5 billion.
And he needed Stanley, the best hacker in the world, to help him break
into the password protecting the bank system. Stanley's lovely daughter
Holly was seized by Gabriel, so he had to work for him. But at the last
moment, Stanley made some little trick in his hacker mission:
he injected a trojan horse in the bank system, so the money would
jump from one account to another account every 60 seconds,
and would continue jumping in the next 10 years. Only Stanley knew
when and where to get the money. If Gabriel killed Stanley,
he would never get a single dollar. Stanley wanted Gabriel to release
all these hostages and he would help him to find the money back.
You who has watched the movie know that Gabriel at last got the money
by threatening to hang Ginger to death. Why not Gabriel go get the money
himself? Because these money keep jumping, and these accounts are
scattered in different cities. In order to gather up these money
Gabriel would need to build money transfering tunnels to connect
all these cities. Surely it will be really expensive to construct
such a transfering tunnel, so Gabriel wants to find out the minimal
total length of the tunnel required to connect all these cites.
Now he asks you to write a computer program to find out the minimal
length. Since Gabriel will get caught at the end of it anyway,
so you can go ahead and write the program without feeling guilty
about helping a criminal.

Input:
The input contains several test cases. Each test case begins with a line
contains only one integer N (0 <= N <=100), which indicates the number of
cities you have to connect. The next N lines each contains two real
numbers X and Y(-10000 <= X,Y <= 10000), which are the citie's Cartesian
coordinates (to make the problem simple, we can assume that we live in a
flat world). The input is terminated by a case with N=0 and you must not
print any output for this case.

Output:
You need to help Gabriel calculate the minimal length of tunnel needed
to connect all these cites. You can saftly assume that such a tunnel can
be built directly from one city to another. For each of the input cases,
the output shall consist of two lines: the first line contains "Case #n:",
where n is the case number (starting from 1); and the next line contains
"The minimal distance is: d", where d is the minimal distance, rounded
to 2 decimal places. Output a blank line between two test cases.

Sample Input:
5
0 0
0 1
1 1
1 0
0.5 0.5
0

Sample Output:
Case #1:
The minimal distance is: 2.83
***/

#include <stdio.h>
#include <math.h>
#include <queue>

#define MAX_SIZE 101

using std::priority_queue;

struct Vertices//顶点
{
	double x;
	double y;
	int parent;//根结点
};

struct EdgeNode//两顶点和边。插入优先队列
{
	int index_1;
	int index_2;
	double edge;
};


Vertices vertices[MAX_SIZE];

bool operator<(const EdgeNode &lhs, const EdgeNode &rhs);
int FindParent(int i);
void Merge(int x, int y);
void InputData(int &n);
void CountEdgeAndEnqueue(int n, priority_queue<EdgeNode> &dege_queue);
double FindAMinPath(priority_queue<EdgeNode> &dege_queue);

int main()
{
    int n = 0;
    int times = 1;
    //freopen("input_data.txt", "r", stdin);
    while(1)
    {
        priority_queue<EdgeNode> dege_queue;
        InputData(n);
        if(n == 0)
            break;
        CountEdgeAndEnqueue(n, dege_queue);

        int path_count = 0;
        double sum_len = 0;
        while(path_count < n-1)
        {
            sum_len += FindAMinPath(dege_queue);
            ++path_count;
        }

        if(times > 1)
        {
            printf("\n");
        }
        printf("Case #%d:\n", times);
        printf("The minimal distance is: %.2lf\n", sum_len);
        ++times;
    }
    return 0;
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
	//i的元素比j的多,i做父亲
	if(vertices[i].parent < vertices[j].parent)
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

void InputData(int &n)
{
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
    {
        scanf("%lf %lf", &vertices[i].x, &vertices[i].y);
        vertices[i].parent = -1;
    }
}

void CountEdgeAndEnqueue(int n, priority_queue<EdgeNode> &dege_queue)
{
    EdgeNode node;
    for(int i = 0; i < n-1; ++i)
    {
        for(int j = i+1; j < n; ++j)
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

double FindAMinPath(priority_queue<EdgeNode> &dege_queue)
{
    while(dege_queue.size() != 0)
    {
        EdgeNode node = dege_queue.top();
        dege_queue.pop();

        int index_1_parent = FindParent(node.index_1);
        int index_2_parent = FindParent(node.index_2);

        if(index_1_parent != index_2_parent)
        {
            Merge(index_1_parent, index_2_parent);
            return node.edge;
        }
    }
    return 0.0;
}

