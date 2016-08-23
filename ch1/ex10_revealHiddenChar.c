/* Program to reveal tab by \t, backspace by \b, 
 * newline by \n, and backslash by \\ text stream */

#include <stdio.h>

int main(void)
{
	int ch;
	while ((ch = getchar()) != EOF){
		if (ch == '\t'){
			putchar('\\');
			putchar('t');
		}
		else if (ch == '\b') {
			putchar('\\');
			putchar('b');
		}
		else if (ch == '\\') {
			putchar('\\');
			putchar('\\');
		}
		else if (ch == '\n') {
			putchar('\\');
			putchar('n');
		}
		else {
			putchar(ch);
		}
	}
	return 0;
}
