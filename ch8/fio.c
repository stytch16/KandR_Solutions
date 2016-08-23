#define DEBUG 1 /* Toggle debugging statements */
#include "fio.h"
#include <fcntl.h> /* open */
#include <unistd.h> /* read, write */
#include <stdlib.h> /* malloc */
#include <stdio.h>

/* initialize data for stdin, stdout, stderr */
_FILE _iob[OPEN_MAX] = {
	{0, (char *)0, (char *)0, 0, {1, 0, 0, 0, 0}}, /* stdin is to be read */
	{0, (char *)0, (char *)0, 1, {0, 1, 0, 0, 0}}, /* stdout is to be written */
	{0, (char *)0, (char *)0, 2, {0, 1, 1, 0, 0}} /* stderr is to be written unbuffered */
};

/* check to see that file is open for reading, check space for file data, read file data into buffer and get count, return first
 * character in buffer */
int _fillbuf( _FILE *fptr)
{
	int bufsize;
	if ( fptr->flags.READMODE == 0 || fptr->flags.EOFMODE == 1 ||  fptr->flags.ERRORMODE == 1) {
		return EOF; /* file must be open for reading and no EOF or error flags*/
	}
	if (DEBUG) { printf("\t **DEBUG @ fillbuf--> CHECKED READMOD & NO EOF/ERROR-MODE **\n" ); }
	bufsize = ( fptr->flags.UNBUFMODE == 1) ? (1) : (BUFSIZE);
	if (DEBUG) { printf("\t **DEBUG @ fillbuf--> BUFSIZE SET TO %d **\n" , bufsize); }
	if ( fptr->base == NULL) {
		if (DEBUG) { printf("\t **DEBUG @ fillbuf--> ALLOCATING SPACE FOR BUFFER **\n" ); }
		if (( fptr->base = (char *)malloc(bufsize)) == _NULL){ 
			/* subsequent calls will see that a buffer has already been allocated */
			return EOF;
		}
	}
	fptr->ptr = fptr->base;
	fptr->cnt = read( fptr->fd, fptr->ptr, bufsize);
	if (DEBUG) { printf("\t **DEBUG @ fillbuf--> READ %d BYTES FROM FILE %d **\n", fptr->cnt, fptr->fd); }

	if ( --fptr->cnt < 0) {
		if (fptr->cnt == -1) { /* once EOF is read, the flag is set. The file is finished with. */
			if (DEBUG) { printf("\t **DEBUG @ fillbuf--> FILE IS EMPTY **\n"); }
			fptr->flags.EOFMODE = 1;
		} else {
			if (DEBUG) { printf("\t **DEBUG @ fillbuf--> FILE READ ERROR **\n" ); }
			fptr->flags.ERRORMODE = 1;
		}
		fptr->cnt = 0;
		return EOF;
	}
	if (DEBUG) { printf("\t **DEBUG @ fillbuf--> RETURNING CHARACTER AT START OF BUFFER %c **\n", *fptr->ptr); }
	return (unsigned char) *fptr->ptr++; /* character at beginning of buffer */
}

/* _flushbuf allocates and flush buffer */
int _flushbuf(int c, _FILE *fptr)
{
	int bufsize;
	int nc; /* number of characters in buffer */
	if ( fptr->flags.WRITEMODE == 0 || fptr->flags.ERRORMODE == 1 ) {
		return EOF;
	}
	if (DEBUG) { printf("\t **DEBUG @ flushbuf--> CHECKED FILE FOR WRITING **\n" ); }
	bufsize = ( fptr->flags.UNBUFMODE == 1) ? (1) : (BUFSIZE);
	if (DEBUG) { printf("\t **DEBUG @ flushbuf--> BUFSIZE SET TO %d **\n" , bufsize); }
	if ( fptr->base == NULL) {
		if (DEBUG) { printf("\t **DEBUG @ flushbuf--> ALLOCATING SPACE FOR BUFFER **\n" ); }
		if ( ( fptr->base = (char *)malloc(bufsize)) == NULL) {
			fptr->flags.ERRORMODE = 1; /* signal error allocating space for writing */
			return EOF;
		}
	} else {
		if (DEBUG) { printf("\t **DEBUG @ flushbuf--> FLUSHING BUFFER **\n" ); }
		nc = fptr->ptr - fptr->base;
		if (DEBUG) { printf("\t **DEBUG @ flushbuf--> %d BYTES TO FLUSH **\n", nc); }
		if ( write( fptr->fd, fptr->base, nc) != nc) {
			if (DEBUG) { printf("\t **DEBUG @ flushbuf--> DIDN'T WRITE ENOUGH BYTES **\n" ); }
			fptr->flags.ERRORMODE = 1;
			return EOF;
		}
		if (DEBUG) { printf("\t **DEBUG @ fflush--> DONE WRITING BUFFER TO FILE **\n" ); }
	}
	if (DEBUG) { printf("\t **DEBUG @ flushbuf--> DONE ALLOCATING/FLUSHING **\n" ); }
	fptr->ptr = fptr->base;
	*fptr->ptr++ = (unsigned char)c;
	if (DEBUG) { printf("\t **DEBUG @ flushbuf--> PLACED %c IN BUFFER. RETURNING CH. **\n"  , *( fptr->ptr)); }
	fptr->cnt = bufsize - 1; /* number of characters that can be written */
	return c;
}

