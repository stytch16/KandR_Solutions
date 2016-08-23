#include <stdio.h>
#include "line.h"
#define MAXLINE 1000
/* Added to line.h
int any(const char s1[], const char s2[]);
*/
int main(void)
{
	char s1[MAXLINE];
	char s2[MAXLINE];

	while (printf("\n: ") && getLine(s1, MAXLINE) > 0 ) {
		printf("\n: ");
		getLine(s2, MAXLINE);

		printf("\nEnd result: %d\n", any(s1, s2));
	}

	return 0;
}

/*
int any(const char s1[], const char s2[])
{
	int i;
	for (i = 0; s1[i] != '\0'; ++i) {
		if (find(s2, s1[i]) >= 0) {
			return i;
		}
	}
	return -1;
}
*/
