#include <stdio.h>
#include <string.h>

char *month_name(int n)
{
    static char *name[] = {
        ""
    };

    return (n < 1 || n > 12) ? name[0] : name[n];
}