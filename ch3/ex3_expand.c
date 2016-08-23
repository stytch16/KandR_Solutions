#include <stdio.h>
#define MAXLINE 1000
void expand(const char shorthand[], char expanded[]);
int main(void)
{
	int i;
	int c;
	char shorthand[MAXLINE];
	char expanded[MAXLINE];

	for (i = 0; (c = getchar()) != EOF; ++i) {
		shorthand[i] = c;
	}

	expand(shorthand, expanded);

	printf("%s\n", expanded);

	return 0;
}

void expand(const char shorthand[], char expanded[])
{
	int c;
	int i = 0, j = 0;
	int prev, next;
	// Return if string is empty
	if (shorthand[i] == '\0') {
		expanded[j] = '\0';
		return;
	}
	// Copy the first element.
	// Keep copying until a '-' is found.
	// If '-' is found,
	// 	Get element x before it and y after it.
	// 	Keep incrementing x and copying until x = y.
	// 	Then copy y.
	for (expanded[j++] = shorthand[i++]; shorthand[i] != '\0'; ++i) {
		if (shorthand[i] == '-') {

			for (prev = i-1, next = i+1, c = shorthand[prev];\
				       	c != shorthand[next];\
				       	++prev) {
				expanded[j++] = ++c;
			}
			++i; /* The element after - has already been dealt with */

		}
		else {
			expanded[j++] = shorthand[i];
		}
	}
	expanded[j] = '\0';
}
