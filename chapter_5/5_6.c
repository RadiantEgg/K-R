#include <stdio.h>
#include <string.h>
#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char **lineptr, int nlines);
void writelines(char **lineptr, int nlines);

// void qsort(char **lineptr, int left, int right);

// int main()
// {
//     int nlines;

//     if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
//         qsort(lineptr, 0, nlines - 1);
//         writelines(lineptr, nlines);
//         return 0;
//     } else {
//         printf("Error: to many lines\n");
//         return 1;
//     }
// }

// #define MAXLEN 1000

// int getline(char *s, int n);

// int readlines(char **lineptr, int maxlines)
// {
//     int len, nlines = 0;
//     char *p, line[MAXLEN];
//     while (len = getlen(line, MAXLEN) >= 0) {
//         if (nlines >= MAXLINES) 
//             return -1;

//         // 删除换行符
//         line[len - 1] = '\0';
//         p = malloc(len);
//         strcpy(p, line);
//         lineptr[nlines++] = p;
//     }
//     return nlines;
// }

// // void writelines(char *lineptr, int nlines)
// // {
// //     for (int i = 0; i < nlines; i++) {
// //         printf("%s\n", lineptr[i]);
// //     }
// // }

// void writelines(char **lineptr, int nlines)
// {
//     while (nlines--) 
//         printf("%s\n", *lineptr++);
// }

// void qsort(int *v, int left, int right)
// {
//     int i, last;
    
//     if (left >= right)   // 数组元素个数小于2
//         return;
//     swap(v, left, (left + right) / 2);  // 划分子集元素
//     last = left;    // last 是最后一个小于基准的位置
//     for (i = left + 1; i <= right; i++) {
//         if (v[i] < v[left])
//             swap(v, ++last, i);
//     }
//     swap(v, left, last);
//     qsort(v, left, last - 1);
//     qsort(v, last + 1, right);
// }

// void qsort(char **v, int left, int right)
// {
//     int i, last;

//     if (left >= right)
//         return;
//     swap(v, left, (left + right) / 2);
//     last = left;
//     for (i = left + 1; i < right; i++) 
//         if (strcmp(v[i], v[left]) < 0)
//             swap(v, ++last, i);
//     swap(v, left, last);
//     qsort(v, left, last - 1);
//     qsort(v, last + 1, right);
// }

// void swap(char ** v, int i, int j)
// {
//     char *temp;
//     temp = v[i];
//     v[i] = v[j];
//     v[j] = temp;
// }


void swap(void *a, void *b, size_t size)
{
    unsigned char tmp;  // unsigned char可以访问任意对象的字节表示

    for (size_t i = 0; i < size; i++) {     // 先把通用指针转化为unsigned char再取字节
        tmp = ((unsigned char *)a)[i];
        ((unsigned char *)a)[i] = ((unsigned char *)b)[i];
        ((unsigned char *)b)[i] = tmp;
    }
}

void *element(void *base, size_t index, size_t size)   // 直接用void*，因为后面的函数传地址都是void*，可以减少一次类型转换
{
    return (void *)((char *)base + index * size);
}

void qsort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *))
{
    // 元素个数小于2直接返回
    if (nmemb < 2)
        return;
    
    // 将第nmemb / 2 个元素设置为标准值
    size_t pivot = nmemb / 2;

    swap(base, element(base, pivot, size), size);
    size_t last_index = 0;    // 小于基准的区间中的最后一个元素下标

    for (size_t i = 1; i < nmemb; i++) {
        if (cmp(element(base, i, size), 0) < 0) 
            swap(element(base, i, size), element(base, ++last_index, size), size);
    }

    // 换回去
    swap(base, element(base, last_index, size), size);

    // 基准左右分区递归
    if (last_index > 0)
        qsort(base, last_index, size, cmp);
    if (last_index + 1 < nmemb)
        qsort(element(base, last_index + 1, size) , nmemb - last_index - 1, size, cmp);
}

int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    return 0;
}

// 改版
void qosrt(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *))
{
    quick_sort(base, 0, nmemb - 1, size, cmp);  //  初始化一个数组并启动排序
}

void quick_sort(void *base, size_t left, size_t right, size_t size, int (*cmp)(const void *,const void *))
{
    if (left >= right)
        return;

    size_t pivot = partition(base, left, right, size, cmp);

    quick_sort(base, left, pivot - 1, size, cmp);
    quick_sort(base, pivot + 1, right, size, cmp);
}


size_t partition(void *base, size_t left, size_t right, size_t size, int (*cmp)(const void *,const void *))
{
    size_t last = left;

    for (size_t i = left + 1; i <= right; i++) {
        if (cmp(element(base, i, size), element(base, left, size)) < 0) 
            swap(element(base, ++last, size), element(base, i, size), size);
    }

    swap(element(base, left, size), element(base, last, size), size);

    return last;
}