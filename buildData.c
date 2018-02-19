/*
 * Filename: buildData.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This function will take in the content of the merged
 * (and possibly sorted) input files (stored in fileLines) and will filter out
 * consecutive duplicated lines. The resulting distinct lines will be stored in
 * a dynamically allocated array of struct distinctLine.
 * Date: 10 March 2017
 * Sources of Help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function name: buildData()
 * Function prototype: struct distinctHead buildData( struct fileLines *
 * 						fileLines, unsigned int flags );
 * Description: This function will take in the content of the merged
 * (and possibly sorted) input files (stored in fileLines) and will filter out
 * consecutive duplicated lines. The resulting distinct lines will be stored in
 * a dynamically allocated array of struct distinctLine.
 * Parameters:
 * 		arg 1: fileLines -- the lines to build data from
 * 		arg 2: flags -- the options bitmap passed in as argument(s)
 * Side Effects: none
 * Error Conditions: dynamic memory allocation failure returns erroneous or
 * partial distinctHead struct
 * Return Value: struct fileLines containing the lines pointer and the number
 * of lines
 */

struct distinctHead buildData( struct fileLines * fileLines,
	unsigned int flags ) {

	// creates distincthead to return
	struct distinctHead * data = malloc(sizeof(struct distinctHead));

	// starts up the values of the return struct
	(data -> numDistinctLines) = 0;
	(data -> head) = malloc(sizeof(struct distinctLine));

	if(!(data -> head)){ // if data isn't allocated appropriately
		(data -> head) = NULL;
		(data -> numDistinctLines) = 0;
		fprintf(stderr, STR_ERR_MEM_EXCEEDED);
		return * data; // returns error and erroneous struct data
	}

	for (int i = 0; i < (fileLines -> numLines); ++i) { // loops through lines

		int exists = 0; // saves index if this line is already in distinctHead
		char * inputLine = (fileLines -> lines)[i]; // saves the current line

		for (int j = 0; j < (data -> numDistinctLines); ++j) {
			// loops through distinctHead searching for inputLine

			char * dataLine = ((data -> head) + j) -> line;
			// saves the current line of the distinct head 
			
			if(!dataLine) continue; // skips if the line doesn't exsist
			
			if(flags & FLAG_I && 
				compareLinesIgnoreCase(&inputLine, &dataLine) != 0)
				continue; // for insensitive flag, skips if lines arent same
			
			else if (!(flags & FLAG_I) && 
				compareLines(&inputLine, &dataLine) != 0)
				continue; // for sensitive case, skips if lines arent same
			
			exists = j; // saves the index of the existing line 
			break;
		}

		if(exists) // if the line exsisted, increases count of that line
			(((data -> head) + exists) -> count)++;

		else { // otherwise, adds new line to distincthead

			(data -> numDistinctLines)++; // make room for new line
			(data -> head) = realloc(data -> head,
				(data -> numDistinctLines) * sizeof(struct distinctLine));

			if(!((data -> head) + ((data -> numDistinctLines) - 1))){
				// if fails to allocate more memory for next line
				fprintf(stderr, STR_ERR_MEM_EXCEEDED);
				return * data; // prints error returns partial struct data
			}

			// adds the line in the new room
			((data -> head) + ((data -> numDistinctLines) - 1)) -> count = 1;
			((data -> head) + ((data -> numDistinctLines) - 1)) -> line
				 = inputLine;
		}
	}

	return * data;
}
