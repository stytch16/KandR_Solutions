#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define DEBUG 1 /* Toggle debugging statements */

/* getch() & ungetch() */
#define BUFSIZE 100
static char buf[BUFSIZE]; /* shared buffer array for input stream */
static int bufp = 0; /* next free position in buffer */

/* Allocating storage for input */
#define MAXWORD 100

/* keytab is array of struct key */
struct key {
	char *word; /* C keywords */
	int count; /* number of instances of word */
} keytab[] = {
	{"#define", 0},
	{"#include", 0},
	{"/", 0},
	{"auto", 0},
	{"break", 0},
	{"case", 0},
	{"char", 0},
	{"const", 0},
	{"continue", 0},
	{"default", 0},
	{"for", 0},
	{"unsigned", 0},
	{"void", 0},
	{"volatile", 0},
	{"while", 0}
};

#define NKEYS (sizeof(keytab) / sizeof(keytab[0]) ) /* unsigned long type */

int getword(char *, int);
struct key *binsearch(char *, struct key *, int);
int comment(void);
int getch(void);
void ungetch(int c);

/* Count C keywords */
int main(void)
{
	int c;
	char word[MAXWORD]; /* buffer */
	struct key *p;

	while (getword(word, MAXWORD) != EOF) {
		c = word[0];
		if (isalpha(c) || c == '#' || c == '_' || c == '\'' || c == '"' || c == '/') {
			/* Search for 'word' in struct array keytab and return index if found */
			if ( ( p = binsearch(word, keytab, (int)NKEYS ) ) != NULL) {
				p->count++;	
			}
		}
	}
	for (p = keytab; p < keytab + NKEYS; ++p) {
		if ( p->count > 0)
			printf("%4d %s\n", p->count, p->word );
	}
	return 0;
}

/* Get next word from input */
int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while (isspace(c = getch())) {
		// Skip over spaces
	}

	if (c != EOF) {
		*w++ = c;
	}
	if (isalpha(c) || c == '_' || c == '#') {
		for ( ; --lim > 0 ; ++w) {
			if (!isalnum(*w = getch())) {
				ungetch(*w); /* put back into input stream the unwanted char */
				break;
			} else {
			}
		}

	} else if (c == '\'' || c == '"') {
		for ( ; --lim > 0 ; ++w) {
			if( (*w = getch() ) == c || *w == EOF) {
				++w;
				break;
			}
		}	
	} else if (c == '/' && ( c = getch() ) == '*') {
		if (!comment()) {
			--w;
		} else {
		}
	} else {
		*w = '\0';
		return c;
	}

	*w = '\0';
	return word[0]; /* return the first char of string representing word */
}

int comment()
{
	int c;
	while ( ( c = getch() ) != '*' && c != EOF) {
		/* ignore all characters until a '*' or a EOF */
	}
	return ( c == '*' && (c = getch()) == '/' ) ? 1 : 0;
}

struct key *binsearch(char *word, struct key *tab, int n)
{
	int cond;

	struct key *low = &tab[0];
	struct key *high = &tab[n-1];
	struct key *mid;

	while (low <= high) {
		mid = low + (high - low)/2; /* = (low + high)/2 but addition between ptrs is illegal */
		if ( ( cond = strcmp(word, mid->word) ) < 0) {
			high = mid - 1;
		} else if (cond > 0) {
			low = mid + 1;
		} else {
			return mid;
		}
	}
	return NULL; /* word not found in tab */
}



/* Purpose: Get a char input. But if there is a char in buffer, it will return that instead.
 * Input: none
 * Output: returns char element in buffer. if no elements in buffer, gets char input
 * Invariant (if any): elements are put in buffer if and only if ungetch() is called.
 *                     Calling ungetch() n times will result in getch() returning buffer
 *                     elements the next n times */
int getch(void)
{
	return (( bufp > 0 ) ? buf[--bufp] : getchar());
}

/* Purpose: Store char in buffer
 * Input: char. this must be the last ch received from getch() in order to cooperate w/ getch()
 * Output: none
 * Invariant (if any): see getch() description */
void ungetch(int c)
{
	if (bufp >= BUFSIZE) {
	} else {
		buf[bufp++] = c;
	}
}
