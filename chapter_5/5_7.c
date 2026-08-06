#include <stdio.h>
#include <string.h>

static char daylab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int day_of_year(int year, int month, int day)
{
    if (month < 1 || month > 12) {
        printf("illegal month\n");
        return 0;
    }
    int i, leap;
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (day < 1 || day > daylab[leap][month]) {
        printf("illegal day for the month\n");
        return 0;
    }
    for (i = 1; i < month; i++)
        day += daylab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    for (i = 1; yearday > daylab[leap][i]; i++)
        yearday -= daylab[leap][i];
    *pmonth = i;
    *pday = yearday; 
}

