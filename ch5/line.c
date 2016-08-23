#include "line.h"
#include <stdio.h>
#include <ctype.h>
#define MAX 100
#define DEBUG 1 /* Toggle debugging statements */

void str_cat(char* dest, char* source)
{
	while( *dest ) /* Move pointer to NULL of dest */
		++dest; /* If this was included in loop, it would increment over the NULL */
	while ((*dest++ = *source++));
}

int str_end(char *str, char *sub)
{
	char *start_str = str;
	char *start_sub = sub;

	for ( ; *str ; ++str) {
		/* Go to end of string */
	}
	for ( ; *sub ; ++sub) {
		/* Go to end of substring */
	}
	for (--str, --sub ; *str == *sub; --str, --sub) {
		/* Loop until mismatch or sub is back at start of string */
		if (sub == start_sub)
			return 1;
		else if (str == start_str) {
			break; /* takes care of case if str and sub have same strings */
		} /* or if sub is a longer string than str */
	}
	return 0;
}

void str_copy(char *dest, char *source)
{
	while (*source)
		*dest++ = *source++;
	*dest = '\0';
}
void str_ncopy(char *dest, const char *source, int n)
{
	while (*source && n-- > 0)
		*dest++ = *source++;
	*dest = '\0';
}

void str_ncat(char *dest, const char *source, int n)
{
	for ( ; *dest ; ++dest) {
		// Go to end of dest
	}
	while (*source && n-- > 0)
		*dest++ = *source++;
	*dest = '\0';
}

int str_cmp(const char *s, const char *t)
{
	for ( ; *s == *t ; ++s, ++t) {
		if (*s == '\0'){
			return 0;
		}
	}
	return (*s - *t);
}

/* str_ncmp: Returns <0 if s < t, 0 if s==t, >0 if s > t */
int str_ncmp(const char *s, const char *t, int n)
{
	while (n-- > 0) {
		if (*s != *t)
			return (*s - *t);
		else {
			++s; ++t;
			if (s == '\0' && t == '\0')
				break;
		}
	}
	return 0;
}

int get_line(char *s, int max) {
	char ch;
	char *t = s;
	while ( ( ch = getchar() ) != EOF && ch != '\n' && max-- > 0) {
		*s++ = ch;
	}
	if (ch == '\n'){
		*s++ = ch;
	}
	*s = '\0';
	return (s - t);
}

int atoi(const char *a)
{
	int n = 0; /* converted integer */
	while (isspace(*a))
		++a;

	while (isdigit(*a)) {
		n = 10 * n + (*a++ - '0');
	}
	return n;
}

double atof(const char *a)
{
	int sign;
	double n = 0.0; /* integer part */
	double m = 0.0; /* fraction part */
	double d = 1.0; /* denominator */

	while(isspace(*a))
		++a;
	sign = (*a == '-') ? -1 : 1;
	if (*a == '-' || *a == '+')
		++a;

	while(isdigit(*a)) {
		n = 10.0 * n + (*a++ - '0');
	}
	if (*a == '.'){
		++a;
		while (isdigit(*a)){
			m = 10.0 * m + (*a++ - '0');
			d *= 10.0;
		}
	}	
	return sign * (n + m / d);
}

char* itoa(char *a, int n)
{
	char *start = a;
	do {
		*a++ = n % 10 + '0';
		n /= 10;
	} while (n != 0);
	*a = '\0';

	reverse(start, a-1);
	return start;
}

char* reverse(char *start, char *end) 
{
	if(start < end){
		swap(start, end);
		reverse(start+1, end-1);
	}
	return start;
}

void swap(char *s, char *t)
{
	char temp = *s;
	*s = *t;
	*t = temp;
}

int str_index(char *str, char *sub)
{
	char *s, *t, *u; /* temp ptr variable */
	s = str;
	u = sub;
	while (*str) {
		if (*str == *sub) {
			t = str;
			++str; ++sub;
			while (*str++ == *sub++) {
				if (!*sub) {
					return (t - s);
				}
			}
			sub = u;
		}
		++str;
	}
	return -1;
}
