/***
http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemId=2

Suppose that we have a square city with straight streets.
A map of a city is a square board with n rows and n columns,
each representing a street or a piece of wall.

A blockhouse is a small castle that has four openings through
which to shoot. The four openings are facing North, East, South,
and West, respectively. There will be one machine gun shooting
through each opening.

Here we assume that a bullet is so powerful that it can run across
any distance and destroy a blockhouse on its way. On the other hand,
a wall is so strongly built that can stop the bullets.

The goal is to place as many blockhouses in a city as possible
so that no two can destroy each other. A configuration of blockhouses
is legal provided that no two blockhouses are on the same horizontal
row or vertical column in a map unless there is at least one wall
separating them. In this problem we will consider small square
cities (at most 4x4) that contain walls through which bullets cannot
run through.

The following image shows five pictures of the same board.
The first picture is the empty board, the second and third pictures
show legal configurations, and the fourth and fifth pictures show
illegal configurations. For this board, the maximum number of blockhouses
in a legal configuration is 5; the second picture shows one way to do it,
but there are several other ways.

Your task is to write a program that, given a description of a map,
calculates the maximum number of blockhouses that can be placed
in the city in a legal configuration.

The input file contains one or more map descriptions, followed by
a line containing the number 0 that signals the end of the file.
Each map description begins with a line containing a positive integer n
that is the size of the city; n will be at most 4.
The next n lines each describe one row of the map,
with a '.' indicating an open space and an uppercase 'X'
indicating a wall. There are no spaces in the input file.

For each test case, output one line containing the maximum number of
blockhouses that can be placed in the city in a legal configuration.

Sample input:

4
.X..
....
XX..
....
2
XX
.X
3
.X.
X.X
.X.
3
...
.XX
.XX
4
....
....
....
....
0
Sample output:

5
1
5
2
4

***/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define SIZE 4

int MAX = -1;
char city[SIZE][SIZE+1];
int n = 0;
char blockhouses = '@';

bool CanBuilt(int row, int col)
{
    if(city[row][col] != '.')
        return false;

    for(int i = row - 1; i >= 0; --i)
    {
        if(city[i][col] == blockhouses)
            return false;
        if(city[i][col] == 'X')
            break;
    }
    for(int j = col - 1; j >= 0; --j)
    {
        if(city[row][j] == blockhouses)
            return false;
        if(city[row][j] == 'X')
            break;
    }

    return true;
}

void DSF(int pos, int count)
{
    if(pos == n * n)
    {
        if(MAX < count)
        {
            MAX = count;
            return;
        }

    }
    else
    {
        int row = pos / n;
        int col = pos % n;
        if(CanBuilt(row, col))
        {
            city[row][col] = blockhouses;
            DSF(pos+1, count+1);
            city[row][col] = '.';
        }

        DSF(pos+1, count);
    }
}

int main()
{
    while(scanf("%d", &n) != EOF && n != 0)
    {
        MAX = -1;
        int count = 0;
        int pos = 0;
        memset(city, 0, sizeof(city));

        for(int i = 0; i < n; ++i)
            scanf("%s", city[i]);

        DSF(pos, count);

        printf("%d\n", MAX);
    }
}
