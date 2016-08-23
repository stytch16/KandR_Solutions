#include "io_lines.h"
#include "line.h"
#include <stdio.h>
#define MAXLEN 1000 /* max length of each line */
#define MAXSTOR 5000 /* max storage available */
#define DEBUG 1 /* Toggle debugging statements */

int readlines(char* lineptr[], char *linestorage, int maxlines)
{
	int len, nlines;
	char *p = linestorage; /* start of storage line */ 
	char *q = linestorage + MAXSTOR; /* end of storage line */
	char line[MAXLEN]; /* for storing lines */

	nlines = 0;
	while ((len = get_line(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || ( p + len ) > q  ) {
			return -1;
		}
		else {
			line[len - 1] = '\0'; /* Remove '\n' */
			str_copy(p, line);
			lineptr[nlines++] = p;
			p += len;
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int pos1, int pos2)
{
	int i = 0;
	for (i = pos1 ; i < pos2 ; ++i) {
		printf("%s\n", lineptr[i]);
	}
}
