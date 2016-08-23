#include <stdio.h>
#include "line.h"

#define MAXLINE 1000
#define abs(x) ( (x) < 0 ? -(x) : (x) )
/*
int itob(int n, char s[], int b);
*/
int main(void)
{
	char s[MAXLINE];
	int n = -323;
	int b = 11;	

	int flag = itob(n,s,b);
	if (!(flag)) {
		return 1;
	}
	printf("%s\n", s);
	return 0;
}
/*
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
*/
