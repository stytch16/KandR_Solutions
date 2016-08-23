#include "line.h"
#include <stdio.h>
#include <string.h>
#define abs(x) ((x) < 0 ? -(x) : (x))
#define digit(x) ('0' <= x && x <= '9') ? 1 : 0

int getLine(char s[], int lim)
{
	int c;  /* char input */
	int i;  /* index */
	for (i = 0 ; --lim > 0 && (c = getchar()) != EOF \
		       && c != '\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}

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

int strindex(char s[], char t[])
{
	int i, j, k;
	for (i = 0 ; s[i] != '\0' ; ++i) {
		for (j = i, k = 0 ; t[k] != '\0' && \
			       s[j] == t[k]; ++j, ++k) {
			// Terminates immediately if first letters don't
			// match. If they do match, loop will continue until
			// either a match fails or we reach end of t.
		}
		if (t[k] == '\0') {
			return i;
		}
	}
	return -1;
}

int rstrindex(char s[], char t[])
{
	
	/* <!-- Thu Aug  4 16:24:56 2016 -->
	 * <!-- TODO: Strip strings s and t of of leading and trailing whitespace -->
	 */
	
	int i, j, k;
	for (i = strlen(s) - 1 ; i >= 0 ; --i) {
		for (j = i , k = 0; t[k] != '\0' && s[j] == t[k] ; ++j, ++k) {
		}
		if (t[k] == '\0') {
			return i;
		}
	}
	return -1;
}
int atoi(const char s[])
{
	return (int)(atof(s));
}
double atof(const char s[])
{
	double val; /* float value */
	double power; /* value after '.' */
	double sci; /* value after 'e' or 'E' */
	double temp; /* temporary variable */
	int i, sign, sci_sign; /* index, negative or positive */
	for (i = 0 ; s[i] == ' ' ; ++i) {
		/* skip white space */
	}
	sign = ( s[i] == '-' ) ? -1 : 1;
	if (s[i] == '+' || s[i] == '-') {
		++i;
	}
	for (val = 0.0 ; digit(s[i]) ; ++i) {
		val = 10.0 * val + (s[i] - '0');
	}
	if (s[i] != '.') {
		return val;
	}
	++i; /* calculate value after . */
	for (power = 1.0 ; digit(s[i]) ; ++i) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	
	if (s[i] != 'e' && s[i] != 'E') {
		return sign * val / power;
	}
	++i; /* calculute value after e */
	sci_sign = 1;
	if (s[i] == '-') {
		sci_sign = -1;
		++i;
	}
	else if (s[i] == '+') {
		++i;
	}
	for (temp = 0.0 ; digit(s[i]) ; ++i) {
		temp = 10 * temp + ( s[i] - '0' );
	}
	
	for (i = 0 , sci = 1.0; i < temp ; ++i) {
		sci *= 10.0;
	} 

	return sci_sign < 0 ? sign * val / power * (1.0 / sci) : sign * val / power * sci;
}
