/*
 * Filename: compareLinesIgnoreCase.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This function compares (case-insensitively) two input strings
 * using strcasecmp().This compare routine will be passed to qsort() when
 * comparing lines for sorting.
 * Date: 10 March 2017
 * Sources of Help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa4.h"

/*
 * Function name: compareLinesIgnoreCase()
 * Function prototype: int compareLinesIgnoreCase( const void * p1,
 * 						const void * p2 );
 * Description: This function compares (case-insensitively) two input strings
 * using strcasecmp().This compare routine will be passed to qsort() when
 * comparing lines for sorting.
 * Parameters:
 * 		arg 1: p1 -- pointer to string to compare
 * 		arg 2: p2 -- pointer to string to compare
 * Side Effects: none
 * Error Conditions: none
 * Return Value: -1 if strcasecmp() returns a negative value, 1 if strcasecmp()
 * returns a value larger than 0, or 0 if strcasecmp() returns 0
 */

int compareLinesIgnoreCase( const void * p1, const void * p2 ) {
	// cast void pointers to string pointers
	char ** a = (char **) p1;
	char ** b = (char **) p2;

	int comp = strcasecmp(*a, *b); // dereferences and compares string pointers
	
	// simplifies output for qsort
	if(comp < 0) return -1;
	if(comp > 0) return 1;

	return comp;
}
