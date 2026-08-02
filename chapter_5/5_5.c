#include <stdio.h>
#include <string.h>

void strcpy_1(char *s, char *t)
{
    int i = 0;
    while ((s[i] = t[i]) != '\0')
        i++;
}

void strcpy_2(char *s, char *t)
{
    while ((*s = *t) != '\0')
        s++, t++;
}

void strcpy_3(char *s, char *t)
{
    while (*s++ = *t++)
        ;
}

int strcmp_1(char *s, char *t)
{
    int i;
    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
}

int strcmp_2(char *s, char *t)
{
    for(; *s == *t; s++, t++)
        if(*s == '\0')
            return 0;
    return *s - *t;
}

void my_strcat(char *s, char *t)
{
    while (*s)
        s++;
    while (*s++ = *t++)
        ;
}

int my_strend(char *s, char *t)
{
    s += strlen(s) - strlen(t);
    while (*s != '\0' && *s == *t)
        s++, t++;
    return (*s == '\0' && *t == '\0') ? 1 : 0;
}

char* my_strncpy(char *s, const char *ct, size_t n)
{
    char *d = s;
    while (*ct && n--) {
        *s = *ct;
        s++;
        ct++;
    }
    while (n--) {
        *s = '\0';
        s++;
    }
    return d;
}

int my_strncmp(const char *s, const char *t, size_t n)
{
    while (n-- && *s == *t) {
        if (*s == '\0')
            return 0;
        s++;
        t++;
    }

    return *(unsigned char *)s - *(unsigned char *)t;
}

char *my_strncat(char *s, const char *t, size_t n)
{
    char *d = s;
    while (*s)
        s++;
    while (*t && n--) {
        *s = *t;
        s++;
        t++;
    }
    *s = '\0';
    return d;
}

int main()
{
    char s[10] = "xxxxx";
    const char *t = "abc";
    printf("%s\n", my_strncat(s, t, 4));
    return 0;
}