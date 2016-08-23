#ifndef SEARCH_H
#define SEARCH_H 

/* Binary search
 * Returns index if x is in v
 * Otherwise, returns -1
 */
int recbinsearch( const int x, int v[], const unsigned from, \
		const unsigned to);
int binsearch( const int x, int v[], const int n );


#endif /* ifndef SEARCH_H */
