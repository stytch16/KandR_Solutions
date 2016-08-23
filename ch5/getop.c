#include <stdio.h>
#include <string.h> /* for strlen() */
#include "calc.h"

#define digit(x) (('0' <=  (x) && (x) <= '9') ? 1 : 0 )
#define whitesp(x) ( ( (x) == ' ' || (x) == '\t' ) ? 1 : 0 ) 

static int expr_index = 0;

/* Purpose: get next operator, numeric operand, function name, or single-letter variable name
 * Input: postfix expression
 * Output: ascii value if operator, signal for number, signal for function, or ascii value of variable name
 * Invariant (if any): 1) every single letter has a different ascii value.
 *			2) a negative sign is followed by a digit. Otherwise, it is a minus sign
 *			3) all single alphabetic character is a variable. */

int getop(char *s, const char *expr)
{
	expr += expr_index;
	const char *start = expr;

	char *s_start = s;

	int ch;
	*s = ch = *expr++;
	while (whitesp(ch)) {
		*s = ch = *expr++;
	}

	*(s+1) = '\0';
	if (!digit(ch) && ch != '.' && ch != '-') {
		expr_index += expr - start;
		if (DEBUG) { printf("\t ****DEBUG at getop--> %c IS OPERATOR ****\n" , ch); }
		return ch;
	} 

	if (ch == '-') {
		int ch1 = ch;
		ch = *expr++;
		if ( whitesp(ch) ) {
			--expr;
			expr_index += expr - start;
			if (DEBUG) { printf("\t ****DEBUG at getop--> %c is OPERATOR ****\n" , ch1); }
			return ch1;
		} else {
			*++s = ch;
		}	
	}

	if (digit(ch)) {
		*++s = ch = *expr++;
		while (digit(ch)) {
			*++s = ch = *expr++;
		}
	}
	
	if (ch == '.') {
		*++s = ch = *expr++;
		while (digit(ch)) {
			*++s = ch = *expr++;
		}
	}
	*s = '\0';
	--expr; /* Copied one too many */
	
	expr_index += expr - start;

	if (DEBUG) { printf("\t ****DEBUG at getop--> NUMBER = %s ****\n", s_start); }
	return NUMBER;
}
