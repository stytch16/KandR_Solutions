#include <stdio.h>
#include "line.h" /* for get_line(), str_copy(), str_cmp(), etc. */
#include "io_lines.h" /* for readlines() and writelines() */
#include "sort.h" /* for qsort() */

#define MAXLINES 5000
#define MAXSTORAGE 5000

char* lineptr[MAXLINES]; /* array of pointers that each point to a line */

int main(void)
{
	int nLines;
	char storage[MAXSTORAGE];
	/* Read all lines of input */
	if ((nLines = readlines(lineptr, storage, MAXLINES)) >= 0) {
		/* Sort them */
		qsort(lineptr, 0, nLines - 1);
		/* Print them in order */
		writelines(lineptr, nLines);
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
	return 0;
}

