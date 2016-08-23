#include "line.h"
#include <stdio.h>
#include <string.h>
#define abs(x) ( (x) < 0 ? -(x) : (x))

void escape(char dest[], const char source[]) {
	int i, j;
	for (i = 0, j = 0; source[i] != '\0'; ++i)
	{
		switch (source[i]) {
			case '\n':
			       	dest[j++] = '\\';
			       	dest[j++] = 'n';
				break;
			case '\t':
			       	dest[j++] = '\\';
			       	dest[j++] = 't';
				break;
			case '\\':
			       	dest[j++] = '\\';
			       	dest[j++] = '\\';
				break;
			case '\b':
				dest[j++] = '\\';
				dest[j++] = 'b';
			default:
				dest[j++] = source[i];
				break;
		}
	}
	dest[j] = '\0';
}

void expand(const char shorthand[], char expanded[])
{
	int c;
	int i = 0, j = 0;
	int prev, next;
	// Return if string is empty
	if (shorthand[i] == '\0') {
		expanded[j] = '\0';
		return;
	}
	// Copy the first element.
	// Keep copying until a '-' is found.
	// If '-' is found,
	// 	Get element x before it and y after it.
	// 	Keep incrementing x and copying until x = y.
	// 	Then copy y.
	for (expanded[j++] = shorthand[i++]; shorthand[i] != '\0'; ++i) {
		if (shorthand[i] == '-') {

			for (prev = i-1, next = i+1, c = shorthand[prev];\
				       	c != shorthand[next];\
				       	++prev) {
				expanded[j++] = ++c;
			}
			++i; /* The element after - has already been dealt with */

		}
		else {
			expanded[j++] = shorthand[i];
		}
	}
	expanded[j] = '\0';
}

void itoa(int n, char s[])
{
	int i;
	int sign;
	
	i = 0;
	sign = n;

	do {
		s[i++] = abs( n % 10 ) + '0';
	} while ((n /= 10) != 0);

	if (sign < 0){
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);
}

void itoa_pad(int n, char s[], const int width)
{
	int i;
	int sign;
	
	i = 0;
	sign = n;

	do {
		s[i++] = abs( n % 10 ) + '0';
	} while ((n /= 10) != 0);

	if (sign < 0){
		s[i++] = '-';
	}

	while (i < (width - 1)){
	       s[i++] = ' ';
	}	
	s[i] = '\0';
	reverse(s);
}


void reverse(char s[])
{
	int i, j;
	for (i = 0, j = strlen(s) - 1; i < j; ++i, --j)
	{
		swap(s, i, j);
	}
}

void swap(char s[], unsigned int i, unsigned int j)
{
	int c = s[i];
	s[i] = s[j];
	s[j] = c;
}

int itob(int n, char s[], int b)
{
	const int NDIGITS = 10, MAXBASE_REPR = 36;
	if (b < 2 || b > (MAXBASE_REPR + 1)) {
		printf("Base must be 2 - 36. Terminating\n");
		return 0;
	}
	else if (b == NDIGITS) {
		itoa(n, s);
	}
	else {
		int i, t, sign;
		sign = n;
		i = 0;
		do {
			t = abs(n % b);
			if (t < NDIGITS) {
				s[i++] = t + '0';
			}
			else if ((NDIGITS <= t) && \
				       	(t < MAXBASE_REPR)){
				s[i++] = (t - NDIGITS) + 'a';
			}
		} while ((n /= b) != 0);
		if (sign < 0) {
			s[i++] = '-';
		}
		s[i] = '\0';

		reverse(s);
	}
	return 1;
}
