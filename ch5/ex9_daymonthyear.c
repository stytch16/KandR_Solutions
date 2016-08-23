#include <stdio.h>
int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main(void)
{
	int year = 1993;
	int month = 9;
	int day = 16;

	int yearday = 48;
	int pmonth;
	int pday;

	printf("%d\n", day_of_year(year, month, day));
	month_day(year, yearday, &pmonth, &pday);
	printf("%d of %d is %d, %d\n", yearday, year, pmonth, pday);

	return 0;
}

int day_of_year(int year, int month, int day)
{
	char *p; /* To point to either daytab[0] or daytab[1] */
	int i, leap;

	/* Is year a leap year? */
	leap = ( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0 );
	/* Get the right set of number of days per month */
	p = daytab[leap];
	/* Calculate number of days for each month preceding the month argument */
	for (i = 1, ++p; i < month ; ++i) {
		day += *p++;
	}
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	char *p;
	int leap;

	/* Is year a leap year? */
	leap = ( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0 );
	/* Get the right set of number of days per month */
	p = daytab[leap];

	for (*pmonth = 0, *pday = yearday ; *pday > *p ; ++*pmonth, ++p) {
		*pday -= *p;
	}
}
