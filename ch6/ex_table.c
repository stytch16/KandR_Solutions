#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define DEBUG 0 /* Toggle debugging statements */

struct nlist {
	struct nlist *next; /* next entry in chain, representing linked list */
	char *name; /* defined name */
	char *defn; /* replacement text */
} ;

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */
/* each pointer essentially points to a linked list */

#define MAXINPUT 1000
#define MAXNAME 200
#define MAXTEXT 700
int get_line(char *s, unsigned int lim);
unsigned hashify(const char *s, char *name, char *text);
unsigned parsedef(const char* s, char* name, char* text);

unsigned hash(char *s);
struct nlist *lookup(char *s);
char *strdup(const char *s);
struct nlist *install(char *name, char *defn);
void clear(char *s);
int undef(char *name);

int main(void)
{
	char s[MAXINPUT]; /* input stream */
	char name[MAXNAME];
	char text[MAXTEXT];
	while (get_line(s, MAXINPUT) > 0) {
		if (hashify(s, name, text)) {
			printf("+ %s\n", s);
		}
	}
	printf("****************************\n");
	struct nlist *np; /* pointer to struct list */
	while( get_line(s, MAXINPUT) > 0) {
		np = lookup(s);
		if (np) {
			printf(">>> %s replaced by %s\n", s, np->defn);
		} else {
			printf(">>> %s not in define table\n", s);
		}
	}
	return 0;
}


int get_line(char *s, unsigned int lim) {
	char *t;
	t = s;

	while ( (lim-- > 0) && (( *s = getchar() ) != '\n') && (*s != EOF)) {
		++s;
	}
	*s = '\0';
	return (s - t);
}

unsigned hashify(const char *s, char *name, char *text)
{
	const char def[] = "#define";
	int i;
	for (i = 0 ; def[i] != '\0' ; ++i) {
		if (*s++ != def[i]) {
			return 0;
		}
	}
	if (parsedef(s, name, text)) {
		if (DEBUG) { printf("\t ****DEBUG at hashify--> NAME = %s, TEXT = %s, INSTALLING... ****\n" , name, text); }
		install(name, text);
	} else {
		if (DEBUG) { printf("\t ****DEBUG at hashify--> NOT A DEFINE PREPROCESS ****\n"); }
		return 0;
	}
	return 1;
}

unsigned parsedef(const char* s, char* name, char* text)
{
	if (!isblank(*s)) 
		return 0; /* #define must be followed by blank*/
	while(isblank(*s)) 
		++s;
	if (!s) 
		return 0; /* no name follows after #define */
	while (*s && !isblank(*s)) {
		*name = *s;
		++s; ++name;
	}
	*name = '\0';

	if (!isblank(*s))
		return 0; /* name must be followed by blank*/
	while(isblank(*s))
		++s;
	if (!s) 
		return 0; /* no replacement text follows name */
	while ( *s ) {
		*text = *s;
		++s; ++text;
	}
	*text = '\0';
	return 1;
}


/* Purpose: form a hash value for the string s, essentially creating a positive integer
 *          for string s for indexing into pointer table. 
 * Input: string
 * Output: remainder modulo size of pointer table
 * Invariant (if any):  Adds each character value of string s to a scrambled 
 *                      combination of the previous ones */
unsigned hash(char *s)
{
	unsigned hashval;
	for (hashval = 0 ; *s != '\0' ; ++s) {
		hashval = *s + 31 * hashval;
	}
	return hashval % HASHSIZE;
}

/* Purpose: Look for string s in hashtab
 * Input: string
 * Output: pointer to found string, NULL otherwise
 * Invariant (if any): if s exists in hashtab, it will be in linked list with index
 *                     hash(s) */
struct nlist *lookup(char *s)
{
	struct nlist *np;
	/* traverse linked list */
	for (np = hashtab[hash(s)] ; np != NULL ; np = np->next) {
		if (strcmp(s, np->name) == 0) {
			return np;
		}
	}
	return NULL;
}

char *strdup(const char *s)
{
	char *pt;
	pt = (char *)malloc(strlen(s) + 1);
	if (!pt) {
		return NULL;
	};
	strcpy(pt, s);
	return pt;
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np; /* pointer to struct nlist */
	unsigned hashval; /* index */

	if ( ( np = lookup(name))  == NULL) {
		/* name not in hash table, put in linked list */
		np = ( struct nlist * )malloc ( sizeof ( *np ) );
		if (np == NULL || ( np->name = strdup(name) ) == NULL) {
			return NULL; /* no more memory left */
		}
		/* insert into a single linked list */
		hashval = hash(name); /* get hash value */
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else {
		free( ( void * ) np->defn); /* replace the replacement text */
	}
	if ( !( np->defn = strdup(defn) )) {
		return NULL; /* no more memory left */
	}
	return np;
}

void clear(char *s)
{
	while (*s != '\0') {
		*s++ = '\0';
	}
}

int undef(char *name)
{
	/* Look up name in hashtab */
	/* if it exists, erase and free name and definition, then free node */
	/* return boolean 1 for successful erase, 0 for unsuccessful erase */
	struct nlist *np; /* pointer to struct nlist */
	if ( (np = lookup(name))){
		clear( np->name);
		clear( np->defn);
		free( ( void * ) np->name);
		free( ( void * ) np->defn);
	} else {
		return 0;
	}
	return 1;
}
