#include <iostream>

using namespace std;

/*******
问题描述：
赛程问题：有N个运动员进行单循环赛，即两个运动员都要与其他
所有运动员比赛一次。要求每个运动员每天只进行一次比赛，
且整个赛程在N-1天内结束，运动员编号由1到N
注：N = 2^k

本算法采用分治的思想
*******/

void GameSchedule(int *table, int sport_count);
void GSchedule(int *table, int tableRows, int sport_count);
void PrintTable(int *table, int sport_count);
int main()
{
    int sport_count = 0;
    cout<<"Please enter the count of sporters: ";
    cin>>sport_count;
    int *table = new int[sport_count * sport_count];
    GameSchedule(table, sport_count);
    PrintTable(table, sport_count);
    delete []table;
    return 0;
}

void GameSchedule(int *table, int sport_count)
{
    GSchedule(table, sport_count, sport_count);
}

void GSchedule(int *table, int tableRows, int sport_count)
{
    int i = 0;
    int j = 0;
    int n = 0;

    if(sport_count == 2)
    {

    }
}

void PrintTable(int *table, int sport_count)
{

}
