#include "line.h"
#include <stdio.h>
#define MAXLINE 1000

//void reverse(char s[], char r[], const int len);

int main(void)
{
	int len;
	char line[MAXLINE];
	char reversed[MAXLINE];
	
	while ((len = getLine(line, MAXLINE)) > 0) {
		reverse(line, reversed, len);
		printf("%s\n", reversed );
	}	
	return 0;
}

/* Included in line.h
 *
 *
void reverse(char s[], char r[], const int len)
{
	int i, j;
	for (i = (len - 2), j = 0 ; i >= 0  ; --i, ++j) {
		r[j] = s[i];
	}
	r[j++] = '\n';
	r[j] = '\0';
}
*/
