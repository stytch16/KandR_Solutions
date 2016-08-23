#include "line.h"
#include <stdio.h>
#include <ctype.h>
#define DEFAULT_N 10
#define MAXLINE 100
#define MAXLEN 1000
#define DEBUG 1 /* Toggle debugging statements */

int main(int argc, char *argv[])
{
	int n; /* Number of lines at end of input */
	n = 0;

	/* Get -n value if it exists */
	if (argc > 1 && **++argv == '-') {
		while (*(++(*argv)) != '\0') {
			if (isdigit(**argv))
				n = 10 * n + (**argv - '0');
			else {
				printf("Usage: tail -n : n is a valid positive integer\nTerminating program\n");
				return 1;
			}
		}
	} else {
		n = DEFAULT_N;
	}
	
	char *lines[MAXLINE]; /* pointers to each line input */
	char *p; /* pointer to line */
	char line[MAXLEN]; /* holds all line inputs */

	p = line;

	int i; /* number of lines */
	int len; /* length of each line input */
	for (i = 0 ; (len = get_line(p, MAXLEN)) > 0 ; ++i ) {
		/* Keep getting input until EOF */
		lines[i] = p;
		p += len + 1; /* Move p to next available space */
	}

	int n_lines = i;
	i -= n;
	i = ( i < 0 ) ? 0 : i;

	for ( ; i < n_lines; ++i) {
		printf("|%s|\n", lines[i]);
	}

	return 0;
}
