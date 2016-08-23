#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp, *ofp;
	char *prog = *argv;
	void filecopy( FILE *, FILE *);
	
	ofp = fopen("outtest.txt", "w");

	if (argc == 1) {
		filecopy(stdin, ofp);
	} else {
		while (--argc > 0) {
			if (!(fp = fopen(*++argv, "r"))) {
				fprintf(stderr, "%s: failed to open %s\n", prog, *argv);
				exit(1); /* signal failure */
			} else {
				filecopy(fp, ofp);
				fclose(fp);
			}
		}
	}
	if (ferror(ofp)) {
		fprintf(stderr, "%s: error writing stdout\n", prog);
		exit(2); /* signal failure */
	}
	exit(0);
}

void filecopy(FILE *ifp, FILE *ofp)
{
	int c;
	while ( ( c = getc(ifp) ) != EOF) {
		putc(c, ofp);
	}
}
