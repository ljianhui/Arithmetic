#include <iostream>

using namespace std;

/**********************************
问题描述：
已知有两个有序的数组a和b，现要求把数组b中的数据合并到数组a中，
合并后，数组a中的数据依然有序，若数组a的大小不足以容纳所有的数据，
则不进行合并，返回-1表示合并失败。
若数组a的大小足以容纳所有的数据，则返回合并后数组a的元素个数

实现思路：
因为我们已经知道数组a的大小和元素个数，也知道数组b的元素个数，
就可以计算出合并后，最后一个元素的位置index。
我们用两个下标a_index和b_index分别指向a和b最后一个元素的位置,
从后往前扫描两个数组，把较大的从最后的位置依次放入到位置index处。
直到a_index或b_index其中一个为小于0即可结束算法

时间复杂度：O（n）
空间复杂度：O（1）
**********************************/


int MergeArray(int *a, int a_count, int a_capacity, int *b, int b_count)
{
    /**********
    参数：
    a：数组a的起始地址
    a_count：数组a的元素个数
    a_capacity：数组a的大小，即容量
    b：数组b的起始地址
    b_count：数组b的元素个数
    **********/
    if(a_capacity < a_count + b_count)
        return -1;

    int index = a_count + b_count - 1;
    int a_index = a_count - 1;
    int b_index = b_count - 1;

    while(a_index >= 0 && b_index >=0)
    {
        //扫描两个数组，把较大的放到index指向的位置
        if(a[a_index] > b[b_index])
        {
            a[index] = a[a_index];
            --a_index;
        }
        else
        {
            a[index] = b[b_index];
            --b_index;
        }
        //index的位置前移
        --index;
    }
    return a_count + b_count;
}

int main()
{
    int a[10] = {1,3,5,7};
    int b[] = {2,7,8,9,10};

    int count = MergeArray(a, 4, 10, b, 5);
    for(int i = 0; i < count; ++i)
    {
        cout << a[i] << endl;
    }
    return 0;
}
