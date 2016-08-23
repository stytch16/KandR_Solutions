#define _GNU_SOURCE

#define DEBUG 1 /* Toggle debugging statements */

#include "_dirent.h"
#include <sys/dir.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DIRSIZ 14

_Dir *_opendir(char *dirname)
{
	int fd;
	struct stat stbuf;
	_Dir *dp;

	if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 || (stbuf.st_mode & S_IFMT) != S_IFDIR || \
				(dp = (_Dir *)malloc(sizeof(_Dir))) == NULL) {
		return NULL; /* ensure opening, gathering of inode data, is a directory, and memory allocation */
	}
	dp->fd = fd;
	if (DEBUG) { printf("\t **DEBUG @ _opendir--> SUCCESS OPENING FILE ID = %d **\n" , dp->fd); }
	return dp;
}

void _closedir(_Dir *dfd)
{
	if (dfd) {
		close( dfd->fd);
		free(dfd);
	}
	if (DEBUG) { printf("\t **DEBUG @ _closedir--> CLOSED DIRECTORY **\n" ); }
}
Dirent *_readdir(_Dir *dfd)
{
	ssize_t nread;
	static struct direct* dirbuf; /* local directory structure defined in sys/dir.h */
	static Dirent d; /* return struct, static for portability outside fn scope */
	if (DEBUG) { printf("\t **DEBUG @ _readdir--> READING FILE %d **\n" , dfd->fd); }

	if (dirbuf == NULL) {
		if (DEBUG) { printf("\t **DEBUG @ _readdir--> ALLOCATING SPACE TO LOCAL DIRECTORY **\n" ); }
		dirbuf = (struct direct *)malloc(sizeof dirbuf);
	}
	/* ****** ERROR BELOW : READ (FD, pointer to direct, size) returns error */
	/* ****** read() CAN"T BE USED WHEN FILE DESCRIPTOR IS A DIRECTORY  */

	nread = read( dfd->fd, (void *)dirbuf, sizeof dirbuf) ;
	if (DEBUG) { printf("\t **DEBUG @ _readdir--> READ %ld BYTES VS. %lu SIZE**\n" , nread, sizeof *dirbuf); }
	while (nread == sizeof dirbuf) {
		/* read function will fill variables of struct direct dirbuf */
		/* subsequent calls will replace variables with the next entry */
		if (DEBUG) { printf("\t **DEBUG @ _readdir--> PUT DIRECT.D_INO = %ld **\n", dirbuf->d_ino); }
		if (dirbuf->d_ino == 0) {
			continue; /* slot not in use because file was removed -> skip */	
		}
		strncpy(d.name, dirbuf->d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0'; /* ensure termination of string */
		if (DEBUG) { printf("\t **DEBUG @ _readdir--> NAME OF DIRECTORY ENTRY = %s **\n" , d.name); }
		return &d;
	}
	free(dirbuf);
	return NULL; /* all files have been dealt with */
}
