#include <stdio.h>
#define MAXLINE 1000		/* maximum input line */

int getLine(char line[], const int max);
void copy(const char source[], char dest[]);

int main(void)
{
	int len;		/* current line length */
	int max = 0;		/* max length seen so far */
	char line[MAXLINE];	/* current input line */
	char longest[MAXLINE]; 	/* longest line saved here */
	
	while ((len = getLine(line, MAXLINE)) > 0)
	{
		if (len > max) {
			max = len;
			copy(line, longest);
		}
	}
	if (max > 0) {
		printf("\n: %s\n", longest);
	}
	
	return 0;
}

/* Reads text stream into line, returns length
 */
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

/* Copies source into dest */
void copy(const char source[], char dest[])
{
	int i;
	for(i = 0; (dest[i] = source[i]) != '\0'; ++i);
}
