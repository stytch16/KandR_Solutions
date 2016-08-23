#include <stdio.h>
#include "line.h"
#define MAXLINE 1000
int main(void)
{
	char s[MAXLINE];
	char t[MAXLINE];
	int pos; /* position of pattern in text streams */
	printf("Enter pattern: \n");
	getLine(t, MAXLINE);
	printf("Enter text streams:\n");
	while ( getLine(s, MAXLINE) > 0) {
		(pos = rstrindex(s,t)) < 0 ? printf("Does not exist\n") : \
			printf("Found pattern at rightmost index = %d\n", pos);
	}

	return 0;
}
