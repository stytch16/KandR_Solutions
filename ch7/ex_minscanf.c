#define DEBUG 0 /* Toggle debugging statements */
#define _GNU_SOURCE
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int minscanf(char *fmt, ...);

int main(void)
{
	char *wkday, *month, *ampm; 
	int day, year;
	double time;
	int n = minscanf("%s %s %d %d %f %s", &wkday, &month, &day, &year, &time, &ampm);
	printf("N=%d\n", n);
	printf("Today is WKDAY=%s, MONTH=%s DAY=%d, YEAR=%d, TIME=%f, AMPM=%s\n", wkday, month, day, year, time, ampm);
	return 0;
}

int minscanf(char *fmt, ...) /* variable list of args */
{
	va_list ap; /* pointer to variable list */
	char *p; /* pointer to fmt string */
	char *s; /* pointer to substring from buffer */
	ssize_t ssize;
	int n; /* number of successful inputs */

	union  {
		char **sval;
		int *ival;
		double *dval;
	} fmtcode;

	/* get a string from user */
	size_t bufsize = 128;
	char *buffer; /* pointer to string input */
	buffer = (char *)malloc(bufsize + 1);
	ssize_t len;
	if (!buffer) {
		printf("No more space available\n");
		return 0;
	}
	len = getline(&buffer, &bufsize, stdin);
	if (len < 0) {
		printf("Failed to scan input\n");
		return 0;
	}
	if (DEBUG) { printf("\t ****DEBUG at minscanf--> GOT %s OF LEN = %ld ****\n", buffer, len); }
	n = 0;
	ssize = 32;
	s = (char *)malloc(ssize + 1);
	char *t = s; /* start pointer */
	va_start(ap, fmt); /* pointer to first unnamed arg */
	for (p = fmt ; *p ; ++p) {
		if (*p != '%') {
			/* ignore everything until an format argument is found */
			continue;
		}
		while (isspace(*buffer))
			++buffer; /* skip over white space */
		while (*buffer && !isspace(*buffer)) {
			*s++ = *buffer++;
		}
		*s = '\0';
		s = t;
		++buffer; /* go to next position in buffer */

		if (DEBUG) { printf("\t ****DEBUG at minscanf--> EXTRACTED %s ****\n" , s); }

		switch (*++p) {
			case 'd':
				fmtcode.ival = va_arg(ap, int*);
				*(fmtcode.ival) = atoi(s);
				if (DEBUG) { printf("\t ****DEBUG at minscanf--> INT ARG = %d ****\n", *(fmtcode.ival)); }
				break;
			case 'f':
				fmtcode.dval = (va_arg(ap, double*));
				*(fmtcode.dval) = atof(s);
				if (DEBUG) { printf("\t ****DEBUG at minscanf--> FLOAT ARG = %.8g ****\n" , *(fmtcode.dval)); }
				break;
			case 's':
				fmtcode.sval = (va_arg(ap, char **));
				*fmtcode.sval = (char *)malloc(sizeof(s));
				strcpy(*fmtcode.sval, s);
				if (DEBUG) { printf("\t ****DEBUG at minscanf--> STRING ARG = %s ****\n" , *fmtcode.sval); }
				break;
			default:
				printf("Unrecognized format code (%%%c)\n", *p );
				return n;
		}
		++n;
	}
	va_end(ap);
	free((void *)s);
	return n;
}
