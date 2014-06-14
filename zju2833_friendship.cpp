/***
http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=1833

Now you've grown up, it's time to make friends. The friends you
make in university are the friends you make for life. You will
be proud if you have many friends.

Input

There are multiple test cases for this problem.

Each test case starts with a line containing two integers N,
M (1 <= N <= 100'000, 1 <= M <= 200'000), representing
that there are totally N persons (indexed from 1 to N)
and M operations, then M lines with the form "M a b" (without quotation)
or "Q a" (without quotation) follow. The operation "M a b" means
that person a and b make friends with each other, though they may be
already friends, while "Q a" means a query operation.

Friendship is transitivity, which means if a and b, b and c are friends
then a and c are also friends. In the initial, you have no friends
except yourself, when you are freshman, you know nobody, right?
So in such case you have only one friend.

Output

For each test case, output "Case #:" first where "#" is the number of
the case which starts from 1, then for each query operation "Q a",
output a single line with the number of person a's friends.

Separate two consecutive test cases with a blank line,
but Do NOT output an extra blank line after the last one.

Sample Input

3 5
M 1 2
Q 1
Q 3
M 2 3
Q 2
5 10
M 3 2
Q 4
M 1 2
Q 4
M 3 2
Q 1
M 3 1
Q 5
M 4 2
Q 4
Sample Output

Case 1:
2
1
3

Case 2:
1
1
3
1
4
Notes

This problem has huge input and output data, please use 'scanf()'
and 'printf()' instead of 'cin' and 'cout' to avoid time limit exceed.
***/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define Maxsize 100020

int  parent[Maxsize];//并查集树父结点表

int Find(int i)
{
	while(parent[i] >= 0)
	{
	    i=parent[i];
	}
	return i;
}

void WeightedUnion(int i, int j)
{
	if(i == j)
        return;

	int temp = parent[i]+parent[j];
	if(parent[j] < parent[i])
	{
	    parent[i] = j;
	    parent[j] = temp;
    }
	else
	{
	    parent[j] = i;
	    parent[i] = temp;
    }
}

int main()
{
	int cases = 0;
	int N = 0;
	int M = 0;
	int x = 0;
	int y = 0;
    char op = '\0';

	while(scanf("%d %d",&N,&M) != EOF)
	{
		cases++;
		if(cases != 1)
            printf("\n");
		printf("Case %d:\n", cases);

        memset(parent, -1, sizeof(parent));

		getchar();
		for(int i=0;i<M;i++)
		{
			scanf("%c",&op);

			if(op=='M')
			{
				scanf("%d %d",&x, &y);
				//人的编号从1开始，所以x<=N。
				if(x > 0 && y > 0 && x <= N && y <= N)
				{
					x = Find(x);
                    y = Find(y);
				    WeightedUnion(x, y);
				}
			}
			else if(op == 'Q')
			{
				scanf("%d", &x);
				if(x > 0 && x <= N)
				{
					x = Find(x);
					//把x所在的树的树根所对应的结点个数输出
				    printf("%d\n", -parent[x]);
				}
			}
			getchar();
		}
	}
	return 0;
}
