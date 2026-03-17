// 1.5 字符输入/输出

// 1.5.1 文件复制
#include <stdio.h>
#include <string.h>
#include <limits.h>
/*


// 将输入复制到输出 版本1 
int main()
{
    int c;
    c = getchar();          // 用int不用char是因为读入EOF = -1
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }
    return 0;
}

// 将输入复制到输出 版本2 
int main()
{
    int c;
    while ((c = getchar()) != EOF)
        putchar(c);
    return 0;
}

// 1.5.2 字符计数

// 统计输入的字符数 版本1 
int main()
{
    long nc = 0;            // 不用int是因为可能只占16位

    while (getchar() != EOF)
        nc++;
    printf("%ld\n", nc);
    return 0;
}

// 统计输入的字符数 版本2 
int main()
{
    double nc;              // 表示更大的数
    for (nc = 0; getchar() != EOF; nc++);
    printf("%.0f\n", nc);   // .0强制转换为整数
    return 0;
}

// 1.5.3 行计数

// 统计输入的行数 
int main()
{
    int c, nl = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            nl++;
    printf("%d\n", nl++);
    return 0;
}

// 连续空格只保留一个 


int main()
{
    int c, space = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (space == 0) {
                putchar(c);
                space = 1;
            }
        }
        else {
            space = 0;
            putchar(c);
        }
    }
    return 0;
}

// “上一个”标记法

int main()
{
    int c, last = 0;
    while ((c = getchar()) != EOF) {
        if (c != ' ' || last != ' ')            // 不是空格或者是空格但上一个不是空格
            putchar(c);
        last = c;
    }
    return 0;
}

// 第一个字符之前的空格都跳过, 后面连续空格只保留一个 

// 版本1 开头标记变量 

//状态先处理， 状态转变的时候不要进行操作，后续进入状态之后用if不是else

int main()
{
    int c, last = 0;
    int in_content = 0;
    while ((c = getchar()) != EOF) {
        // 处理开头部分并在进入前做好状态转换
        if (!in_content) {
            if (c == ' ')
                continue;
            else {
                in_content = 1;
            }
        }

        //处理字符部分
        if (c != ' ' || last != ' ') {
            putchar(c);
            last = c;
        }
    }
    return 0;
}



// 1.5.4 单词计数 wc
#define IN 1
#define OUT 0
int main()
{
    int c, nl, nc, nw, state;
    state = OUT;
    nl = nc = nw = 0;
    while ((c = getchar()) != EOF) {
        nc++;
        if (c == '\n')
            nl++;
        if (c == '\n' || c == '\t' || c == ' ') {
            state = OUT;
        }
        else {
            if (state == OUT) {
                state = 1;
                nw++;
            }else {
                continue;
            }
        }
    }
    printf("%d %d %d\n", nl, nc, nw);
    return 0;
}


// 每行一个单词打印输入           

#define IN 1
#define OUT 0
int main()
{
    int c, state;
    state = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                putchar('\n');
            }
            state = OUT;
        }else {
            if (state == OUT) {
                state = IN;
            }
            putchar(c);
        }
    }
    return 0;
}

#define MAXLINE 1000

int getline(char *s)
{
    int len = 0, i;
    int c;
    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    s[i] = '\0';
    return i;
}
int main()
{
    int len, max = 0;
    char line[MAXLINE];
    char longest[MAXLINE];
    while ((len = getline(line)) > 0) {
        if (len > max) {
            max = len;
            strcpy(longest,line);
        }
    }
    if (max > 0) {
        printf("%s\n", longest);
    }
    return 0;
}



// 删除输入行末尾的空格和制表符，同时删掉空行（全是' '和'\t'或只有'\n'）
#define MAXLINE 1000

int getline(char *s)
{
    int c, i;
    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}
int main()
{
    int len, i = 0;
    char line[MAXLINE];
    while ((len = getline(line)) > 0) {
        for (i = len - 1; i >= 0; i--) {
            char c = line[i];
            if (c != ' ' && c != '\t' || c != '\n')
                break;
        }
        if (i >= 0) {
            line[i+1] = '\0';
        }else {
            line[0] = '\0';
        }
    }
    return 0;
}

*/

// 超前预读，用缓冲区管理

int main()
{
    int c, started = 0;
    int blank_buffer = 0;
    while ((c = getchar()) != EOF) {
        // 用状态标记处理前置空白
        if (!started) {
            if (c != ' ' && c != '\t') {
                started = 1;
            }else {
                continue;
            }
        }

        // 处理正文
        if (c == ' ' || c == '\t') {
            blank_buffer++;
        }else if (c == '\n') {
            blank_buffer = 0;
            putchar(c);
            started = 0;
        }else {
            if (blank_buffer > 0) {
                putchar(' ');
                blank_buffer = 0;
            }
            putchar(c);
        }
    }
    return 0;
}