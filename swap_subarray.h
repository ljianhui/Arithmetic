#ifndef SWAP_SUBARRAY_H_INCLUDED
#define SWAP_SUBARRAY_H_INCLUDED
/****************
问题描述：
有一数组X[0...n-1],现在把它发为两个子数组x1[0...m]和x2[m+1...n-1],
交换这两个子数组，使用数组x由x1x2变成x2x1，
例如x={1，2，3，4，5，6，7，8，9}，
x1={1，2，3，4，5}，x2={6，7，8，9}，
交换后，x={6，7，8，9，1，2，3，4，5}

解题思想：分治思想，时间复杂度O(N),空间复杂O(1)
首先交换第一个子数组的内容，
再交换第二个子数组的内容，
最后交换把整个数组的元素
交换两个数组后，x1={5，4，3，2，1}，x2={9，8，7，6}，
即x={5，4，3，2，1，9，8，7，6}
交换整个数组后，x={6，7，8，9，1，2，3，4，5}
****************/
template<typename T>
void SwapSubArray(T *array, int array_size, int div);

template<typename T>
void Swap(T *array, int left, int right);

template<typename T>
void SwapSubArray(T *array, int array_size, int div)
{
    //首先交换第一个子数组的内容
    Swap(array, 0, div);
    //再交换第二个子数组的内容
    Swap(array, div+1, array_size-1);
    //最后交换把整个数组的元素
    Swap(array, 0, array_size-1);
}

template<typename T>
void Swap(T *array, int left, int right)
{
    //交换数组left到right的内容
    for(; left < right; ++left, --right)
    {
        T tmp = array[left];
        array[left] = array[right];
        array[right] = tmp;
    }
}


#endif // SWAP_SUBARRAY_H_INCLUDED
