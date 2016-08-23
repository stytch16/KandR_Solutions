#include <stdio.h>
#include "calc.h"

#define MAXVAL 100

static int sp = 0; /* next free stack position, i.e. top */
static double val[MAXVAL]; /* value stack */

/* Purpose: Push double value onto stack
 * Input: double value
 * Output: none
 * Invariant (if any):  */
void push(double f)
{
	if (sp < MAXVAL) {
		val[sp++] = f;
		if (DEBUG) { printf("\t ****DEBUG at stack()--> Pushed %g ****\n" , val[sp-1]); }
	} else {
		printf("error: stack is full. can't push %g\n", f);
	}
}

/* Purpose: Pop double value from stack
 * Input: none
 * Output: double value
 * Invariant (if any): none */
double pop(void)
{
	if (sp > 0) {
		if (DEBUG) { printf("\t ****DEBUG at stack()--> Popped %g ****\n", val[sp-1]); }
		return val[--sp];
	} else {
		printf("error: stack is empty\n");
		return 0.0;
	}
}

/* Purpose: Return copy of top element in stack
 * Input: none
 * Output: double value of copy
 * Invariant (if any): none */
double top(void)
{
	if (sp > 0) {
		return val[sp-1];
	} else {
		printf("error: stack is empty\n");
		return 0.0;
	}
}

/* Purpose: Print the top element in stack
 * Input: none
 * Output: none
 * Invariant (if any): none */
void peek(void)
{
	if (sp > 0) {
		printf("%g\n", val[sp]);
	} else {
		printf("error: stack is empty\n");
	}
}

/* Purpose: Duplicate top element of stack
 * Input: none
 * Output: none
 * Invariant (if any): none */
void duplicate(void)
{
	if (sp >= 0) {
		val[sp + 1] = val[sp];
		++sp;
	} else {
		printf("duplicate() error: stack is empty\n");
	}
}
/* Purpose: Swap top element and element before top
 * Input: none
 * Output: none
 * Invariant (if any): none */
void sswap(void)
{
	if (sp < 1) {
		printf("swap() error: >2 elements in stack\n");
		return;
	}
	double temp = val[sp];
	val[sp] = val[sp - 1];
	val[sp - 1] = temp;
}

/* Purpose: Clear the stack
 * Input: none
 * Output: none
 * Invariant (if any): Losing the index => losing the elements */
void clear(void)
{
	sp = -1;
}
