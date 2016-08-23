#include <stdio.h>
#include "line.h"

#define MAXLINE 1000
/* Added to line.h
void squeeze(char s1[], const char s2[]);
int find(const char s[], const char c);
*/
int main(void)
{
	char s[MAXLINE];
	char x[MAXLINE];
	while(printf(": ") && getLine(s, MAXLINE) != 0 ) {
		printf(": ");
		getLine(x, MAXLINE);
		printf("Squeezing %s from %s\n", x, s);
		squeeze(s, x);
		printf(">> %s\n", s);
	}
	return 0;
}
/*
void squeeze(char s1[], const char s2[])
{
	int i, j;
	for (i = j = 0; s1[i] != '\0'; ++i) {
		if ( find(s2, s1[i]) < 0) {
			s1[j++] = s1[i];
		}
	}
	s1[j] = '\0';
}

int find(const char s[], const char c)
{
	int i;
	for (i = 0; s[i] != '\0'; ++i) {
		if (s[i] == c) {
			return i;
		}
	}
	return -1;
}
*/
