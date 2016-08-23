#include <stdio.h>
#define SIZE 100
int main(void)
{
	int n, array[SIZE], getint(int *);

	/* Fill array with integers by calls to getint */
	for (n = 0 ; n < SIZE && getint(&array[n]) != EOF ; n++) {
	}

	int i= 0;
	for (i = 0 ; i < n ; ++i) {
		printf("%d) %d\n", i,  array[i]);
	}

	return 0;
}

#include <ctype.h>

#define DEBUG 1

int getch(void);
void ungetch(int);

/* Purpose: Performs free-format input conversion by breaking a stream of characters into integer values, one integer per call
 * Input: address of array to save integer value
 * Output: EOF for end of file, zero if next input is not a number, or a positive value if the input is a number
 * Invariant (if any): none */
int getint(int *ip)
{
	int c, d, sign;

	while (isspace(c = getch())) {
		// Skip over spaces.
	}

	if (DEBUG) { printf("\t ****DEBUG at getint()--> GOT %c FROM INPUT ****\n" ,c); }

	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		if (DEBUG) { printf("\t ****DEBUG at getint()--> PLACING %c IN BUFFER ****\n" , c); }
		ungetch(c); /* Save non-digit char to buffer stream */
		return 0;
	}

	sign = ( c == '-' ) ? -1 : 1;
	if (c == '+' || c == '-') {
		if (DEBUG) { printf("\t ****DEBUG at getint()--> GETTING NEXT CHAR AFTER +/- ****\n" ); }
		d = c;
		if (!isdigit(c = getch())) {
			if (c != EOF) {
				ungetch(c);
			}
			ungetch(d);
			return d;
		}	
	}

	if (DEBUG) { printf("\t ****DEBUG at getint()--> GOT %c FROM INPUT ****\n" , c); }
	for (*ip = 0 ; isdigit(c) ; c = getch()) {
		*ip = 10 * *ip + (c - '0'); /* Configure the integer */
		if (DEBUG) { printf("\t ****DEBUG at getint()--> GOT %c, VALUE = %d ****\n" , c, *ip); }
	}
	*ip *= sign;
	if (DEBUG) { printf("\t ****DEBUG at getint()--> FINAL VALUE = %d ****\n" , *ip); }
	if (c != EOF) {
		if (DEBUG) { printf("\t ****DEBUG at getint()--> PLACING %c IN BUFFER ****\n" , c); }
		ungetch(c);
	}
	if (DEBUG) { printf("\t ****DEBUG at getint()--> RETURNING %c ****\n" ,c); }
	return c;
}

/* <--- getch() and ungetch() for managing input stream --> */
#define BUFSIZE 100

int buf[BUFSIZE]; /* shared buffer array for input stream */
int bufp = 0; /* next free position in buffer */

/* Purpose: Get a char input. But if there is a char in buffer, it will return that instead.
 * Input: none
 * Output: returns char element in buffer. if no elements in buffer, gets char input
 * Invariant (if any): elements are put in buffer if and only if ungetch() is called.
 *                     Calling ungetch() n times will result in getch() returning buffer
 *                     elements the next n times */
int getch(void)
{
	int c;
	
	if (bufp > 0) {
		if (DEBUG) { printf("\t ****DEBUG at getch()--> RETURNING FROM BUFFER, %c ****\n" , buf[bufp-1]); }
		return buf[--bufp];
	} else {
		if (DEBUG) { printf("\t ****DEBUG at getch()--> GETTING CHARACTER FROM INPUT STREAM ****\n" ); }
		c = getchar();
		return c;
	}
//	return ( ( bufp > 0 ) ? buf[--bufp] : getchar() );
}

/* Purpose: Store char in buffer
 * Input: char. this must be the last ch received from getch() in order to cooperate w/ getch()
 * Output: none
 * Invariant (if any): see getch() description */
void ungetch(int c)
{
	if (bufp >= BUFSIZE) {
		printf("No more space in buffer\n");
	} else {
		buf[bufp++] = c;
	}
}


