#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char **lineptr, int nlines);
void writelines(char **lineptr, int nlines);

void qsort(void **lineptr, int left, int right, int (*cmp)(void *, void *));
int numcmp(char *, char *);

int main(int argc, char **argv)
{
    int nlines;
    int numeric = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))(numeric ? numcmp : strcmp) );
        writelines(lineptr, nlines);
    } else {
        printf("input overload");
        return 1;
    }
    return 0;
}

void swap(void **v, int i, int j);

void qsort(void **v, int left, int right, int (*cmp)(void *, void *))
{
    int i, last;
    if (left >= right)
        return;
    
    swap(v, left, (left + right) / 2);

    last = left;

    for (i = left + 1; i <= right; i++)
        if (cmp(v[i], v[left]) < 0)
            swap(v, i, ++last);

    swap(v, left, last);

    qsort(v, left, last - 1, cmp);
    qsort(v, last + 1, right, cmp);
}


int numcmp(char *s, char *t)
{
    double v1 = atof(s), v2 = stof(t);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else 
        return 0;
}

void swap(void **v, int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}