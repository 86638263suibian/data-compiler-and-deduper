/*
 * File:        pa4.h
 * Description: Header file that contains function prototypes and constants.
 *
 * XXX Only add constants to this file at the bottom.
 * DO NOT EDIT FUNCTION PROTOTYPES OR PREDEFINED CONSTANTS
 *
 */

#ifndef PA4_H
#define PA4_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <sys/stat.h>


/* enum for mutually exclusive options to determine output mode */
enum outputMode {
  duplicate,      /* -d flag: only print duplicate lines       */
  unique,         /* -u flag: only print unique lines          */
  regular         /* default mode: print 1st copy of each line */
};

/* Struct to store information about an input file */
struct fileInfo {
  struct stat statInformation;
  char * filename;
};

/* Struct to store the contents of the merged input files */
struct fileLines {
  char ** lines;
  int numLines;
};

/* Struct to store a single distinct line from the merged input files */
struct distinctLine {
  unsigned int count;
  char * line;
};

/* Struct to use as the head node for the array of distinctLine structs */
struct distinctHead {
  struct distinctLine * head;
  unsigned int numDistinctLines;
};


/* Local function prototypes for PA4 written in C */
FILE ** sortFiles( int numFiles, char * filenames[], unsigned int flags );
struct fileLines mergeFiles( FILE ** files, int numFiles );
int compareLines( const void * p1, const void * p2 );
int compareLinesIgnoreCase( const void * p1, const void * p2 );
struct distinctHead buildData( struct fileLines * fileLines, 
                               unsigned int flags );
void displayOutput( struct distinctHead distinctHead, unsigned int flags, 
                    enum outputMode outputMode );

/* Local function prototypes for PA4 written in Assembly */
int timeCompare( const void * p1, const void * p2 );
int revTimeCompare( const void * p1, const void * p2 );
int filenameCompare( const void * p1, const void * p2 );
int revFilenameCompare( const void * p1, const void * p2 );


/* Arg string for use with getopt_long() */
#define ARG_STR "cdirstuh"

/* Bit masks to use with the bitmap to keep track of which flags are set */
#define FLAG_D 0x01
#define FLAG_U 0x02
#define FLAG_C 0x04
#define FLAG_I 0x08
#define FLAG_R 0x10
#define FLAG_S 0x20
#define FLAG_T 0x40
#define FLAG_H 0x80

/* Short options/flags */
#define FLAG_D_CHAR 'd' 
#define FLAG_U_CHAR 'u' 
#define FLAG_C_CHAR 'c' 
#define FLAG_I_CHAR 'i' 
#define FLAG_R_CHAR 'r' 
#define FLAG_S_CHAR 's' 
#define FLAG_T_CHAR 't' 
#define FLAG_H_CHAR 'h' 

/* Long options/flags */
#define FLAG_D_STR "duplicate" 
#define FLAG_U_STR "unique" 
#define FLAG_C_STR "displayCount" 
#define FLAG_I_STR "ignoreCase" 
#define FLAG_R_STR "reverse" 
#define FLAG_S_STR "sort" 
#define FLAG_T_STR "timeCompare" 
#define FLAG_H_STR "help" 


/* TODO Add any constants that you wish below this line. DONT EDIT ABOVE THIS */


#endif /* PA4_H */
