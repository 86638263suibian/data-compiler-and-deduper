/*
 * Filename: displayOutput.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This function simply takes the array of distinctLine structs
 * created in buildData() and displays the output lines according to the
 * outputMode. Depending on the outputMode, you will either want to print only
 * duplicate lines, print distinct lines, or print all filtered lines
 * (regular mode)
 * Date: 10 March 2017
 * Sources of Help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function name: displayOutput()
 * Function prototype: void displayOutput( struct distinctHead distinctHead,
 * 						unsigned int flags, enum outputMode outputMode );
 * Description: This function simply takes the array of distinctLine structs
 * created in buildData() and displays the output lines according to the
 * outputMode. Depending on the outputMode, you will either want to print only
 * duplicate lines, print distinct lines, or print all filtered lines
 * Parameters:
 * 		arg 1: distinctHead -- the data to print
 * 		arg 2: flags -- the options bitmap
 * 		arg 3: outputMode -- the mode of the output
 * Side Effects: none
 * Error Conditions: none
 * Return Value: none
 */

void displayOutput( struct distinctHead distinctHead,
	unsigned int flags, enum outputMode outputMode ){

	// loops through the lines of distincthead
	for (int i = 0; i < (distinctHead.numDistinctLines); ++i){

		if((distinctHead.head[i]).count == 1 && outputMode == duplicate)
			continue; // skips if the mode is duplicate and line is unique

		else if((distinctHead.head[i]).count > 1 && outputMode == unique)
			continue; // skips if the mode is unique and line >= duplicate
		
		if(flags & FLAG_C) // prints prefix in case of count flag
			printf(STR_COUNT_PREFIX, distinctHead.head[i].count);

		printf("%s", (distinctHead.head[i]).line); // prints line
	}
}
