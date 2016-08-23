#include "line.h"
#include <stdio.h>
int count(const char s[])
{
	int i;
	for (i = 0; s[i] != '\0'; ++i) ;
	return i;
}

int getLine(char line[], const int max)
{
	int c, i;
	
	/* Terminates if text stream exceeds max,
	 * if a newline is read,
	 * or if EOF is read.
	 */
	for (i = 0; i < (max - 1) && (c = getchar()) != EOF && c != '\n'; ++i) {
		line[i] = c;
	}

	if (c == '\n') {
		line[i] = c;
		++i;
	}

	line[i] = '\0';
	return i;

}
void copy(char dest[], const char source[])
{
	int i;
	for(i = 0; (dest[i] = source[i]) != '\0'; ++i);
}

int strip(char s[])
{
	int i, j;
	// Get index i of first non-whitespace character
	for (i = 0 ; (s[i] == '\t') || (s[i] == ' ') || (s[i] == '\n') ; ++i);

	// Get length of line
	int len = count(s); 

	// If s is full of whitespace, then change line to an empty string and return
	if (i == len){
		clear(s, len);
		return 0;
	}
	// Get index j of last non-whitespace character
	for (j = (len - 1) ; (s[j] == '\t') || (s[j] == ' ') || (s[j] == '\n') ; --j);

	// Copy from i to j into a placeholder array
	char temp[len];
	int k;
	for (k = i; k <= j; ++k) {
		temp[k - i] = s[k];
	}
	temp[k - i] = '\0';

	clear(s, len);

	// Copy into s
	copy(s, temp);
	return (k - i); /* new length */
}

void clear(char s[], const int len)
{
	int i;
	for (i = 0; i < len; ++i) {
		s[i] = '\0';
	}	
}

void reverse(const char s[], char r[])
{
	int i, j;

	for (i = count(s) - 1, j = 0 ; i >= 0  ; --i, ++j) {
		r[j] = s[i];
	}
	r[j] = '\0';
}

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

void printHiddenChar(const char s[])
{
	char c;
	int i;
	for (i = 0; s[i] != '\0'; ++i) {
		c = s[i];
		if (c == '\t') {
			printf("\\t");
		}
		else if (c == '\n') {
			printf("\\n");
		}
		else if (c == '\\') {
			printf("\\\\");
		}
		else if (c == '\b') {
			printf("\\b");
		}
		else {
			putchar(c);
		}
	}
}

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
