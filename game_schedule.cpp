#include <iostream>

using namespace std;

/*******
����������
�������⣺��N���˶�Ա���е�ѭ�������������˶�Ա��Ҫ������
�����˶�Ա����һ�Ρ�Ҫ��ÿ���˶�Աÿ��ֻ����һ�α�����
������������N-1���ڽ������˶�Ա�����1��N
ע��N = 2^k

���㷨���÷��ε�˼��

����˼·��
�����β���,���ǿ��Խ����е�ѡ�ַ�Ϊ����,
��n��ѡ�ֵı����ճ̱����ͨ��n/2��ѡ�ֵı����ճ̱�������.
�ݹ��������һ��Ϊ���Ĳ��Զ�ѡ�ֽ��л���,
ֱ��ֻʣ������ѡ��ʱ,����������ѡ�ֽ��б����Ϳ�����

�ճ̱���þ�������ʶ��Ԫ��ֵΪ�˶�Ա��ţ�
�������ʾ�ڼ��죬�±��0��ʼ��
��Լ����0�죬��ʾ�Լ����Լ�������
���磬����ֻ��������ԱԱ�����
1 2
2 1
��ʾ��1�ĵ�1���2������2�ĵ�һ���1������

�ݴˣ������Ͻ�С���е��������ְ������λ�ó������½�,
�ֽ����½�С���е��������ְ������λ�ó������Ͻ�,
�������Ǿͷֱ��ź���
*******/

void GameSchedule(int *table, int table_rank);
//��ѭ�������㷨��������
void GSchedule(int *table, int table_rank,
               int r1, int c1, int r2, int c2, int n);
//��ѭ�����̵İ���ʵ��
void InitTable(int *table, int table_rank);
//��ʼ�����̱�
void PrintTable(int *table, int table_rank);
//������̱�
int main()
{
    int sport_count = 0;//��¼�˶�Ա������
    cout<<"Please enter the count of sporters: ";
    cin>>sport_count;
    //����һ���˶�Ա����*�˶�Ա���������̱�
    int *table = new int[sport_count * sport_count];
    //��������
    GameSchedule(table, sport_count);
    //������Ž��
    PrintTable(table, sport_count);
    delete []table;
    return 0;
}

void GameSchedule(int *table, int table_rank)
{
    //���ȶ����̱��ʼ����Ȼ��������̰���
    InitTable(table, table_rank);
    GSchedule(table, table_rank,
              0, 0, table_rank-1, table_rank-1, table_rank);
}

void GSchedule(int *table, int table_rank,
               int r1, int c1, int r2, int c2, int n)
{
   //table_rankΪ����Ľ�����nΪ�˶�Ա������
   //(r1,c1)ΪҪ������Ӿ���ĵ�һ��Ԫ�ص�����
   //(r2,c2)ΪҪ������Ӿ�������һ��Ԫ�ص�����
   if(n >= 2)
   {
       //��������(r1,c1)Ϊʼ��,(r2,c2)Ϊ�յ�����е��˶�Ա��������
       for(int i = 0; i < n; ++i)
       {
            //�������Ͻ�С���е��������ְ������λ�ó������½�
            //�����½�С���е��������ְ������λ�ó������Ͻ�
            if(*(table + (r2-i)*table_rank+c2) == 0)
                *(table + (r2-i)*table_rank+c2)
                    = *(table+(r1+i)*table_rank+c1);
            else
                *(table+(r1+i)*table_rank+c1)
                    = *(table+(r2-i)*table_rank+c2);
       }
       int mr = (r2-r1)/2;
       int mc = (c2-c1)/2;
       n /= 2;//���˶�Ա����������һ��
       //Ϊ�����Ͻǵ��ķ�֮һ�ľ���������
       GSchedule(table, table_rank, r1,c1, r1+mr,c1+mc, n);
       //Ϊ�����Ͻǵ��ķ�֮һ�ľ���������
       GSchedule(table, table_rank, r1, c1+mc+1, r1+mr, c2, n);
       //Ϊ�����½ǵ��ķ�֮һ�ľ���������
       GSchedule(table, table_rank, r1+mr+1, c1, r2, c1+mc, n);
       //Ϊ�����½ǵ��ķ�֮һ�ľ���������
       GSchedule(table, table_rank, r1+mr+1, c1+mc+1, r2, c2, n);
   }
}

void InitTable(int *table, int table_rank)
{
    //��ʼ�����̱����Ȱ����е�������0
    for(int i = 0; i < table_rank; ++i)
    {
        for(int j = 0; j < table_rank; ++j)
            *(table + i * table_rank +j) = 0;
    }
    //���õ�0��Ϊ���Լ�����
    for(int i = 0; i < table_rank; ++i)
    {
        *(table+i*table_rank+0) = i + 1;
    }
}

void PrintTable(int *table, int table_rank)
{
    //������̱�
    for(int i = 0; i < table_rank; ++i)
    {
        for(int j = 0; j < table_rank; ++j)
            cout << *(table+i*table_rank+j) <<' ';

        cout<<endl;
    }
}
