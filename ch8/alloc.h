#ifndef ALLOC_H
#define ALLOC_H
void *my_calloc(unsigned bytes, unsigned size);
void *my_malloc(unsigned bytes);
void my_free(void *ap);
unsigned bfree(void *, unsigned);
#endif
