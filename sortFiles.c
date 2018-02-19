/*
 * Filename: sortFiles.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This function will sort the files from filenames using qsort()
 * and the respective compare function according to the flags specified
 * (see Process Overview for information on the flags).
 * Date: 6 March 2017
 * Sources of Help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function name: sortFiles()
 * Function prototype:  FILE ** sortFiles( int numFiles, char * filenames[],
 * 							unsigned int flags );
 * Description: This function will sort the files from filenames using qsort()
 * and the respective compare function according to the flags specified
 * (see Process Overview for information on the flags).
 * Parameters:
 *  arg 1: numFiles -- the number of files to be sorted
 * 	arg 2: filenames -- an array of the filenames to be sorted
 * 	arg 3: flags -- the integer with all the flags specifying sort type
 *
 * Side Effects: none
 * Error Conditions: dynamic memory allocation fails, stat on a file fails,
 * opening of file fails
 * Return Value: null pointer in the case of error; otherwise, an array of
 * the opened files.
 */

FILE ** sortFiles( int numFiles, char * filenames[], unsigned int flags ){
	struct fileInfo * information = calloc(numFiles, sizeof(struct fileInfo));
	
	if(!information){ // checks that memory is properly allocated
		fprintf(stderr, STR_ERR_MEM_EXCEEDED);
		free(information);
		return NULL;	
	} 

	for (int i = 0; i < numFiles; ++i) { // saves fileinfo for each file
		(information + i) -> filename = filenames[i];
		if(stat((information + i) -> filename,
			&((information + i) -> statInformation)) != 0){
			// entertains stat error
			perror(filenames[i]);
			free(information);
			return NULL;
		}
	}

	int time = flags & FLAG_T; // saves nonzero int if time was set
	int rev = flags & FLAG_R; // saves nonzero int if reverse was set

	if(time){ // if time flag is active
		if(rev) qsort(information, numFiles, // sorts reverse for reverse flag
			sizeof(struct fileInfo), revTimeCompare);
		else qsort(information, numFiles, // otherwise supports chrono normal
			sizeof(struct fileInfo), timeCompare);
	} else { // entertains alphabetical case
		if(rev) qsort(information, numFiles, // sorts reverse for reverse flag
			sizeof(struct fileInfo), revFilenameCompare);
		else qsort(information, numFiles, // otherwise supports normal lexo
			sizeof(struct fileInfo), filenameCompare);
	}

	FILE ** files = calloc(numFiles, sizeof(FILE));
	
	if(!files){ // checks that memory is properly allocated
		fprintf(stderr, STR_ERR_MEM_EXCEEDED);
		free(files);
		free(information);
		return NULL;	
	}
	
	for (int i = 0; i < numFiles; ++i) {
	// prepares opened files in order for return
		files[i] = fopen((information + i) -> filename, "r");
		if(!(files[i])){ // checks that file opens properly
			perror((information + i) -> filename);
			free(files);
			free(information);
			return NULL;
		}
	}

	free(information);
	return files;
}
