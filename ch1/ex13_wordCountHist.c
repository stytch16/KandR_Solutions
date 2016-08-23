/* Program to print a histogram of the length of words
 * in a text stream
 */

#include <stdio.h>

#define MAX 30
#define IN 1
#define OUT 0

int main(void)
{
	int length[MAX];
	
	// Reset count
	int i;
	for (i = 0; i < MAX; ++i)
		length[i] = 0;
	
	int ch;
	int state = OUT;
	int count = 0;

	while ((ch = getchar()) != EOF) {
		if (ch == ' ' \
			|| ch == '\t' \
			|| ch == '\n') {
			
			if (state){
				++length[count];
				count = 0;
			}
			state = OUT;
			
		}
		else if (!state){
			state = IN;
		}

		if (state){
			++count;
		}
	}

	// Print histogram
	int j;
	for (i = 0; i < MAX; ++i) {
		if (length[i]){
			printf("\n%d\t", i);
			for (j = 0; j < length[i]; ++j) {
				putchar('*');
			}
			printf("\tFreq: %d", length[i] );
		}
	}


	return 0;
}

