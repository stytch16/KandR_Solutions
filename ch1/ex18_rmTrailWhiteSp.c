/* Program to remove trailing blanks and tabs from each line of input and 
 * delete entirely blank lines.
 * e.g
 *    this is my string    <--- spaces follow
 *			   <--- blank line entered
 *			   <--- EOF
 * this is my string	   <--- "this is my string"
 */

#include <stdio.h>
#include "line.h"  /* getline(), copy() */

#define MAXLINE 1000

//int strip(char s[], const int len);
//void clear(char s[], const int len);

int main(void)
{
	char line[MAXLINE];	/* line to hold input text stream */
	int len;
	while ((len = getLine(line, MAXLINE)) > 0) {
		len = strip(line, len);
		printf("|%s|%4d long\n", line, len);
	}

	return 0;
}
/*
 * All included in line.h
 * 
 *
int strip(char s[], const int len)
{
	int i, j;
	char temp[len];
	// Get index i of first non-whitespace character
	for (i = 0 ; (s[i] == '\t') || (s[i] == ' ') || (s[i] == '\n') ; ++i);

	// If s is full of whitespace, then change line to an empty string and return
	// s is full of whitespace if all we did was count the length of line
	if (i == len){
		clear(s, len);
		return 0;
	}
	// Get index j of last non-whitespace character
	for (j = (len - 1) ; (s[j] == '\t') || (s[j] == ' ') || (s[j] == '\n') ; --j);

	// Copy from i to j into a placeholder array
	int k;
	for (k = i; k <= j; ++k) {
		temp[k - i] = s[k];
	}
	temp[k - i] = '\0';

	clear(s, len);

	// Copy into s
	copy(temp, s);
	return (k - i); // new length
}

void clear(char s[], const int len)
{
	int i;
	for (i = 0; i < len; ++i) {
		s[i] = '\0';
	}	
}
*/
