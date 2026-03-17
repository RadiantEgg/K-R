/*#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

double atof(char *s)
{
    int c, sign, i;          // 读到EOF
    double val, digit, power;
    for (i = 0; isspace(s[i]); i++);
    sign = (s[i] == '-1') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++) {
        val = val * 10 + (s[i] - '0');
    } 
    if (s[i] == '.') 
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = val * 10 + (s[i] - '0');
        power *= 10.0;
    }    
    return sign * val / power;
}

int main()
{
    char s[100];
    scanf("%s",s);
    printf("The number is %f\n", atof(s));
    return 0;
}

int getline(char line[], int max) //空行，空白行，空字符串
{
    int c, i;
    i = 0;
    while (--max > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}

int main()                              // 记账本雏形
{
    double sum, atof;
    char line[MAXLINE];
    
    sum = 0;
    while (getline(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof);
    return 0;
}



#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000
int atoi(char *s)
{ 
    int val, power, i, sign;
    for (i = 0; isspace(s[i]); i++);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0; isdigit(s[i]); i++) {
        val = val * 10 + (s[i] - '0');
    }
    return sign * val;
}

int main()
{
    char s[MAXLINE];
    scanf("%s", s);
    printf("数字是: %d\n", atoi(s));
    return 0;
}
    */

// 扩展读入科学计数法

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

double atof(char *s)
{
    double val, power;
    int i, sign;
    for (i = 0; isspace(s[i]); i++) ;
    sign = (s[i] == '-') ? -1 : 1;
    for (val = 0.0; isdigit(s[i]); i++) {
        val = val * 10 + (s[i] - '0');
    }
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = val * 10 + (s[i] - '0');
        power *= 10;
    }
    return sign * val / power;
}

double atof_plus(char *s)
{
    double num, power;
    int exp;
    char *p = s;
    while(*p != 'e' && *p != 'E')
        p++;
    num = atof(s);
    exp = (int)atof(p + 1);
    power = 1.0;
    if (exp > 0) {
        while (exp > 0) {
            power *= 10;
            exp--;
        }
    } else {
        while (exp < 0) {
            power /= 10;
            exp++;
        }
    }
    return num * power;
}

int main()
{
    char s[MAXLINE];
    scanf("%s", s);
    printf("The number is %f\n", atof_plus(s));
    return 0;
}