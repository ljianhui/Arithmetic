#include <iostream>

using namespace std;
/***********
����������
ʵ��������C���Եĺ���power������һ��������n�η�
�㷨˼�룺���η�
***********/

long int Power(long int x, unsigned int n);

int main()
{
    cout << Power(2, 0) << endl;
    cout << Power(2, 1) << endl;
    cout << Power(2, 5) << endl;
    cout << Power(2, 6) << endl;
    return 0;
}

long int Power(long int x, unsigned int n)
{
    if(n == 0)
        return 1;
    else if(n == 1)
        return x;
    else if(n % 2 == 0)
        return Power(x * x, n/2);
    else
        return Power(x * x, n/2) * x;
}
