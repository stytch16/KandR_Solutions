#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 0 /* Toggle debugging statements */

struct node {
	unsigned int n; /* number of occurences */
	char *w; /* array of words */
	struct node *left; /* left child */
	struct node *right; /* right child */
};

#define MAXWORDLEN 100
static unsigned int wordcount;
int getword(char *, unsigned int);
unsigned int isValid(char *);
struct node *addtree(struct node *, char *);

#define MAXWORDS 5000
#define MAXFRQ 100
/* freqbins is an array of groups.
 * each group has words which all have a common frequency
 * in freqbins, the index corresponds to the common frequency */
struct group {
	char *words[MAXWORDS]; /* string array */
} freqbins[MAXFRQ];

static unsigned int maxfrq; /* last index with words in freqbins */
void addtobins(struct node*);
void addword(char **ptr, char * w);
void printbins(unsigned int);

int main(void)
{
	struct node* root; /* root of binary tree */
	root = NULL;
	char word[MAXWORDLEN]; /* word buffer */
	while (getword(word, MAXWORDLEN) >= 0) {
		if (isValid(word)) {
			++wordcount;
			root = addtree(root, word);
		}
	}
	printf("COUNTED %u WORDS\n", wordcount);
	maxfrq = 0;
	addtobins(root);
	printbins(maxfrq);
	return 0;
}

int getword(char *w, unsigned int lim)
{
	char c;
	char *start; /* to point to start of word */
	start = w;

	while (isspace(*w = c = getchar())) {
		/* skip over spaces */
	}
	if (c == EOF) {
		*w = '\0';
		return -1;
	} else if (!isalpha(c) && !isdigit(c)) {
		*++w = '\0';
		return 0;
	} else {
		++w;
		while (lim-- > 0 && !isspace(*w = c = getchar()) && c != EOF ) {
			++w;
		}
		*w = '\0';
	}
	if (DEBUG) { printf("\t ****DEBUG at getword--> READ %s FROM INPUT OF LENGTH = %ld ****\n" ,start, w-start); }
	return (w - start);
}

unsigned int isValid(char *w)
{
	/* valid <=> first char in string is alphabetic char */
	if (DEBUG) { printf("\t ****DEBUG at isValid--> %s IS VALID WORD ****\n", w); }
	return ( isalpha(*w) || isdigit(*w) ) ? 1 : 0;
}

struct node *addtree(struct node * nPtr, char * w)
{
	int cond;
	if (nPtr) {
	}
	if (!nPtr) {
		nPtr = (struct node *)malloc(sizeof(struct node));
		nPtr->n = 1;
		nPtr->w = (char *)malloc(strlen(w) + 1);
		strcpy(nPtr->w, w);
		if (DEBUG) { printf("\t ****DEBUG at addtree--> ADD TO TREE %s ****\n" , nPtr->w); }
		nPtr->left = NULL;
		nPtr->right = NULL;
	} else if (!(cond = strcmp(w, nPtr->w))) {
		if (DEBUG) { printf("\t ****DEBUG at addtree--> FOUND IN TREE ****\n" ); }
		++nPtr->n;	
	} else if (cond < 0) {
		if (DEBUG) { printf("\t ****DEBUG at addtree--> GOING LEFT ****\n" ); }
		nPtr->left = addtree( nPtr->left, w);
	} else {
		if (DEBUG) { printf("\t ****DEBUG at addtree--> GOING RIGHT ****\n" ); }
		nPtr->right = addtree( nPtr->right, w);
	}
	return nPtr;
}

void addtobins(struct node * root) {
	if (root) {
		addtobins( root->left);
		maxfrq = (maxfrq < root->n) ? root->n : maxfrq;
		if (DEBUG) { printf("\t ****DEBUG at addtobins--> ADDING %s TO BIN #%u ****\n" , root->w, root->n - 1); }
		addword((freqbins[root->n - 1]).words, root->w);
		addtobins( root->right);
	}
}

void addword(char **ptr, char * w)
{
	while( *ptr ) {
		++ptr;
	}
	*ptr = (char *)malloc(strlen(w) + 1);
	strcpy(*ptr, w);
	if (DEBUG) { printf("\t ****DEBUG at addword--> BIN-ADDED %s ****\n" , *ptr); }
}
void printbins(unsigned int max)
{
	if (DEBUG) { printf("\t ****DEBUG at printbins--> GOT MAXFRQ = %u ****\n" , max); }
	char **ptr;
	while(max-- > 0) {
		ptr = freqbins[max].words;
		if (*ptr) 
			printf("WORD FREQ OF %u:\n", max+1);
		while (*ptr) {
			printf("... %s \n", *ptr);
			++ptr;
		}
	}
}
