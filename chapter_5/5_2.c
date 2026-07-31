#include <stdio.h>
#include <ctype.h>
// void swap(int* x, int *y)
// {
//     int temp = *x;
//     *x = *y;
//     *y = temp;
// }

// int main()
// {
//     int a = 0, b = 1;
//     swap(&a, &b);
//     printf("%d\n%d\n", a, b);
// }

/* 
getint 函数接收自由格式的输入，将字符流分解为整数，到达输入结尾的时候返回文件结束标记
*/

// 超前读入
#define BUFSIZE 128

char buf[BUFSIZE];
int bufp = 0;   // buf中下一个空闲位置

int getch(void)
{
    return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE) 
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
}


int getint(int *pn)     // *pn 存这个输入的合法整数
{
    int c, sign;

    while (isspace(c = getch()))    // 跳过空白
        ;

    if (!isdigit(c) && c != '-' && c != '+' && c != EOF) {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int next = getch();
        if (isdigit(next))
            c = next;
        else if (next != EOF){
            ungetch(next);
            ungetch(c);
            return 0;
        } 
        else {
            ungetch(next);
            return 0;
        }
    }
    
    for (*pn = 0; isdigit(c); c = getch())
        *pn = *pn * 10 + (c - '0');

    *pn *= sign;

    if (c != EOF)
        ungetch(c);
    return c;
}


// getfloat 函数

int getfloat(double *pn)     // *pn 存这个输入的合法float
{
    int c, sign;
    double fac;

    while (isspace(c = getch()))    // 跳过空白
        ;

    if (!isdigit(c) && c != '-' && c != '+' && c != EOF) {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int next = getch();
        if (isdigit(next))
            c = next;
        else if (next != EOF){
            ungetch(next);
            ungetch(c);
            return 0;
        } 
        else {
            ungetch(next);
            return 0;
        }
    }
    
    for (*pn = 0; isdigit(c); c = getch())
        *pn = *pn * 10 + (c - '0');

    if (c == '.') {
        c = getch();
    }
    for (fac = 0.1; isdigit(c); fac /= 10)
        *pn += (c - '0') * fac;

    *pn *= sign;

    if (c != EOF)
        ungetch(c);
    return c;
}