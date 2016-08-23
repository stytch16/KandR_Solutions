/* Fold long input lines into shorter lines after last non-blank character that occurs
 * before nth column of input.
 * 
 * >> this is my very long string that exceeds n
 * 
 * >> this is my
 * >> very long
 * >> string 
 * >> that
 * >> exceeds n 
 *
 */

#include <stdio.h>
#include "line.h"

#define COLUMNLENGTH 10
#define MAXLINE 1000

int insert(char s[], const char ch, const int pos, const int lim);
int find_lastof(const char s[], const char ch, const int fromX);

int main(void)
{
	char line[MAXLINE];
	char temp[MAXLINE];
	char placeholder[MAXLINE];

	int len;
	int pos_line;
	int pos_temp;
	int pos_placeholder;
	int last_blank;

	while ( (len = getLine(line, MAXLINE) ) > 0 ) {
	
		pos_line = 0;
		pos_placeholder = 0;
		
		for (; pos_line < len; ) {
			for (pos_temp = 0;\
				        (pos_line < len) && \
					pos_temp < COLUMNLENGTH; ++pos_temp, ++pos_line) {
				temp[pos_temp] = line[pos_line];
			}

			temp[pos_temp] = '\0';
			last_blank = find_lastof(temp, ' ', pos_temp);

			if (last_blank == -1) {
				if (pos_line >= len) {
					for (pos_temp = 0; \
							(placeholder[pos_placeholder++] \
							 = temp[pos_temp] ) != '\0' ; \
							++pos_temp);
				}
				else{
					--pos_line;
					for (pos_temp = 0; \
							pos_temp < (COLUMNLENGTH - 1);
							++pos_temp) {
						placeholder[pos_placeholder++] \
							= temp[pos_temp];
					}
					placeholder[pos_placeholder++] = '\\';
					placeholder[pos_placeholder++] = '\n';
				}		
			}
			else {
				pos_line = pos_line - pos_temp + last_blank  + 1;
				for (pos_temp = 0; pos_temp <= last_blank; ++pos_temp) {
					placeholder[pos_placeholder++] = temp[pos_temp];
				}
				placeholder[pos_placeholder++] = '\n';
			}
		}
		placeholder[pos_placeholder] = '\0';

		printf("%s\n", placeholder );
	}	
	return 0;
}

int find_lastof(const char s[], const char ch, const int fromX) 
{
	int i;
	for (i = fromX; i >= 0 && s[i] != ch; --i);
	return i;
	// returns -1 if the ch was not found. otherwise, returns index of char in s.	
}

int insert(char s[], const char ch, const int pos, const int lim)
{
	char temp[lim];	
	
	int i, j;
	for (i = 0, j = 0; s[i] != '\0'; ++i, ++j) {
		if (i == pos){
			temp[j++] = ch;
		}
		temp[j] = s[i];
	}
	temp[j] = '\0';

	// pos exceeded the length of array s so return a false flag
	if (j == i) {
		return 0;
	}
	else{
		copy(s, temp);
		return 1;
	}
}
