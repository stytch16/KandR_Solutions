/*
 * Program to replace strings of spaces with minimum number of tabs and spaces.
 * 1 tab = 8 spaces
 */

#include <stdio.h>
#include "line.h"

#define MAXLINE 1000
#define SPACE_PER_TAB 8

void entab(char line[]);
int countFrontSpaces(const char line[]);

int main(void)
{
	char line[MAXLINE];

	while ( getLine(line, MAXLINE) > 0 ) {
		entab(line);
		printf("%s\n",line );
		printHiddenChar(line);
		putchar('\n');
	}		
	return 0;
}

void entab(char line[]) {

	int nFrontSpaces;
	int nTabs;
	int nRemainSpaces;
	
	char temp[MAXLINE];
	int i, j;
	
	nFrontSpaces = countFrontSpaces(line);
	printf("Counted %d spaces\n", nFrontSpaces);


	nTabs = nFrontSpaces / SPACE_PER_TAB;
	nRemainSpaces = nFrontSpaces % SPACE_PER_TAB; 
		
	strip(line);

	for (i = 0; i < nTabs; ++i) {
		temp[i] = '\t';
	}
	
	for (j = 0; j < nRemainSpaces; ++i, ++j) {
		temp[i] = ' ';
	}
	temp[i] = '\0';

	prepend(line, temp, MAXLINE);
}

int countFrontSpaces(const char line[]) {
	int i;
	for (i = 0; line[i] == ' '; ++i);
	return i;
}
