#include <iostream>

using namespace std;

/*******
����������
�������⣺��N���˶�Ա���е�ѭ�������������˶�Ա��Ҫ������
�����˶�Ա����һ�Ρ�Ҫ��ÿ���˶�Աÿ��ֻ����һ�α�����
������������N-1���ڽ������˶�Ա�����1��N
ע��N = 2^k

���㷨���÷��ε�˼��
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
