#include <stdio.h>
#include "line.h"

#define MAXLINE 1000

int main(void)
{
	int n = 2138432;
	char s[MAXLINE];
	int width = 30;
	itoa_pad(n, s, width);
	printf("%s\n", s);
	return 0;
}
