#include <iostream>

using namespace std;

/*******
问题描述：
赛程问题：有N个运动员进行单循环赛，即两个运动员都要与其他
所有运动员比赛一次。要求每个运动员每天只进行一次比赛，
且整个赛程在N-1天内结束，运动员编号由1到N
注：N = 2^k

本算法采用分治的思想

解题思路：
按分治策略,我们可以将所有的选手分为两半,
则n个选手的比赛日程表可以通过n/2个选手的比赛日程表来决定.
递归地用这种一分为二的策略对选手进行划分,
直到只剩下两个选手时,就让这两个选手进行比赛就可以了

日程表可用矩阵来标识，元素值为运动员编号，
列坐标表示第几天，下标从0开始，
并约定第0天，表示自己跟自己比赛，
例如，对于只有两个动员员的情况
1 2
2 1
表示，1的第1天跟2比赛，2的第一天跟1比赛。

据此，将左上角小块中的所有数字按其相对位置抄到右下角,
又将左下角小块中的所有数字按其相对位置抄到右上角,
这样我们就分别安排好了
*******/

void GameSchedule(int *table, int table_rank);
//单循环赛程算法启动函数
void GSchedule(int *table, int table_rank,
               int r1, int c1, int r2, int c2, int n);
//单循环赛程的安排实现
void InitTable(int *table, int table_rank);
//初始化赛程表
void PrintTable(int *table, int table_rank);
//输出赛程表
int main()
{
    int sport_count = 0;//记录运动员的人数
    cout<<"Please enter the count of sporters: ";
    cin>>sport_count;
    //创建一张运动员人数*运动员人数的赛程表
    int *table = new int[sport_count * sport_count];
    //安排赛程
    GameSchedule(table, sport_count);
    //输出安排结果
    PrintTable(table, sport_count);
    delete []table;
    return 0;
}

void GameSchedule(int *table, int table_rank)
{
    //首先对赛程表初始化，然后进行赛程安排
    InitTable(table, table_rank);
    GSchedule(table, table_rank,
              0, 0, table_rank-1, table_rank-1, table_rank);
}

void GSchedule(int *table, int table_rank,
               int r1, int c1, int r2, int c2, int n)
{
   //table_rank为矩阵的阶数，n为运动员的人数
   //(r1,c1)为要处理的子矩阵的第一个元素的坐标
   //(r2,c2)为要处理的子矩阵的最后一个元素的坐标
   if(n >= 2)
   {
       //对以坐标(r1,c1)为始点,(r2,c2)为终点的所有的运动员安排赛程
       for(int i = 0; i < n; ++i)
       {
            //即将左上角小块中的所有数字按其相对位置抄到右下角
            //将左下角小块中的所有数字按其相对位置抄到右上角
            if(*(table + (r2-i)*table_rank+c2) == 0)
                *(table + (r2-i)*table_rank+c2)
                    = *(table+(r1+i)*table_rank+c1);
            else
                *(table+(r1+i)*table_rank+c1)
                    = *(table+(r2-i)*table_rank+c2);
       }
       int mr = (r2-r1)/2;
       int mc = (c2-c1)/2;
       n /= 2;//将运动员的人数减少一半
       //为其左上角的四分之一的矩阵安排赛程
       GSchedule(table, table_rank, r1,c1, r1+mr,c1+mc, n);
       //为其右上角的四分之一的矩阵安排赛程
       GSchedule(table, table_rank, r1, c1+mc+1, r1+mr, c2, n);
       //为其左下角的四分之一的矩阵安排赛程
       GSchedule(table, table_rank, r1+mr+1, c1, r2, c1+mc, n);
       //为其右下角的四分之一的矩阵安排赛程
       GSchedule(table, table_rank, r1+mr+1, c1+mc+1, r2, c2, n);
   }
}

void InitTable(int *table, int table_rank)
{
    //初始化赛程表，首先把所有的数据置0
    for(int i = 0; i < table_rank; ++i)
    {
        for(int j = 0; j < table_rank; ++j)
            *(table + i * table_rank +j) = 0;
    }
    //设置第0天为与自己比赛
    for(int i = 0; i < table_rank; ++i)
    {
        *(table+i*table_rank+0) = i + 1;
    }
}

void PrintTable(int *table, int table_rank)
{
    //输出赛程表
    for(int i = 0; i < table_rank; ++i)
    {
        for(int j = 0; j < table_rank; ++j)
            cout << *(table+i*table_rank+j) <<' ';

        cout<<endl;
    }
}
