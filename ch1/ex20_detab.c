/*
 * Program to replace tabs in input with proper number
 * of spaces to next tab stop.
 */

#include <stdio.h>
#include "line.h"

#define N_SPACES 3
#define MAXLINE 1000

void entab(char s[], int n, int lim);
int countTabs(char s[]);
//int prepend(char dest[], const char source[], const int lim);
//int append(char dest[], const char source[], const int lim);

int main(void)
{
	char line[MAXLINE];
	while ( getLine(line, MAXLINE) > 0 )
	{
		entab(line, N_SPACES, MAXLINE);
		printf("%s\n", line);
	}
	return 0;
}

void entab(char s[], int n, const int lim)
{
	int nTabs = countTabs(s);
	int nSpaces = nTabs * n;
	
	int newLen = strip(s);

	if ((nSpaces + newLen) < (lim - 1)) { 
		
		char t[MAXLINE];
		int i;
		for (i = 0; i < nSpaces; ++i) {
			t[i] = ' ';
		}
		t[i] = '\0';

		prepend(s, t, lim);
	}
	else {
		printf("Overflow Error: Adding %d spaces to %s\n", nSpaces, s);
	}
}

int countTabs(char s[])
{
	int i;
	for (i = 0; s[i] == '\t'; ++i);
	return i;
}
/* 
 * Added to line.h
 *
int prepend(char dest[], const char source[], const int lim)
{
	char temp[lim];

	// Copy source into temp except the null character
	int i;
	for (i = 0; source[i] != '\0'; ++i) {
		temp[i] = source[i];
	}
	
	// Append dest to temp
	int j;
	for (j = 0; (i < (lim - 1)) &&  ((temp[i] = dest[j]) != '\0'); ++j, ++i);

	// Copy temp to dest
	copy(temp, dest);

	// Return total size of prepended array
	return i;
}

int append(char dest[], const char source[], const int lim)
{
	// Get index of last char of dest
	int i;
	for (i = 0; dest[i] != '\0'; ++i);

	// Append source to dest 
	int j;
	for(j = 0; (i < (lim - 1)) && (dest[i] = source[j]) != '\0'; ++i, ++j);

	return i;
}
*/
