#include <stdio.h>
#define MAXLINE 1000

int getline(char *line, int lim);
int strindex(char *line, char *target);


int main()      // 两两比较最好用单独两个指针下标
{
    int found = 0;
    char line[MAXLINE];
    char target[MAXLINE];
    printf("输入目标字符串:");
    scanf("%s", target);
    getchar();
    while (getline(line, MAXLINE) > 0) {
        if (strindex(line, target) >= 0) {
            printf("%s\n", line);
            found++;
        }       
    }
    printf("有%d行出现%s\n", found, target);
    return 0;
}

int getline(char *line, int lim)            // 读行理论，存换行再加结束符
{
    int c;              // c可能读到EOF!!!
    int i;
    /* for (i = 0; lim > 0 && (c = getchar()) != EOF && c != '\n'; lim--) {
        line[i++] = c;
    } */

    

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')        // 是大于，多一个位置给 '\0'
        line[i++] = c;
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}

int strindex(char *line, char *target)
{
    int i, j, k;
    /* for (i = 0; !found && line[i]; i++) {
        for (j = 0; target[j]; j++) {
            if (target[j] && (line[i + j] == target[j])) {
                continue;
            } else {
                break;
            }
        }
        if (!target[j]) {
            found = 1;
        }
    }
    return found ? i : -1; 
}*/
 
    for (i = 0; line[i] != 0; i++) {
        for (j=i, k=0; target[k] != '\0' && line[j] == target[k]; j++, k++);
        if (k > 0 &&!target[k]) {       // K&R 认为空串“”不应该被找到
            return i;
        }
    }
    return -1;
}



// strrindex(s, t) 返回字符串t在s最右边出现的位置，未出现返回-1

#include <stdio.h>

#define MAXLINE 100

int strrindex(char *s, char *t);

int main()
{
    char s[MAXLINE];
    char t[MAXLINE];
    scanf("%s", s);
    scanf("%s", t);
    int result;
    result = strrindex(s, t);
    if (result == -1) {
        printf("%s 在 %s 中不存在\n",t, s);
    } else {
        printf("%s 在 %s 最右边出现的位置是%d\n", t, s, result);
    }
    return 0;
}

int strrindex(char *s, char *t)
{
    if (t[0] == '\0')
        return -1;
    int i, j, k, index;
    index = -1;
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) ;
        if (t[k] == '\0') {
            index = i;
        }
    }
    return index;
}


// 改进版本，采用指针以及右扫描
#include <stdio.h>
#include <string.h>

int strrindex(char *s, char *t)
{
    int len_s, len_t, i, j, k;
    if (s == NULL || t == NULL || t[0] == '\0')
        return -1;
    len_s = strlen(s);
    len_t = strlen(t);
    if (len_s < len_t)
        return -1;
    for (i = len_s-len_t; i >= 0; i--) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++);
        if (t[k] == '\0')
            return i;
    }
    return -1;
}