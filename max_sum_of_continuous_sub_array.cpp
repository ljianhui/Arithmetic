#include <iostream>

using namespace std;

/************
问题描述：
一个整型数组，数组里有正数也有负数。
数组中连续的一个或多个整数组成一个子数组，
每个子数组都有一个和，
求所有子数组的和的最大值，要求时间复杂度为O(n)。
注意：当全是负数的情况时，返回最大的那个负数
************/
int MaxSum(int* a,int n);
int main()
{
    int a[100] = {1, -2, 3, 10, -4, 7, 2, -5};
    cout<<MaxSum(a,8)<<endl;
    return 0;
}

int MaxSum(int* a,int n)
{
    int sum = 0; //用于记录最大的连续子数组和
    int flag = 0;//用于记录负数的个数
    int MaxNum = *a;//用于记录数组中最大的数
    int ThisSum = 0;//用于记录当前的最大的连续子数组和
    for(int i = 0; i < n; ++i)
    {
        if(a[i] < 0) //如果无素为负数，则把flag的值加1
            ++flag;
        if(MaxNum < a[i]) //记录数组当前的最大值
            MaxNum = a[i];
        ThisSum += a[i]; //更新当前的子数组之和
        if(ThisSum > sum)
        {
            //若当前连续子数组之和大于记录的子数组之和
            //则设置最大连续子数组之和为当前的和
            sum = ThisSum;
        }
        else if(ThisSum < 0)
        {
            //如果当前连续子数组之和小于0，则抛弃之前的连续子数组，
            //从此元素的下一个元素重新计算连续子数组之和
            ThisSum = 0;
        }
    }
    //若全是负数，最大值为数组中的最大无素
    if(flag == n)
        sum = MaxNum;
    return sum;
}
