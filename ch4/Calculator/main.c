#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <string.h> /* for strcmp(), etc. */
#include <ctype.h>
#include <math.h> /* for fmod(), sin(), cos(), exp(), pow(), etc. */

#define MAXOP 100 /* max size of operand or operator*/
#define NABC 26 /* number of letters in alphabet */
#define NUMBER 'N' /* signal that a number was found */
#define FUNC 'F' /* signal that a function was found */
int getop(char []);

void mathfunc(char []);

void push(double);
double pop(void);
double top(void);
void peek(void);
void duplicate(void);
void swap(void);
void clear(void);

/* reverse Polish calculator */
int main(void)
{
	int type; /* type of variable from stack array */
	double op2; /* temporary variable for holding operand */
	char s[MAXOP]; /* operator & operand stack array */

	/* Create a list of single letter variables for each letter in alphabet */	
	/* Initialize each variable to 0.0 */
	double v_list[NABC + 1]; /* extra @ */
	int last_v;
	last_v = ' '; /* set it to a starting character for comparision later */

	int i;
	for (i = 0 ; i < NABC+1 ; ++i) {
		v_list[i] = 0.0;
	}

	printf("Reverse Polish Calculator\nSupports negativity & variables.\nVariable '@' holds the 'ans', the most recently computed value\n\n: \n");
	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case FUNC:
				mathfunc(s);
				
				/* <!-- Fri Aug  5 02:50:17 2016 -->
				 * <!-- TODO: How do you handle functions? 
				 *            Create a function which determines
				 *            the name. Then call the same function in math.h -->
				 */
				
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0) {
					push(pop() / op2);
				}
				else {
					printf("Error: dividing by 0\n");
				}
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0) {
					fmod(pop(), op2);
				} else {
					printf("Error: modulo by 0\n");
				}
			case '=': /* = should always be followed by operand and then a variable */
				printf("\t ****DEBUG at main()--> PUTTING %G INTO V_LIST AT POS = %d ****\n" , top(), last_v - '@');
				v_list[last_v - '@'] = top();
				printf("\t ****DEBUG at main()--> %c NOW EQUALS %g ****\n" , last_v, v_list[last_v - '@']);
				break;
			case '\n':
				/* print the top */
				printf("\t ****DEBUG at main()--> SAVING @ = %g ****\n" , top());
				v_list[0] = top(); /* Save the ans */
				printf(" = %.8g\n", pop());
				break;
			default:
				if ( ('@' <= type ) && ( type <= 'Z' ) ) {
					printf("\t ****DEBUG at main()--> %c IS A VAR ****\n", type);
					if (type == '@' || last_v == toupper(type) ){
						printf("\t ****DEBUG at main()--> %c HAS ALREADY BEEN ASSIGNED %g****\n" , type, v_list[toupper(type) - '@']);
						push(v_list[toupper(type) - '@']);
						printf("\t ****DEBUG at main()--> VALUE IS %g ****\n" , v_list[toupper(type) - '@']);
					} else {
						printf("\t ****DEBUG at main()--> %c IS NOW LAST VAR TO BE ASSIGNED ****\n" ,type);
						last_v = toupper(type);
					}
				} else {
					printf("Error: unknown command %s\n", s);
				}
				break;
				
		}
	}
	return 0;
}


void mathfunc(char s[])
{
	if (!strcmp(s, "sin")) {
		push(sin(pop()));
	}
	else if (!strcmp(s, "cos")) {
		push(cos(pop()));
	}
	else if (!strcmp(s, "exp")) {
		push(exp(pop()));	
	}
	else if (!strcmp(s, "pow")) {
		int op; /* temp variable */	
		op = pop();
		push(pow(pop(), op));	
	}
	else {
		printf("error: bad function name - %s\n", s);
	}
}

/* <--- Stack functions ---> */
#define MAXVAL 100

