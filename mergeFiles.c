/*
 * Filename: mergeFiles.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This function will merge the array of opened files line by line
 * into a single dynamically allocated lines array. The array will then be
 * stored in struct fileLines (see pa4.h) before the function returns.
 * Date: 10 March 2017
 * Sources of Help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function name: mergeFiles()
 * Function prototype: struct fileLines mergeFiles( FILE ** files,
 * 							int numFiles );
 * Description: This function will merge the array of opened files line by line
 * into a single dynamically allocated lines array. The array will then be
 * stored in struct fileLines (see pa4.h) before the function returns.
 * Parameters:
 * 		arg 1: files -- array of opened files to merge
 * 		arg 2: numFiles -- the number of files
 * Side Effects: none
 * Error Conditions: dynamic memory allocation failure returns erroneous result
 * Return Value: struct fileLines containing the lines pointer and the number
 * of lines
 */

struct fileLines mergeFiles( FILE ** files, int numFiles ) {
	char buffer[BUFSIZ]; // buffer to fgets
	char * input; // stores lines from file
	int closed = 0; // counts the number of files closed

	// starts new fileLines struct to return
	struct fileLines * fileLines = malloc(sizeof(struct fileLines));
	(fileLines -> numLines) = 0;
	(fileLines -> lines) = malloc(sizeof(char *));

	if(!(fileLines -> lines)){ // if fileLines isn't allocated appropriately
		(fileLines -> lines) = NULL;
		(fileLines -> numLines) = -1;
		fprintf(stderr, STR_ERR_MEM_EXCEEDED);
		return * fileLines; // returns error and erroneous struct fileLines
	}

	while(numFiles != closed){ // loops through lines
		for (int idx = 0; idx < numFiles; ++idx) { // loops through files

			if(!(files[idx])) continue; // skip closed files

			input = fgets(buffer, BUFSIZ, files[idx]); // saves input line

			if(!input){	// at end of a file, close file 
				fclose(files[idx]);
				files[idx] = NULL;
				closed++;
				continue;
			}
			
			input[BUFSIZ - 1] = '\0'; // null terminates input string

			(fileLines -> numLines)++; // makes space for new line			
			(fileLines -> lines) = realloc(fileLines -> lines,
				(fileLines -> numLines) * sizeof(char *));


			if(!((fileLines -> lines) + (fileLines -> numLines) - 1)){
				// if space isn't successfully made
				(fileLines -> lines) = NULL;
				(fileLines -> numLines) = -1;
				fprintf(stderr, STR_ERR_MEM_EXCEEDED);
				return * fileLines; // returns error and erroneuos fileLines
			}

			// adds the new line to fileLines
			*((fileLines -> lines) + ((fileLines -> numLines) - 1)) =
				malloc(strlen(buffer) + 1);
			strncpy(*((fileLines -> lines) + ((fileLines -> numLines) - 1)),
				input, (strlen(buffer) + 1));
		}
	}

	return * fileLines;
}
