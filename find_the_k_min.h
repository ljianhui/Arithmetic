#ifndef FIND_THE_K_MIN_H_INCLUDED
#define FIND_THE_K_MIN_H_INCLUDED

#include <stdlib.h>
#include <time.h>

/**********************************
问题描述：
在一个数组中找出其第k个最小的数，例如对于数组x，
x = {3，2，1，4，5，6}，则其第2个最小的数为2

算法思想：减治法,时间复杂度为NlogN，比快排快

本算法跟快排的思想相似，首先在数组中选取一个数centre作为枢纽，
将比centre小的数，放到centre的前面
将比centre大的数，放到centre的后面
如果此时centre的位置刚好为k，则centre为第k个最小的数
如果此时centre的位置比k前，则第k个最小数一定在centre后面，
递归地在其右边寻找
如果此时centre的位置比k后，则第k个最小数一定在centre后面，
递归地在其左边寻找
注意：centre的位置=其下标值+1，因为数组中的第一个元素的下标为0

**********************************/

//返回数组中的第k个最小元素的启动函数，注意会破坏原数组
template<typename T>
T FindTheKMin(T *x, int x_size, int k);

//返回数组中的第中个最小元素的下标的启动函数，不破坏原数组
template<typename T>
int IndexOfKMin(const T *x, int x_size, int k);

//实现查找数组中第K个最小元的功能函数
template<typename T>
T TheKMin(T *x, int left, int right, int k);

//实现查找数组中第K个最小元下标的功能函数
template<typename T>
int TheKMin(const T *x, int *track, int left, int right, int k);

template<typename T>
void Swap(T &a, T &b);

int Random(int begin, int end);

template<typename T>
T FindTheKMin(T *x, int x_size, int k)
{
    //判断k的值是否过大，即超过数组的大小
    //若是则返回第0个元素，主要是为了防止无效的递归
    if(x_size < k)
        return x[0];
    return TheKMin(x, 0, x_size-1, k);
}

template<typename T>
int IndexOfKMin(const T *x, int x_size, int k)
{
    //判断k的值是否过大，即超过数组的大小
    //若是则返回下标-1，主要是为了防止无效的递归
    if(x_size < k)
        return -1;
    //创建一个跟踪数组，其内容为原数组中元素的下标，
    //用于记录元素的交换（即代替元素的交换）
    //按顺序以track数组中的数据为下标访问元素，访问顺序与上一方法相同
    int *track = new int[x_size];
    for(int i = 0; i < x_size; ++i)
        track[i] = i;
    int i = TheKMin(x, track, 0, x_size-1, k);
    delete []track;
    return i;
}

template<typename T>
T TheKMin(T *x, int left, int right, int k)
{
    //随机选取一个元素作为枢纽，并与数组最后一个元素交换
    int i = Random(left, right);
    Swap(x[i], x[right]);

    T centre = x[right];
    i = left;
    int j = right - 1;
    while(true)
    {
        //从前向后扫描，找到第一个小于枢纽的值，
        //在到达数组末尾前，必定结束循环,因为最后一个值为centre
        while(x[i] < centre)
            ++i;
        //从后向前扫描，此时要检查下标，防止数组越界
        while(j >= left && x[j] > centre)
            --j;
        //如果没有完成一趟交换，则交换
        if(i < j)
            Swap(x[i], x[j]);
        else
            break;
    }
    //把枢纽放在正确的位置
    Swap(x[i], x[right]);
    //如果此时centre的位置刚好为k，则centre为第k个最小的数
    if(i+1 == k)
        return x[i];
    else if(i+1 < k)
    {
        //如果此时centre的位置比k前,递归地在其右边寻找
        TheKMin(x, i+1, right, k);
    }
    else
    {
        //如果此时centre的位置比k后,递归地在其左边寻找
        TheKMin(x, left, i-1, k);
    }
}

template<typename T>
int TheKMin(const T *x, int *track, int left, int right, int k)
{
    //随机选取一个元素作为枢纽，并与跟踪数组最后一个元素交换
    int i = Random(left, right);
    Swap(track[i], track[right]);

    T centre = x[track[right]];
    i = left;
    int j = right - 1;
    while(true)
    {
        //从前向后扫描，找到第一个小于枢纽的值，
        //在到达数组末尾前，必定结束循环,因为最后一个值为centre
        //注意此时的数据的下标不是i，而是track[i]
        while(x[track[i]] < centre)
            ++i;
        //从后向前扫描时要检查下标，防止数组越界
        while(j >= left && x[track[j]] > centre)
            --j;
        //如果没有完成一趟交换，则交换，注意，是交换跟踪数组的值
        if(i < j)
            Swap(track[i], track[j]);
        else
            break;
    }
    //把枢纽放在正确的位置
    Swap(track[i], track[right]);
    //如果此时centre的位置刚好为k，则centre为第k个最小的数，
    //返回其在真实数组中的下标，即track[i]
    if(i+1 == k)
        return track[i];
    else if(i+1 < k)
    {
        //如果此时centre的位置比k前,递归地在其右边寻找
        TheKMin(x, track, i+1, right, k);
    }
    else
    {
        //如果此时centre的位置比k后,递归地在其左边寻找
        TheKMin(x, track, left, i-1, k);
    }
}

template<typename T>
void Swap(T &a, T &b)
{
    T tmp(a);
    a = b;
    b = tmp;
}

int Random(int begin, int end)
{
    //产生begin至end，包括begin和end的随机数，即[begin, end]范围的整数
    return rand()%(end - begin + 1) + begin;
}

#endif // FIND_THE_K_MIN_H_INCLUDED
