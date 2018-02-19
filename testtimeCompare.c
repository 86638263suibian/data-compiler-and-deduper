/*
 * Filename: testtimeCompare.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: Unit test program to test the assembly function timeCompare.
 * Date: 5 March 2017
 * Sources of Help
 */ 

#include <string.h>

#include "test.h"
#include "pa4.h"

/*
 * Unit Test for timeCompare.s
 * 
 * int timeCompare( const void * p1, const void * p2 )
 * 
 * Compares two times passed in for sorting purposes. 
 * Returns 0 if the times are the same, -1 if the first time
 * is smaller, or +1 if the first time is larger.
 */

void testtimeCompare() {
  printf( "Testing timeCompare()\n" );

  struct fileInfo f1; 
  struct fileInfo f2; 
  
  f1.statInformation.st_mtime = 1488757730;
  f2.statInformation.st_mtime = 1488757748;
  TEST( timeCompare( &f1, &f2 ) == -1 );

  f1.statInformation.st_mtime = 1488757748;
  f2.statInformation.st_mtime = 1488757748;
  TEST( timeCompare( &f1, &f2 ) == 0 );

  f1.statInformation.st_mtime = 1488757750;
  f2.statInformation.st_mtime = 1488757748;
  TEST( timeCompare( &f1, &f2 ) == 1 );

  printf( "Finished running tests on timeCompare()\n" );
}


int main() {
  testtimeCompare();
  return 0;
}
