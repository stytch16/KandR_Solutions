/* Binary tree implementation in C */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 1 /* Toggle debugging statements */

#define MAXWORDFREQ 5000
#define MAXLINES 2000
struct tnode {
	char *word[MAXWORDFREQ]; /* string array*/
	int line_numbers[MAXLINES]; /* line numbers */
	int count; /* number of occurences */
	struct tnode *left; /* left child */
	struct tnode *right; /* right child */
} ;

#define MAXWORD 100
static int line_number;
struct tnode *addtree(struct tnode *, char *, unsigned int);
struct tnode *talloc(void);
char *str_dup(char *);
void treeprint(struct tnode *);
void printstrs(char *[]);
int getword(char *, int);
int strstrcmp(char *, char *, unsigned int );
char *get_sigfigs(char *, unsigned int);
char *addword(char *, char *[]);
void add_line_number(int *);
void print_linenumbers(int *s);

/* getch() & ungetch() */
#define BUFSIZE 100
static char buf[BUFSIZE]; /* shared buffer array for input stream */
static int bufp = 0; /* next free position in buffer */
int getch(void);
void ungetch(int c);

int main( int argc, char *argv[])
{
	unsigned int nsigfigs; /* first nsigfigs chars to be compared between words */
	if (argc == 1)
		nsigfigs = 6; /* by default */
	else if (argc == 2) {
		if (isdigit(**++argv)){
			nsigfigs = atoi(*argv);
		}
	}
	else {
		printf("USAGE: ex_tree [n] where n is a positive integer\n");
		return 1;
	}
	struct tnode *root; /* root node */
	char word[MAXWORD];

	root = NULL;
	line_number = 0;
	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) {
			root = addtree(root, word, nsigfigs); /* root remains the root node of tree */
		}
	}
	treeprint(root);
	return 0;
}

struct tnode *addtree(struct tnode *pt, char *w, unsigned int n)
{
	int cond;
	if (pt == NULL) {
		if (DEBUG) { printf("\t ****DEBUG at addtree--> ADDING TO TREE ****\n"); }
		pt = talloc(); /* make a new node */
		*pt->word = get_sigfigs(w, n);
		pt->word[1] = str_dup(w);
		pt->count = 1;
		pt->left = pt->right = NULL;
		add_line_number( pt->line_numbers);
	} else if ( ( cond = strstrcmp(w, *pt->word, n))== 0) {
		if (DEBUG) { printf("\t ****DEBUG at addtree--> FOUND EXISTING ****\n" ); }
		pt->count++;
		addword( w, pt->word);
		add_line_number( pt->line_numbers);
	} else if (cond < 0) {
		if (DEBUG) { printf("\t ****DEBUG at addtree--> LEFT ****\n" ); }
		/* percolate down to left subtree */
		pt->left = addtree( pt->left, w, n);
	} else {
		if (DEBUG) { printf("\t ****DEBUG at addtree--> RIGHT ****\n" ); }
		/* percolate down to right subtree */
		pt->right = addtree( pt->right, w, n);
	}
	return pt; /* recursion will return the root node of tree */
}

int strstrcmp(char *w, char *s, unsigned int n)
{
	if (DEBUG) { printf("\t ****DEBUG at strstrcmp--> COMPARING %s & %s ****\n", w, s); }
	while (n-- > 0){
		if (*w != *s)
			return (*w - *s);
		else {
			w++;
			s++;
		}
	}
	return 0;
}

char *addword(char* w, char *pt[])
{
	while (*++pt) {
		if (strcmp(*pt, w) == 0) {
			/* return pointer if word already exists in string array */
			return *pt;
		}
		++pt;
	}
	*pt = str_dup(w);
	return *pt;
}

char *get_sigfigs(char *w, unsigned int n)
{
	char *pt;
	int allocsize = (strlen(w) > n) ? ( n+1 ): ( strlen(w)+1 ); 
	pt = ( char* )malloc ( allocsize );
	strncpy(pt, w, allocsize-1);
	return pt;
}

void add_line_number(int *pt)
{
	if (DEBUG) { printf("\t ****DEBUG at add_line_number--> ADDING LINE NUMBER %d ****\n" , line_number); }
	while (*pt) {
		++pt;
	}
	*pt = line_number++;
}


struct tnode *talloc(void)
{
	/* malloc returns a void pointer to buffer */
	return (struct tnode *)malloc(sizeof(struct tnode));
}

char *str_dup(char *s)
{
	char *pt;
	pt = (char *)malloc( strlen(s) + 1);
	if (pt) { /* space was allocated */
		strcpy(pt, s);
	}
	return pt;
}
/* prints tree in sorted order by printing left, then parent, then right node */
void treeprint(struct tnode *pt)
{
	if (pt) {
		treeprint( pt->left);
		printf("%4d  ", pt->count);
		printstrs( pt->word);
		print_linenumbers( pt->line_numbers);
		printf("\n");
		treeprint( pt->right);
	}
}

void printstrs(char *s[])
{
	/* the first elements of each string array were not included in tree*/
	while (*++s) {
		printf("|%s", *s++);
	}
}

void print_linenumbers(int *s)
{
	printf(" - %d ", *s++ + 1); /* first may be 0, so print that first */
	while (*s){
		printf(" - %d ",  *s+1);
		++s;
	}
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
	if (isalpha(c)) {
		for ( ; --lim > 0 ; ++w) {
			if (!isalnum(*w = getch())) {
				ungetch(*w); /* put back into input stream the unwanted char */
				break;
			} 
		}
	} else {
		*w = '\0';
		return c;
	}
	*w = '\0';
	return word[0]; /* return the first char of string representing word */
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
