#include <stdio.h>

int main() 
{
    // int a = 10;
    // int *p = &a;
    // printf("%ld\n", sizeof(p));
    // printf("%p\n", &a);
    // printf("%p\n", p);
    // printf("%p\n", &p);
    // printf("%d\n", *p);

    int x = 1, y = 2, z[10];

    int *ip;
    ip = &x;
    y = *ip;
    ip = &z[0];
    return 0;
}