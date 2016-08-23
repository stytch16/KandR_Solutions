#include "io_lines.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXSTOR 5000
#define MAXLINES 100
#define DEBUG 1 /* Toggle debugging statements */
enum order { LEXICOGRAPHIC, NUMERIC, FOLD, DICTLEX, DICTFOLD };

void readargs(int argc, char *argv[], int*, int *);
void quisort(void *v[], int left, int right, int (*comp)(const void*, const void *), int rev);
void swaplns(void *v[], int i, int j);
int num_cmp(const void *s, const void *t);
int lex_cmp(const void *s, const void *t);
int lex_cmp_fold(const void *s, const void *t);
int dict_cmp(const void *s, const void *t);
int dict_cmp_fold(const void *s, const void *t);

/* function pointer array */
int (*comp[])(const void *, const void*) = \
	{lex_cmp, num_cmp, lex_cmp_fold, dict_cmp, dict_cmp_fold};

char *lineptr[MAXLINES]; /* pointers to text lines */
int fn_toggle; /* comp function pointer array index */
int rev; /* 1 or -1, set -1 for decreasing order */
int dict; /* boolean for -d option */
int pos1, pos2; /* field-handling */

/* command  <-- default is lexicographic comparison
 * command -n <-- enables numeric comaparison
 * command -r <-- enables sorting in decreasing order 
 * command -d <-- enables dictionary ordering
 * command [+pos1] <-- from line of index = pos1 : pos1 is a positive int
 * command [-pos2] <-- to line of index = pos2 : pos2 is a position int */
int main(int argc, char *argv[])
{
	char buffer[MAXSTOR]; /* allocated storage space */
	int n_lines_read;

	/* Set defaults */
	fn_toggle = LEXICOGRAPHIC;
	rev = 1;
	dict = 0;
	pos1 = -1;
	pos2 = -1;

	/* Read arguments */
	readargs(argc, argv, &pos1, &pos2);

	/* Read lines, sort them, output in sorted order */
	if ( ( n_lines_read = readlines(lineptr, buffer, MAXLINES )) >= 0){
		/* Declaration of num_cmp & lex_cmp */
		/* int num_cmp(void *, void *) */
		/* typecast num_cmp or lex_cmp to a fn ptr with resp. args and return type */
		if ((pos1 == pos2 && pos1 == -1) || (pos2 < pos1)){
			pos1 = 0;
			pos2 = n_lines_read - 1;
		}
		quisort( ( void ** )lineptr, pos1, pos2, comp[fn_toggle] , rev);
		printf("\n");
		writelines(lineptr, pos1, pos2 + 1);
		return 0;
	} else {
		printf("input is too big to sort\n");
		return 1;
	}

	return 0;
}

void readargs(int argc, char *argv[], int *pos1, int *pos2)
{
	char flag;
	char option;
	while (--argc > 0 && ((option = **++argv) == '-' || **argv == '+')) {
		while ((flag = *(++( *argv )))) {
			if (isalpha(flag))
				switch (flag) {
					case 'n':
						fn_toggle = NUMERIC;
						break;
					case 'r':
						rev = -1; /* r flag set */
						break;
					case 'f':
						if (fn_toggle != NUMERIC) {
							if (fn_toggle == DICTLEX) {
								fn_toggle = DICTFOLD;
							} else {
								fn_toggle = FOLD;
							}
						}
						break;
					case 'd':
						if (fn_toggle != NUMERIC) {
							if (fn_toggle == FOLD) {
								fn_toggle = DICTFOLD;
							} else {
								fn_toggle = DICTLEX;
							}
						}
						break;
					default:
						printf("USAGE: unknown %c\n", flag);
						break;
				}
			else if (isdigit(flag) && option == '+') {
				*pos1 = atoi(*argv);
				break;
			}
			else if (isdigit(flag) && option == '-') {
				*pos2 = atoi(*argv);
				break;
			}
			else {
				printf("USAGE: -n -d -f -r options\n");
			}
		}
	}
}

void quisort(void *v[], int left, int right, int (*comp)(const void*, const void *), int rev)
{
	int i, last;
	void swaplns(void *v[], int, int);

	if (left >= right) {
		return;
	}
	swaplns(v, left, (left+right)/2);
	last = left;
	for (i = left+1 ; i <= right ; ++i) {
		if ((*comp)(v[i], v[left]) * rev < 0) {
			/* Multiply by rev = 1 or -1 to change comparison result */
			swaplns(v, ++last, i);
		}
	}
	swaplns(v, left, last);
	quisort(v, left, last-1, comp, rev);
	quisort(v, last+1, right, comp, rev);
}

void swaplns(void *v[], int i, int j)
{
	void *temp = v[i]; /* v[i] == *(v+i) */
	v[i] = v[j];
	v[j] = temp;
}

int num_cmp(const void *s, const void *t)
{
	double i = atof( ( char * )s);
	double j = atof( ( char * )t);
	if (i < j) {
		return -1;
	}
	else if (i > j) {
		return 1;
	}
	else {
		return 0;
	}
}

int lex_cmp(const void *s, const void *t)
{
	char* cp1 = (char*)s;
	char* cp2 = (char*)t;
	for ( ; *cp1 == *cp2 ; ++cp1, ++cp2) {
		if (cp1 == '\0'){
			return 0;
		}
	}
	return (*cp1 - *cp2);
}

int lex_cmp_fold(const void *s, const void *t) 
{
	char* cp1 = (char *)s;
	char* cp2 = (char *)t;

	for( ; tolower(*cp1) == tolower(*cp2) ; ++cp1, ++cp2) {
		if (*cp1 == '\0') {
			return 0;
		}
	}
	return (tolower(*cp1) - tolower(*cp2));
}

int dict_cmp(const void *s, const void *t)
{
	char* cp1 = (char *)s;
	char* cp2 = (char *)t;
	unsigned int inequality = 0;

	do {
		while ((!isalnum(*cp1) && !isspace(*cp1)) || (!isalnum(*cp2) && !isspace(*cp2))) {
			++cp1; ++cp2;
		}
		if (*cp1 == *cp2 && *cp1 == '\0')
			return 0;
		else if (*cp1 != *cp2)
			inequality = 1;
		else {
			++cp1; ++cp2;
		}
			
	} while (!inequality);

	return (*cp1 - *cp2);
}

int dict_cmp_fold(const void *s, const void *t)
{
	char* cp1 = (char *)s;
	char* cp2 = (char *)t;
	unsigned int inequality = 0;

	char c1 = tolower(*cp1), c2 = tolower(*cp2);
	do {
		while ((!isalnum(c1) && !isspace(c1)) || (!isalnum(c2) && !isspace(c2))) {
			c1 = tolower(*++cp1);
			c2 = tolower(*++cp2);	
		}
		if (c1 == c2 && c1 == '\0')
			return 0;
		else if (c1 != c2)
			inequality = 1;
		else {
			c1 = tolower(*++cp1);
			c2 = tolower(*++cp2);	
		}
			
	} while (!inequality);

	return (c1 - c2);
}


