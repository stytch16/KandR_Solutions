#define _GNU_SOURCE

#define DEBUG 1 /* Toggle debugging statements */
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "_dirent.h"

#define MAX_PATH 1024

void fsize(char *);
void dirwalk(char *, void(*fn)(char *));

int main(int argc, char *argv[])
{
	if (argc == 1) {
		fsize("."); /* default is the current directory */
	} else {
		while (--argc > 0) {
			if (DEBUG) { printf("\t **DEBUG @ main()--> GETTING SIZE OF %s **\n" , argv[1]); }
			fsize(*++argv);
		}
	}
	return 0;
}
/* fsize: print size of file but if file is a directory, recursively go thru all files in it */
void fsize(char *dirname)
{
	struct stat stbuf; /* contains inode variables */
	if (stat(dirname, &stbuf) == -1) { /* get inode variables for this file/ directory */
		fprintf(stderr, "fsize: can't access %s\n", dirname);
		return;
	}
	if (DEBUG) { printf("\t **DEBUG @ fsize--> GOT INODE VARIABLES **\n" ); }

	if ( (stbuf.st_mode & S_IFMT) == S_IFDIR) { /* st_mode -> mode bit field.  */
		if (DEBUG) { printf("\t **DEBUG @ fsize--> THIS IS A DIRECTORY **\n" ); }
		/* if type of file is a directory, recursively go thru all files in it */
		dirwalk(dirname, fsize);	
	}
	if (DEBUG) { printf("\t **DEBUG @ fsize--> THIS IS A FILE. PRINTING SIZE OF FILE. **\n" ); }
	printf("%20s......%-8ld\n", dirname, stbuf.st_size); /* print file size */
}

void dirwalk(char *dir, void(*fn)(char *))
{
	char name[MAX_PATH]; /* name of file inside dir */
	Dirent *dp; /* entry in dir */
	_Dir *dfd; /* pointer to dir */

	if ( (dfd = _opendir(dir)) == NULL) { /* open directory with name */
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	if (DEBUG) { printf("\t **DEBUG @ dirwalk--> TRAVERSING DIRECTORY ENTRIES **\n" ); }
	while ( (dp = _readdir(dfd)) != NULL) { /* read list of filenames in directory */
		if (DEBUG) { printf("\t **DEBUG @ dirwalk--> READ DIRECTORY ENTRY |%s| **\n" , dp->name); }
		if (strcmp( dp->name, ".") == 0 || strcmp( dp->name, "..") == 0) {
			continue; /* skip parent and current directory files that exist in every directory */
		}
		if (strlen(dir) + strlen( dp->name) + 2 > sizeof(name)) {
			/* +2 for '/' in between dirname and filename and for '/0' */
			fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->name);
		} else {
			sprintf(name, "%s/%s", dir, dp->name); /* store filename entry */
			if (DEBUG) { printf("\t **DEBUG @ dirwalk--> CALLING FSIZE(%s) **\n", name); }
			(*fn)(name);  /* recursive call back to fsize with filename entry!!! */
		}
	}
	if (DEBUG) { printf("\t **DEBUG @ dirwalk--> DONE WITH FILE ENTRIES IN |%s| **\n" , dir); }
	_closedir(dfd);
}


