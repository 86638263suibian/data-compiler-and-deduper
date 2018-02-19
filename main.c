/*
 * Filename: main.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This is the main driver for the program. Its main tasks are to
 * parse the command line arguments, open and merge the input files, sort the
 * content of the merged files if the -s flag is set, then record all distinct
 * lines and the count of their occurrence into an array of distinctLine
 * structs, and finally display output based on the output mode (regular, 
 * duplicate, or unique -- an enum is defined for this in pa4.h).
 * Date: 10 March 2017
 * Sources of Help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa4.h"
#include "pa4Strings.h"

/*
 * Function name: main()
 * Function prototype:  int main( int argc, char * argv[] );
 * Description: This is the main driver for the program. Its main tasks are to
 * parse the command line arguments, open and merge the input files, sort the
 * content of the merged files if the -s flag is set, then record all distinct
 * lines and the count of their occurrence into an array of distinctLine
 * structs, and finally display output based on the output mode (regular, 
 * duplicate, or unique -- an enum is defined for this in pa4.h).
 * Parameters:
 * 		arg 1: argc -- number of arguments
 * 		arg 2: argv -- array of arguments
 * Side Effects: none
 * Error Conditions: 
 * - Bad option detected by getopt_long() -> print short usage.
 * - Mutually exclusive flags set at the same time -> print corresponding error
 *   message from pa4Strings.h and short usage
 * - No files were passed in as command line arguments -> print short usage.
 * - Error detected (and reported) in sortFiles() -> nothing to print.
 * - Error detected (and reported) in mergeFiles() -> nothing to print.
 * Return Value: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */

int main( int argc, char * argv[] ) {
	char c; //for get opts response
	int idxptr = 0;  // index pointer for get opts long
	unsigned int flags = 0; // flags bitmap
	enum outputMode mode = regular;

	struct option options[] = { // long options for getopt_long
		{FLAG_D_STR, no_argument, NULL, FLAG_D_CHAR},
		{FLAG_U_STR, no_argument, NULL, FLAG_U_CHAR},
		{FLAG_C_STR, no_argument, NULL, FLAG_C_CHAR},
		{FLAG_I_STR, no_argument, NULL, FLAG_I_CHAR},
		{FLAG_R_STR, no_argument, NULL, FLAG_R_CHAR},
		{FLAG_S_STR, no_argument, NULL, FLAG_S_CHAR},
		{FLAG_T_STR, no_argument, NULL, FLAG_T_CHAR},
		{FLAG_H_STR, no_argument, NULL, FLAG_H_CHAR}
	};

	// loops through flags and adds to bitmap appropriately
	while ((c = getopt_long(argc, argv, ARG_STR, options, &idxptr)) != -1)
		switch (c) {
			case FLAG_D_CHAR:
				flags += FLAG_D;
				mode = duplicate;
				break;
			case FLAG_U_CHAR:
				flags += FLAG_U;
				mode = unique;
				break;
			case FLAG_C_CHAR:
				flags += FLAG_C;
				break;
			case FLAG_I_CHAR:
				flags += FLAG_I;
				break;
			case FLAG_R_CHAR:
				flags += FLAG_R;
				break;
			case FLAG_S_CHAR:
				flags += FLAG_S;
				break;
			case FLAG_T_CHAR:
				flags += FLAG_T;
				break;
			case FLAG_H_CHAR: // help flag prints usage and returns
				printf(STR_USAGE_LONG, argv[0]);
				return EXIT_SUCCESS;
		}

	if((flags & FLAG_D) && (flags & FLAG_U)) { // checks for mutual exclusion
		fprintf(stderr, STR_ERR_MUTUAL_EX);
		fprintf(stderr, STR_USAGE_SHORT, argv[0], argv[0]);
		return EXIT_FAILURE;
	}

	if(argc <= optind) { // checks if no filename passed (no args after flags)
		fprintf(stderr, STR_USAGE_SHORT, argv[0], argv[0]);
		return EXIT_FAILURE;
	}

	char * filename = malloc(sizeof(char *));
	char ** filenames = malloc(sizeof(char *));
	int numFiles = 0;
	while((filename = argv[optind]) != NULL){ // loops through filenames
		numFiles++; // (this and below) adds filename to filenames array 
		filenames = realloc(filenames, sizeof(char *) * numFiles);
		filenames[numFiles - 1] = filename;
		optind++;
	}

	// sorts and opens files into 'files'
	FILE ** files = sortFiles(numFiles, filenames, flags);
	if(!files) return EXIT_FAILURE; // exits if there is error in sortFiles

	// merges lines of files into 'mergedLines'
	struct fileLines mergedLines = mergeFiles(files, numFiles);
	if(!(mergedLines.lines)) return EXIT_FAILURE; // exits if error in merge

	int sort = flags & FLAG_S; // saves nonzero if sort flag is passed
	int insensitive = flags & FLAG_I; // saves nonzero if insensitive passed

	if(sort && insensitive) // sorts insensitively
		qsort(mergedLines.lines, mergedLines.numLines,
			sizeof(char *), compareLinesIgnoreCase);
	else if(sort) // sorts sensitively
		qsort(mergedLines.lines, mergedLines.numLines,
			sizeof(char *), compareLines);

	// builds data from merged lines with flags into 'distinctInfo'
	struct distinctHead distinctInfo = buildData(&mergedLines, flags);
	displayOutput(distinctInfo, flags, mode); // displays output

	// freeing allocated space: 

	free(filename);
	free(filenames);
	free(files);

	for (int i = 0; i < mergedLines.numLines; ++i)
		free(&mergedLines.lines[i]);

	for (int i = 0; i < distinctInfo.numDistinctLines; ++i)
		free(&distinctInfo.head[i]);

	return EXIT_SUCCESS;
}
