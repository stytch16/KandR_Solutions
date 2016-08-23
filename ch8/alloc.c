#define _GNU_SOURCE
#define DEBUG 1 /* Toggle debugging statements */
#include "alloc.h"
#include <stddef.h>
#include <unistd.h> /* sbrk(intptr_t incr) */
#include <stdio.h>

#define MAXBYTES 1073741824 /* 1 GB size limit on memory space for this program */

typedef long Align; /* 64 bit (64-bit system) alignment of all variables */

/* header is a block w info that comes before blocks for free storage */
union header {
	struct  {
		union header *ptr; /* pointer to next block in free list */
		unsigned size; /* size of block */
	} s;
	Align x; /* alignment -> address of header is a multiple of 64  */
	/* not necessary however because size of s is 16 > 8 */
} ;
typedef union header Header;

static Header base; /* Header element with null data for linked list -> free list */
static Header *freep = NULL; /* pointer to free list */

static Header *morecore(unsigned); /* asks OS for memory if all in use */

static unsigned maxalloc = 0;

void *my_calloc(unsigned bytes, unsigned size)
{
	unsigned totalbytes;
	char *p = my_malloc((totalbytes = bytes * size));
	if (p != NULL) {
		/* initializes every byte/char to 0 */
		char *q;
		unsigned i;
		for (q = p, i = 0 ; i < totalbytes ; ++i, ++q) {
			*q = 0;
		}
	}
	return (void *)p;
}

void *my_malloc(unsigned bytes)
{

	if (DEBUG) { printf("\t **DEBUG @ my_malloc--> CALL WITH BYTES PARAM = %u **\n" , bytes); }
	if (bytes > MAXBYTES) {
		fprintf(stderr, "requested memory exceeds program size limit set at 1 GB\n");
	}

	Header *p; /* pointer index for linked list, return var*/
	Header *prevp; /* pointer to save position of p after return */

	unsigned nunits; /* block is of (nunits * sizeof header) bytes */

	/* round up the number of header sized units needed  */
	nunits = (bytes + sizeof(Header) - 1) / (sizeof(Header)) + 1;
	if (DEBUG) { printf("\t **DEBUG @ my_malloc--> COMPUTED N_UNITS = %u **\n" , nunits); }

	/* following only called when no free list created */
	if (!(prevp = freep)) {
		if (DEBUG) { printf("\t **DEBUG @ my_malloc--> NO FREE LIST CREATED YET, FREE_P IS NULL **\n" ); }
		/* no free list created yet, create degenerate free list */
		/* block of size 0, and header ptr points to itself */
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
		if (DEBUG) { printf("\t **DEBUG @ my_malloc--> CREATED DEGENERATE LIST OF SIZE = 0 **\n" ); }
	}
	/* Look for free block */
	if (DEBUG) { printf("\t **DEBUG @ my_malloc--> LOOKING FOR A FREE BLOCK **\n" ); }
	for (p = prevp->s.ptr ; /* no condition, return statement */ 
			; (prevp = p) ,  p = p->s.ptr) {
		if (DEBUG) { printf("\t **DEBUG @ my_malloc--> p->s.size = %u vs nunits = %u **\n", p->s.size, nunits); }
		/* is there enough units in free list? */
		if ( p->s.size >= nunits) {
			if ( p->s.size == nunits) {
				if (DEBUG) { printf("\t **DEBUG @ my_malloc--> BLOCK IS EXACTLY %u UNITS REQUESTED **\n" ,nunits); }
				prevp->s.ptr = p->s.ptr;
				if (DEBUG) { printf("\t **DEBUG @ my_malloc--> PREV_P PTR TO NEXT SET TO P PTR TO NEXT **\n" ); }
			} else {
				/* split block */
				if (DEBUG) { printf("\t **DEBUG @ my_malloc--> SPLIT BLOCK, GET TAIL END **\n" ); }
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
				if (DEBUG) { printf("\t **DEBUG @ my_malloc--> P AT x_%p, UPDATED P SIZE TO %u **\n" , p, nunits); }
			}
			freep = prevp;
			if (DEBUG) { printf("\t **DEBUG @ my_malloc--> FREE_P AT PREV_P, x_%p **\n" , freep); }
			if (DEBUG) { printf("\t **DEBUG @ my_malloc--> RETURNING USER STORAGE PORTION OF TAIL END **\n" ); }
			return (void *)(p + 1); 
			/* return address of starting block */
			/* for free storage */
		}
		if (p == freep) {
			if (DEBUG) { printf("\t **DEBUG @ my_malloc--> POINTER INDEX AT START OF FREE LIST -> NO MORE SPACE IN FREE LIST **\n" ); }
			if (DEBUG) { printf("\t **DEBUG @ my_malloc--> CALLING MORECORE(%u) **\n" , nunits); }
			if (!(p = morecore(nunits))) {
				return NULL;
			}
			/* if morecore returns NULL, failed to get  */
			/* more memory from OS. */
		}
	}
}

#define NALLOC 1024 /* minimum number of units to request from OS */

