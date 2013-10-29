#include <iostream>

using namespace std;
/***********
问题描述：
实现类似于C语言的函数power，计算一个整数的n次方
算法思想：减治法
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
