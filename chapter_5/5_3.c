#include <stdio.h>

long int my_strlen(char *s)
{
    int len;
    for (len = 0; *s != '\0'; s++)
        len++;
    return len;
}
int main()
{
    // int a[10];
    // int *p = &a[0];
    // int x = *p;
    // printf("%p\n", &a[0]);
    // printf("%p\n", &a[9]);
    // return 0;
    char arr[10] = "abcde";
    char *p = "lll";
    printf("%ld\n%ld\n%ld\n", my_strlen(arr), my_strlen(p), my_strlen("hello"));
    return 0;
}

