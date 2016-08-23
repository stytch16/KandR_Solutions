/* Program to evaluate postfix expression from the command line */
#include <stdio.h>
#include "calc.h"
#include "line.h"

#define MAX 100
#define NUMBER 'N'

void get_args(char expr[], char *argv[]);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: Must enter postfix expression\n");
	} else {
		char expr[MAX];
		get_args(expr, argv);

		int type;
		int op2;
		char s[MAX];

		while ((type = getop(s, expr)) != '\0') {
			
			switch (type) {
				case NUMBER:
					push(atof(s));
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
						push(pop()/op2);
					} else {
						printf("error: divide by 0\n");
					}
					break;
				case '\n':
					printf(" = %.8f\n", pop());
					break;
				default:
					printf("error: unknown command");
					break;
			}
		}
	}
	return 0;
}

void get_args(char expr[], char *argv[])
{
	int i;
	char *pexpr;
	
	i = 0;	
	while( (pexpr = *++argv) != NULL) {
		while (*pexpr != '\0') {
			expr[i++] = *pexpr++;
		}
		expr[i++] = ' ';
	}
	expr[i++] = '\n';
	expr[i] = '\0';
}
