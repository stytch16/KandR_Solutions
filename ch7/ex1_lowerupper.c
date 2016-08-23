#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("USAGE: upper or lower? \n");
		return 1;
	}

	int c;
	if (!strcmp(*++argv, "lower")) {
		while ( ( c = getchar() ) != EOF) {
			putchar(tolower(c));
		}
	} else {
		while ( ( c = getchar() ) != EOF) {
			putchar(toupper(c));
		}
	}

	
	return 0;
}