static Header *morecore(unsigned nu)
{
	if (DEBUG) { printf("\t **DEBUG @ morecore--> CALL TO MORECORE(%u) **\n" , nu); }
	char *cp; /* pointer to memory received from OS */
	Header *up;
	if (nu < NALLOC) {
		nu = NALLOC;
	}
	if (DEBUG) { printf("\t **DEBUG @ morecore--> ASKING OS FOR %u SPACE **\n" , nu); }
	cp = sbrk(nu * sizeof(Header)); /* allocates space, returns void ptr */
	if (cp == (char *)-1) { /* sbrk returns -1 not NULL if failed */
		return NULL;
	}
	up = (Header *)cp;
	if (DEBUG) { printf("\t **DEBUG @ morecore--> GOT ALLOCATED SPACE AND A HEADER PTR AT %p **\n", up); }
	up->s.size = nu;

	/* update maximum block units allocated */
	maxalloc = (maxalloc < up->s.size) ? (up->s.size) : (maxalloc); 

	if (DEBUG) { printf("\t **DEBUG @ morecore--> HEADER PTR DEREFERENCES SIZE OF %u **\n" , up->s.size); }
	if (DEBUG) { printf("\t **DEBUG @ morecore--> CALLING MY_FREE(x_%p) **\n" , up + 1); }
	my_free((void *)(up + 1)); /* insert new free block to free list */
	return freep;
}

void my_free(void *ap) 
{
	if (DEBUG) { printf("\t **DEBUG @ my_free--> CALLED MY_FREE **\n" ); }
	Header *bp; /* points to block to be freed */
	Header *p; /* pointer index for linked list */

	bp = (Header *)ap - 1;

	/* error-checking, ensure that the address at block pointer contains an allocated block thru malloc */
	if (bp->s.size == 0 || bp->s.size > maxalloc) { /* Check size field of block is valid in free list */
		fprintf(stderr, "block does not contain a valid size field\n");	
	}
	if (DEBUG) { printf("\t **DEBUG @ my_free--> BLOCK TO BE FREED IS AT x_%p **\n", bp); }
	/* Insert free block : storage addresses of blocks are kept in incr. order */
	for (p = freep ; !(bp > p && bp < p->s.ptr) ; p = p->s.ptr) {
		if (DEBUG) { printf("\t **DEBUG @ my_free--> SCAN FREE LIST **\n" ); }
		if (DEBUG) { printf("\t **DEBUG @ my_free--> &p = x_%p, &p->s.ptr = x_%p, &bp = x_%p **\n" , p, p->s.ptr, bp); }
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr) ) {
			if (DEBUG) { printf("\t **DEBUG @ my_free--> (p >= p->s.ptr && (bp > p || bp < p->s.ptr) == TRUE SO SCANNING DONE **\n" ); }
			break;
		}
	}
	if (DEBUG) { printf("\t **DEBUG @ my_free--> CONNECTING LINKS **\n" ); }
	if (DEBUG) { printf("\t **DEBUG @ my_free--> (bp+bp->s.size = x_%p vs. p->s.ptr = x_%p **\n", (bp+bp->s.size), p->s.ptr); }
	if (bp + bp->s.size == p->s.ptr) {
		if (DEBUG) { printf("\t **DEBUG @ my_free--> ADJUSTING SIZES **\n" ); }
		bp->s.size += p->s.ptr->s.size;
		if (DEBUG) { printf("\t **DEBUG @ my_free--> BP SIZE INCREMENTED BY SIZE OF LAST FREED BLOCK FOLLOWING IT**\n" ); }
		bp->s.ptr = p->s.ptr->s.ptr;
		if (DEBUG) { printf("\t **DEBUG @ my_free--> BP PTR PLACED AT LOCATION OF BASE HEADER **\n" ); }
	} else {
		if (DEBUG) { printf("\t **DEBUG @ my_free--> PLACING BP POINTER TO NEXT TO P POINTER TO NEXT **\n" ); }
		bp->s.ptr = p->s.ptr;
	}
	if (DEBUG) { printf("\t **DEBUG @ my_free--> (p+p->s.size = x_%p) vs. (bp = x_%p) **\n" , (p+p->s.size), bp); }
	if (p + p->s.size == bp) {
		if (DEBUG) { printf("\t **DEBUG @ my_free--> THIS BLOCK WAS LAST ONE GIVEN TO USER SO FUSING IT WITH LEFTOVER SPACE **\n" ); }
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
		if (DEBUG) { printf("\t **DEBUG @ my_free--> P POINTER TO NEXT NOW POINTS TO HEADER OF FREED SPACE BLOCK **\n" ); }
	} else {
		if (DEBUG) { printf("\t **DEBUG @ my_free--> PLACING P POINTER TO NEXT TO BP **\n" ); }
		p->s.ptr = bp;
	}
	freep = p;
	if (DEBUG) { printf("\t **DEBUG @ my_free--> FREE PTR SET TO P AND RETURNING... **\n" ); }
}

unsigned bfree (void *fp, unsigned nbytes)
{
	if (nbytes < (sizeof(Header))) {
		fprintf(stderr, "bfree: must free some multiple of block size \n");
		return 0;
	}
	Header *hp = (Header *)fp;
	hp->s.size = nbytes / sizeof(Header); /* calculated size of space to free in block units */
	my_free((void *)(hp + 1)); /* pass block to my_free() */
	return hp->s.size; /* return header size units freed : user can create a static/external array of that length ??? */
}
