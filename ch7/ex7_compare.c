#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum flag { NO, YES};
enum signalerro { NORMAL, FAILOPEN, FAILARGS, FAILWRITE };

int main( int argc, char *argv[])
{
	FILE *fp1, *fp2;
	char *prog = *argv;
	int compare( FILE *, FILE *, FILE *);
	
	if (argc < 3) {
		fprintf(stderr, "%s: usage requires two filenames as arguments\n", prog);
		exit(FAILARGS);
	} else {
		/* open first read file */
		fp1 = fopen(*++argv, "r");
		if (!fp1) {
			fprintf(stderr, "%s: failed to open %s\n", prog, *argv);
			exit(FAILOPEN); /* signal failure */
		}

		/* open second read file */
		fp2 = fopen(*++argv, "r");
		if (!fp2) {
			fprintf(stderr, "%s: failed to open %s\n", prog, *argv);
			exit(FAILOPEN); /* signal failure */
		}

		compare(fp1, fp2, stdout);
		fclose(fp1);
		fclose(fp2);
	}
	if (ferror(stdout)) {
		fprintf(stderr, "%s: error writing out\n", prog);
		exit(FAILWRITE); /* signal failure */
	}
	exit(0);
}

#define MAX 128
int compare( FILE *file1, FILE *file2, FILE *out)
{
	int line_num;
	char line1[MAX], line2[MAX];
	char *p, *q;
	line_num = 0;
	p = fgets(line1, MAX, file1);
	q = fgets(line2, MAX, file2);
       	while (p && q) {
		++line_num;
		if (strcmp(p, q)) {
			fprintf(out, "Line %d \nFile 1: %sFile 2:%s\n", line_num, p, q);
			return line_num;
		}
		p = fgets(line1, MAX, file1);
		q = fgets(line2, MAX, file2);
	}	
	if (!p && !q) {
		fprintf(out, "Read %d lines. Identical files\n", line_num);
	}
	else if (p && !q) {
		fprintf(out, "File 1 exceeds file 2 at line number %d\n", line_num);
	}
	else {
		fprintf(out, "File2 exceeds file 1 at line number %d\n", line_num);
	}
	return line_num;
}