/* _fflush flushes buffer associated with file pointer */
int _fflush( _FILE *fptr)
{
	int rc = 0; /* return code of 0 indicates success, EOF indicates failure */
	if (fptr->flags.WRITEMODE == 1) {
		if (DEBUG) { printf("\t **DEBUG @ _fflush--> FLUSHING BUFFER INTO FILE **\n" ); }
		rc = _flushbuf(0, fptr); /* place null at start of buffer */
	}
	if (DEBUG) { printf("\t **DEBUG @ fflush--> RESETTING BUFFER VARIABLES **\n" ); }
	/* reset ptr, cnt */
	fptr->ptr = fptr->base;
	fptr->cnt = ( fptr->flags.UNBUFMODE == 1) ? (1) : (BUFSIZE);
	return rc;
}

/* fopen opens a file with name and mode and returns the file pointer */
_FILE *_fopen(char *name, char *mode)
{
	int fd;
	_FILE *fptr;
	if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
		return _NULL;
	}
	
	for (fptr = _iob ; fptr < _iob + OPEN_MAX ; ++fptr) {
		if (fptr->flags.READMODE == 0 && fptr->flags.WRITEMODE == 0) {
			if (DEBUG) { printf("\t **DEBUG @ fopen--> FOUND SPACE IN FILE BUFFER **\n" ); }
			/* find available space for file pointer in file buffer */
			break;
		}
	}
	if (fptr >= _iob + OPEN_MAX) {
		return _NULL;
	}
	if (*mode == 'w') {
		if (DEBUG) { printf("\t **DEBUG @ fopen--> CREATING FILE FOR WRITING **\n" ); }
		fd = creat(name, PERMS);
	} else if (*mode == 'a') {
		if (DEBUG) { printf("\t **DEBUG @ fopen--> OPENING FILE FOR APPENDING **\n" ); }
		if ( (fd = open(name, O_WRONLY, 0)) == -1 ) {
			fd = creat(name, PERMS);
		}
		lseek(fd, 0L, 2); /* point to end of file */
	} else {
		if (DEBUG) { printf("\t **DEBUG @ fopen--> OPENING FILE FOR READING **\n" ); }
		fd = open(name, O_RDONLY, 0);
	}
	if (fd == -1)
		return _NULL;
	if (DEBUG) { printf("\t **DEBUG @ fopen--> SUCCESS OPENING FILE **\n" ); }
	fptr->fd = fd;
	fptr->base = _NULL;
	fptr->cnt = 0; /* first call to getc/putc will call _fillbuf/_flushbuf that will try to allocate a buffer*/

	/* Set flag field */
	fptr->flags.UNBUFMODE = fptr->flags.ERRORMODE = fptr->flags.EOFMODE = 0;
	if (*mode == 'r') {
		fptr->flags.READMODE = 1;
		fptr->flags.WRITEMODE = 0;
	} else {
		fptr->flags.READMODE = 0;
		fptr->flags.WRITEMODE = 1;
	}
	if (DEBUG) { printf("\t **DEBUG @ fopen--> RETURNING FILE POINTER **\n" ); }
	return fptr;
}

int _fclose(_FILE *fptr)
{
	int rc;
	if (DEBUG) { printf("\t **DEBUG @ fclose--> ATTEMPTING TO CLOSE FILE **\n" ); }
	if ( (rc = _fflush(fptr)) != EOF) {
		if (DEBUG) { printf("\t **DEBUG @ fclose--> SUCCESS. RESETTING FILE VAR. **\n" ); }
		free(fptr->base);
		fptr->cnt = 0;
		fptr->flags.READMODE = fptr->flags.WRITEMODE = fptr->flags.UNBUFMODE = \
				       fptr->flags.ERRORMODE = fptr->flags.EOFMODE = 0;
		fptr->ptr = fptr->base = NULL;
	}
	return rc;
}
