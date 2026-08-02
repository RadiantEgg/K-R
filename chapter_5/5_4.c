#include <stdio.h>

// 有缺陷的存储分配程序
// 8.7 实现malloc 和free
#define MALLOCSIZE 1024

static char allocbuf[MALLOCSIZE];
static char *allocp = allocbuf;
char *alloc(int n)
{
    if (allocbuf + MALLOCSIZE - allocp >= n) {
        allocp += n;
        return alloc - n;
    }
    else
        return NULL;
}

void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + MALLOCSIZE) 
        allocp = p;
}


int my_strlen(char *s)
{
    char *p = s;
    while (*p != '\0')
        p++;
    return p - s;
}