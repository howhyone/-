//
//  main.c
//  烙饼问题
//
//  Created by mob on 2019/1/8.
//  Copyright © 2019年 mob. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int maxn = 7;
int n, arr[maxn];            //烙饼个数和烙饼数组
int arr_cmp[maxn];
int arr_tmp[maxn];                //记录初始数组

int search_times = 0;        //总搜索次数
int max_swap;            //最小交换次数
int arr_swap[2 * maxn];        //最终翻转方案
int tarr_swap[2 * maxn];    //当前翻转方案

void sort(int *a, int l)//a为数组地址，l为数组长度。
{
    int i, j;
    int v;
    //排序主体
    for(i = 0; i < l - 1; i ++)
        for(j = i+1; j < l; j ++)
        {
            if(a[i] > a[j])//如前面的比后面的大，则交换。
            {
                v = a[i];
                a[i] = a[j];
                a[j] = v;
            }
        }
}

void revert(int *pDishes, int nBegin, int nEnd)
{
    int i,j ,tmp;
    assert(nEnd > nBegin);
    for (i = nBegin, j = nEnd; i < j; i++,j--) {
        tmp = pDishes[i];
        pDishes[i] = pDishes[j];
        pDishes[j] = tmp;
    }
}

void Init()
{
   

    for (int i = 0; i < n; i++) {
        arr_tmp[i] = arr_cmp[i] = arr[i];
    }
    sort(arr_cmp, sizeof(arr_cmp) / sizeof(10));
    max_swap = 2 * (n-1);
}

int LowerBound()
{
    int ret = 0;
    for (int i = 1; i<n; i++) {
        if (arr[i -1] > arr[i]) {
            ret++;
        }
        
    }
    return ret;
}

_Bool isSort()
{
    for (int i = 0; i< n; i++) {
        if (arr_cmp[i] != arr[i]) {
            return 0;
        }
    }
    return 1;
}

void search(int step)
{
    search_times++;
    if (isSort()) {
        if (step < max_swap) {
            max_swap = step;
            for (int i = 0; i < max_swap ; i++) {
                arr_swap[i] = tarr_swap[i];
            }
        }
    }
    if ((step + LowerBound()) > max_swap)  {
        return;
    }
    for (int i = 1; i <= n; i++) {
        revert(arr, 0, i);
        tarr_swap[step] = i;
        search(step+1);
        revert(arr,0,i);
    }
}

void Print()
{
     printf("搜索次数：%d\n", search_times);
     printf("翻转次数: %d\n", max_swap);
     for (int i = 0; i < max_swap; i++)  printf("%d ", arr_swap[i]);
     printf("\n具体的翻转情况：\n");
     for (int i = 0; i < max_swap; i++)
     {
        revert(arr_tmp, 0, arr_swap[i]);
        for (int j = 0; j < n; j++)  printf("%d ", arr_tmp[j]);
        printf("\n");
 }
}

int main(int argc, const char * argv[]) {
//    scanf("%d",&n);
//    for (int i = 0; i < n; i++) {
//        scanf("%d",&arr[i]);
//    }
    int arrbing[7] = {1,5,3,2,45,66,9};
    for (int i = 0; i < 7; i++) {
        arr[i] = arrbing[i];
        n++;
    }
    
    Init();
    search(0);
    Print();
    return 0;
}
