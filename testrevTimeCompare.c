/*
 * Filename: testrevTimeCompare.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: Unit test program to test the assembly function revTimeCompare.
 * Date: 5 March 2017
 * Sources of Help
 */ 

#include <string.h>

#include "test.h"
#include "pa4.h"

/*
 * Unit Test for revTimeCompare.s
 *
 * 
 * int revTimeCompare( const void * p1, const void * p2 )
 * 
 * Compares two times passed in for sorting purposes. 
 * Returns 0 if the times are the same, +1 if the first time
 * is smaller, or -1 if the first time is larger.
 */

void testrevTimeCompare() {
  printf( "Testing revTimeCompare()\n" );

  struct fileInfo f1; 
  struct fileInfo f2; 
  
  f1.statInformation.st_mtime = 1488757730;
  f2.statInformation.st_mtime = 1488757748;
  TEST( revTimeCompare( &f1, &f2 ) == 1 );

  f1.statInformation.st_mtime = 1488757748;
  f2.statInformation.st_mtime = 1488757748;
  TEST( revTimeCompare( &f1, &f2 ) == 0 );

  f1.statInformation.st_mtime = 1488757750;
  f2.statInformation.st_mtime = 1488757748;
  TEST( revTimeCompare( &f1, &f2 ) == -1 );

  printf( "Finished running tests on revTimeCompare()\n" );
}


int main() {
  testrevTimeCompare();
  return 0;
}
