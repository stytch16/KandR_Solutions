#include <stdarg.h> /* for variable length argument lists */
#include <stdio.h>

void minprintf(char *fmt, ...); /* ... implements variable length argument list */

int main(void)
{
	minprintf("TEST %s %d %f %d", "STRING", 1, 1.5, 2);
	return 0;
}

void minprintf(char *fmt, ...) /* ... implements variable length argument list */
{
	va_list ap; /* points to each unnamed arg in turn */
	char *p; /* points to each char in fmt */
	
	union {
		char *sval; /* %s */
		int ival; /* %d */
		double dval; /* %f */
	} fmtcode;	

	va_start(ap, fmt); /* ap points to first unnamed arg */
	for (p = fmt ; *p ; ++p) {
		if (*p != '%') {
			putchar(*p);
			continue; /* go to next iteration */
		}
		switch (*++p) {
			case 'd':
				/* int */
				fmtcode.ival = va_arg(ap, int); /* convert arg to int */
				printf("%d", fmtcode.ival);
				break;
			case 'f':
				/* float */
				fmtcode.dval = va_arg(ap, double);
				printf("%f", fmtcode.dval);
				break;
			case 's':
				/* string */
				for (fmtcode.sval = va_arg(ap, char *) ; *fmtcode.sval ; ++fmtcode.sval) {
					putchar(*fmtcode.sval);
				}
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap); /* clean up */
}
