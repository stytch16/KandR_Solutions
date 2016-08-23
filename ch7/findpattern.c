#define DEBUG 0 /* Toggle debugging statements */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXFILES 100
#define MAXLINE 1000

enum flag { NOTFOUND, FOUND };
unsigned searchpattern(char *pattern, FILE *);
unsigned find(char *pattern, char *line);

int main(int argc, char *argv[])
{
	/* Get a set of files from argv */
	/* Ask user for pattern to look for */
	/* Search files and print those files that contain the pattern */
	char *prog = *argv;
	char *pattern;
	size_t patternsize;
	int patternlen;
	FILE *fp;
		
	if (argc == 1) {
		fprintf(stderr, "%s: usage requires file arguments\n", prog);
		exit(1);
	} else {
		fprintf(stdout, "Enter search: \n");

		patternsize = 128;
		pattern = (char *)malloc(patternsize + 1);
		patternlen = getline(&pattern, &patternsize, stdin);
		pattern[patternlen - 1] = '\0'; /* remove newline char */

		if (DEBUG) { printf("\t **DEBUG @ main()--> LOOKING FOR '%s' IN FILES **\n" ,pattern); }

		while (--argc > 0) {
			if (!(fp = fopen(*++argv, "r"))) {
				fprintf(stderr, "%s: failed to open %s\n", prog, *argv);
			} else {
				if (searchpattern(pattern, fp)) 
					fprintf(stdout, "%s\n", *argv);
				fclose(fp);
			}
		}
	}
	free((void *)pattern);
	if (ferror(stdout)) {
		fprintf(stderr, "%s: error writing out\n", prog);
		exit(2); /* signal failure */
	}
	exit(0);
}

unsigned searchpattern(char *pattern, FILE *fp)
{
	char line[MAXLINE];
	while (fgets(line, MAXLINE, fp)) {
		if (DEBUG) { printf("\t **DEBUG @ searchpattern--> EXTRACTING LINE = %s **\n" ,line); }
		if (find(pattern, line)) {
			return FOUND;
		}
	}
	return NOTFOUND;
}

unsigned find(char *pattern, char *line)
{
	char *resetline;
	char *resetpattern;

	resetpattern = pattern;
	while(*line)  {
		if (*line != *pattern) {
			++line;
		} else {
			resetline = line;
			while (*line == *pattern) {
				if (!pattern[1]) {
					return FOUND;
				}
				++line; ++pattern;
			}
			line = ++resetline; /* reset to next unprocessed ch in line */
			pattern = resetpattern;
		}
	}
	return NOTFOUND;

}
