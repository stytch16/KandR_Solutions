#ifndef FIO
#define FIO 

#define _NULL 0
#define _EOF (-1)
#define BUFSIZE 1024
#define OPEN_MAX 20 /* MAX _FILES THAT CAN BE OPEN AT ONCE */
#define PERMS 0666 /* user, group, and others have read-write permission */

typedef struct _iobuf {
	int cnt; /* characters left */
	char *ptr; /* next character position in buffer*/
	char *base; /* location of buffer */
	int fd; /* file descriptor */
	struct  {
		unsigned READMODE : 1;   /*  00001, file open for reading */
		unsigned WRITEMODE : 1;   /* 00010, file open for writing */
		unsigned UNBUFMODE : 1;   /* 00100, file is unbuffered */
		unsigned EOFMODE : 1;    /*  01000, EOF has occurred on file */
		unsigned ERRORMODE : 1; /*   10000, error occurred on file */
	} flags;
} _FILE;
extern _FILE _iob[OPEN_MAX]; /* storage for open files */

#define _stdin (&_iob[0]) /* Reserve space for stdin, stdout, stderr */
#define _stdout (&_iob[1])
#define _stderr (&_iob[2])


/* MACROS */
#define _feof(p) (((p)->flag & _EOF) != 0)
#define _ferror(p) (((p)->flag & _ERR) != 0)
#define _fileno(p) ( (p)->fd)

/* getc decrements count, advances pointer, and returns char.
 * if count is non-positive, call _fillbuf */
#define _getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define _putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define _getchar() _getc(_stdin)
#define _putchar(x) _putc((x), _stdout)

/* _fillbuf replenishes the buffer, reinitializes the structure contents, and returns a char for getc()*/
int _fillbuf( _FILE *);
/* _flushbuf allocates a buffer, places int at start of buffer, and returns the int */
int _flushbuf(int, _FILE *);
/* _fflush flushes buffer associated with file pointer */
int _fflush( _FILE *fptr);
/* fopen opens a file with name and mode and returns the file pointer */
_FILE *_fopen(char *name, char *mode);
int _fclose(_FILE *fptr);

#endif /* ifndef FIO */