/* External variables */
int sp = 0; /* next free stack position, i.e. top */
double val[MAXVAL]; /* value stack */

/* Purpose: Push double value onto stack
 * Input: double value
 * Output: none
 * Invariant (if any):  */
void push(double f)
{
	if (sp < MAXVAL) {
		val[sp++] = f;
		printf("\t ****DEBUG at push()--> PUSHED %g TO STACK ****\n" , f);
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
		printf("\t ****DEBUG at pop()--> POPPED %g FROM STACK ****\n" , val[sp-1]);
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
void swap(void)
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
/* <--- getop function ---> */
#define digit(x) (('0' <=  (x) && (x) <= '9') ? 1 : 0 )
#define alpha(x) ( (( 'a' <= (x) && (x) <= 'z' ) || ( '@' <= (x) && (x) <= 'Z' )) ? 1 : 0 )
#define whitesp(x) ( ( (x) == ' ' || (x) == '\t' ) ? 1 : 0 ) 

int getch(void);
void ungetch(int);

/* Purpose: get next operator or numeric operand
 * Input: postfix expression
 * Output: ascii value if operator. Else, returns 0 for number.
 * Invariant (if any): every operand has a different ascii value */
int getop(char s[])
{
	int i, c, c1 ; /* pos in s, char variable, char variable */
	/* s[0] must be a whitespace */
	s[0] = c = getch();
	while ( whitesp(c)) {
		s[0] = c = getch();
		/* skip whitespace */
	}
	s[1] = '\0';
	if (!(digit(c)) && !(alpha(c)) && c != '-' && c != '.') {
		printf("\t ****DEBUG at getop()--> RETURNING OPERATOR %c ****\n" , c);
		return c;  /* ascii value of operator returned */
	}
	
	i = 0;	
	if (alpha(c)) { /* get the function or variable name */
		c1 = c; /* for variables, return the ascii value of letter */
		c = getch();
		while (alpha(c) || digit(c)) {
			s[++i] = c;
			c = getch();
		}

		ungetch(c);	
		s[++i] = '\0';
		printf("\t ****DEBUG at getop()--> EVAL ALPHA CHAR RESULTED IN %s ****\n" ,s);
		if (strlen(s) > 1) {
			printf("\t ****DEBUG at getop()--> RETURNING FUNC ****\n" );
			return FUNC;
		} else {
			printf("\t ****DEBUG at getop()--> RETURNING A CHAR VARIABLE ****\n" );
			return c1; /* variable names are only 1 char */
		}

	/* Wait! '-' can be an operator or the negative sign of an operand.
	 * In postfix, a '-' before a space must be a minus operator.
	 * If it precedes a digit, it is a negative sign.
	 */

	}
	if (c == '-') {
		c1 = c;
		c = getch();
		ungetch(c);
		if (whitesp(c) || c == '\n' || c == EOF) {
			return c1; /* return the minus operator */
		} else {
			c = getch(); /* the negative sign is at the first pos of s */
					/* get the next char in expression */
			s[++i] = c; /* put the first digit in s */
		}
	}

	if (digit(c)) {
		s[++i] = c = getch();
		while (digit(c)) {
			s[++i] = c = getch();
			/* get the integer until non-digit or '.' and store in s including
			 * non-digit or '.'*/
		}
	}
	if (c == '.') {
		s[++i] = c = getch();
		while (digit(c)) {
			s[++i] = c = getch();
			/* get the fraction portion and store in s */
		}
	}

	/* Wait! We copied one too many to s, the final non-digit. */
	s[i] = '\0';
	if (c != EOF) {
		ungetch(c);
	}
	return NUMBER;
}

/* <--- getch() and ungetch() for managing input stream --> */
#define BUFSIZE 100

char buf[BUFSIZE]; /* shared buffer array for input stream */
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
		return buf[--bufp];
	} else {
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
	} else {
		buf[bufp++] = c;
	}
}


























