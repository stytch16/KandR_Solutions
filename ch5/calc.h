#ifndef CALC_H
#define CALC_H

#define MAXOP 100 /* max size of operand or operator*/
#define NUMBER 'N' /* signal that a number was found */
#define FUNC 'F' /* signal that a function was found */
#define DEBUG 0 /* Toggle debugging statements */

void print_user_info(void); /* in userinfo.c */
void mathfunc(char []); /* in mathfunc.c */
int getop(char *s, const char *expr);
void push(double); /* in stack.c */
double pop(void);
double top(void);
void peek(void);
void duplicate(void);
void sswap(void);
void clear(void);
int getLine(char s[], int lim); /* in getLine.c */


#endif /* ifndef CALC_H */
