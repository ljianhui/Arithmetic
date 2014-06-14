/***
http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=1770

It is well known that, in the period of The Three Empires, Liu Bei,
the emperor of the Shu Empire, was defeated by Lu Xun,
a general of the Wu Empire. The defeat was due to Liu Bei's wrong
decision that he divided his large troops into a number of camps,
each of which had a group of armies, and located them in a line.
This was the so-called "Linked Camps".

Let's go back to that time. Lu Xun had sent many scouts to obtain
the information about his enemy. From his scouts, he knew
that Liu Bei had divided his troops into n camps, all of which
located in a line, labeled by 1..n from left to right.
The ith camp had a maximum capacity of Ci soldiers. Furthermore,
by observing the activities Liu Bei's troops had been doing those days,
Lu Xun could estimate the least total number of soldiers
that were lived in from the ith to the jth camp.
Finally, Lu Xun must estimate at least how many soldiers did Liu Bei had,
so that he could decide how many troops he should send to burn
Liu Bei's Linked Camps.

Input:

There are multiple test cases! On the first line of each test case,
there are two integers n (0<n<=1,000) and m (0<=m<=10,000).
On the second line, there are n integers C1��Cn. Then m lines follow,
each line has three integers i, j, k (0<i<=j<=n, 0<=k<2^31),
meaning that the total number of soldiers from the ith camp to the
jth camp is at least k.

Output:

For each test case, output one integer in a single line:
the least number of all soldiers in Liu Bei's army from Lu Xun's
observation. However, Lu Xun's estimations given in the input data
may be very unprecise. If his estimations cannot be true,
output "Bad Estimations" in a single line instead.

Sample Input:

3 2
1000 2000 1000
1 2 1100
2 3 1300
3 1
100 200 300
2 3 600
Sample Output:

1300
Bad Estimations
***/

#include <stdio.h>
#include <memory.h>
#include <limits.h>
#include <queue>
#include <iostream>

#define MAX_DIST INT_MAX/2
#define MAX_CAMP 1001

using std::queue;

/*
 * the value of graph[i][j] means the max soldiers
 * that move form ith camp to jth camp
 */
int graph[MAX_CAMP][MAX_CAMP];

int dist[MAX_CAMP];

/*
 * The value of counts[i] means that the times of ith camp enter queue
 * if the value of counts[i] > n, mean that the graph has a loop
 */
int counts[MAX_CAMP];

/*
 * if the ith camp in the queue, in_queue[i] == true
 */
bool in_queue[MAX_CAMP];

int n = 0;
int m = 0;

void Init()
{
    for(int i = 0; i <= n; ++i)
    {
        for(int j = 0; j <= n; ++j)
        {
            graph[i][j] = MAX_DIST;
        }
        graph[i][i] = 0;
    }
    memset(dist, 0, sizeof(dist));
    memset(counts, 0, sizeof(counts));
    memset(in_queue, 0, sizeof(in_queue));
}

void InputData()
{
    for(int i = 1; i <= n; ++i)
    {
        int capacity = 0;
        scanf("%d", &capacity);
        //capacity[i] means that total soldiers form 1 to i
        //capacity[i]-capacity[i-1]<=k
        graph[i-1][i] = capacity;
        //capacity[i-1]-capacity[i]<=0, ensure every camp's soldiers > 0
        graph[i][i-1] = 0;
    }

    for(int i = 1; i <= m; ++i)
    {
        int camp_i = 0;
        int camp_j = 0;
        int soldiers = 0;
        scanf("%d%d%d", &camp_i, &camp_j, &soldiers);
        //camp[camp_j] - camp[camp_i-1] >= soldiers ->
        //E(camp_j, camp_i-1) <= -soldiers
        graph[camp_j][camp_i-1] = -soldiers;
    }
}

bool CountMinSoldiers(int start)
{
    queue<int> vertex_que;
    vertex_que.push(start);//the start-th camp enqueue
    in_queue[start] = true;//the start-th is in queue
    ++counts[start];//add start-th camp's enqueue times

    while(!vertex_que.empty())
    {
        int i = vertex_que.front();
        vertex_que.pop();//dequeue
        in_queue[i] = false;//the ith camp is not in queue
        for(int j = 0; j <= n; ++j)
        {
            if(graph[i][j] != MAX_DIST &&
               dist[j] > dist[i] + graph[i][j])
            {
                dist[j] = dist[i] + graph[i][j];
                //if j-th camp is not in queue, enqueue j-th camp
                if(in_queue[j] == false)
                {
                    vertex_que.push(j);
                    in_queue[j] = true;
                    ++counts[j];//add the j-th camp enqueue times
                    if(counts[j] > n)//has a loop
                        return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    //freopen("input_data.txt", "r", stdin);
    while(scanf("%d %d", &n, &m) != EOF)
    {
        Init();
        InputData();
        if(CountMinSoldiers(n) == true)
        {
            printf("%d\n", -dist[0]);
        }
        else
        {
            printf("Bad Estimations\n");
        }
    }
    return 0;
}

