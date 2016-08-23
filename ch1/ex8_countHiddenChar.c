#include <stdio.h>

int main(void)
{
	int ch;
	int c;

	for (c = 0; ( ch = getchar() ) != EOF; ) {
		if (ch == ' ' || ch == '\t' || ch == '\n')
			++c;
	}
	printf("Counted %d\n", c);
	return 0;
}
