// 逆波兰运算器

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXVAL 100
#define BUFSIZE 100
#define MAXOP 100
#define NUMBER   '0'

int getop(char *);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void print(void);
void exchange(void);
void clean(void);


char buf[BUFSIZE];
int bufp = 0;
int sp = 0;
double val[MAXVAL];

int main()
{
    int type;
    char s[MAXOP];
    double op1, op2;

    while ((type = getop(s)) != EOF) {
        switch (type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (fabs(op2) > 1e-10)     
                    push(pop() / op2);
                else 
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                op1 = pop();
                if (fabs(op2) > 1e-10){
                    if (fabs(op1 - (int)op1) > 1e-10 || fabs(op2 - (int)op2) > 1e-10)
                        printf("error: modulus requires integers\n");
                    else
                        push((int)op1 % (int)op2);
                }       
                else    
                    printf("error: zero modulus\n");
                break;
            case 'p':
                print();
                break;
            case 'e':
                exchange();
                break;
            case 'c':
                clean();
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command\n");
                break;
        }
    }
    return 0;
}




void push(double f)
{
    if(sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push\n");
    }
}

double pop(void)
{
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(char *s)
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';    // 提前把字符串合法化
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;
    if (c == '-') {
        int next = getch();
        if (!isdigit(next)) {
            ungetch(next);
            return c;
        } else {
            s[++i] = next; 
            c = next;
        }
    }
    if (isdigit(c)) 
        while (isdigit((s[++i] = c = getch())));
    if (c == '.') 
        while (isdigit((s[++i] = c = getch())));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}




int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
}


void print()
{
    if (sp == 0)
        printf("print: stack top empty\n");
    else {
        int top = sp -1;
        printf("top: \t.8g%f\n", val[top]);
    }
}

void exchange()
{
    int index_1, index_2;
    index_1 = sp - 1;
    index_2 = index_1 - 1;
    if (index_2 < 0)
        printf("exchange: not enough operators in stack\n");
    else {
        double temp = val[index_1];
        val[index_1] = val[index_2];
        val[index_2] = temp;
    }
}

void clean()
{
    int i = 0;
    if (sp == 0) 
        printf("clean: stack is empty\n");
    else 
        sp = 0;     // 栈清空只与sp位置有关
}