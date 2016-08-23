/* Program to print a histogram of each ASCII character
 * frequency in the text stream
 */

#include <stdio.h>

#define N_ASCII 255
int main(void)
{
	int length[N_ASCII];
	
	int i;
	for (i = 0; i < N_ASCII; ++i) {
		length[i] = 0;
	}

	int ch;
	while ( (ch = getchar()) != EOF) {
		++length[ch];
	}

	int j;
	for (i = 0; i < N_ASCII; ++i) {
		if (length[i]) {
			printf("\n%4c\t", i);
			for (j = 0; j < length[i]; ++j) {
				putchar('*');
			}
			printf("\tFreq: %d", length[i] );
		}
	}


	return 0;
}
