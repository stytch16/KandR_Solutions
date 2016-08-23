#include <stdio.h>
#include "line.h"
#include <string.h>

#define MAXLINE 1000
int main(void)
{
	char s[MAXLINE];
	while (getLine(s, MAXLINE) > 0) {
		printf("\nFloating value is %f\n", atof(s));
	}
	return 0;
}
