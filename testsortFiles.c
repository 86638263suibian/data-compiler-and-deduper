/*
 * Filename: testsortFiles.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: Unit test program to test the function sortFiles().
 * Date: 5 March 2017
 * Sources of Help
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "pa4.h" /* For sortFiles() function prototype */
#include "test.h" /* For TEST() macro and stdio.h */

#define SYSRUN(CMD)(system(CMD))

static void runTest(int numFiles, char * filenames[], unsigned int flags,
    char * expectedOrder[], int expectedNull, char * expectedErr,
    char * testDesc);

static char * testFileName = ".test_sortFiles_student_file";
static FILE * testFilePtr;

/*
 * Unit Test for sortFiles.c
 * 
 * FILE ** sortFiles( int numFIles, char * filenames[], unsigned int flags );
 *
 * Sorts the files specified by the filenames based on the sort comparison
 * specified by the flags. Then opens the files for reading and returns their
 * file pointers.
 */
static void testsortFiles() {
    int numFiles;
    int expectedNull;
    unsigned int flags;

    /* Test 1 */
    (void) fprintf(stderr, "\nRUNNING TEST 1!\n");
    numFiles = 1;
    char * filenames1[] = {
        "badfile"
    };
    flags = 0;
    char * expectedOrder1[] = {
        "badfile"
    };
    expectedNull = 1;
    char * expectedErr1 = "badfile: No such file or directory\n";

    runTest(numFiles, filenames1, flags, expectedOrder1, expectedNull,
        expectedErr1, "Test 1, file does not exist");

    /* Test 2 */
    (void) fprintf(stderr, "\nRUNNING TEST 2!\n");
    numFiles = 1;
    char * filenames2[] = {
        "restrictedFile"
    };
    flags = 0;
    char * expectedOrder2[] = {
        "restrictedFile"
    };
    expectedNull = 1;
    char * expectedErr2 = "restrictedFile: Permission denied\n";

    runTest(numFiles, filenames2, flags, expectedOrder2, expectedNull,
        expectedErr2, "Test 2, do not have permission to open file");

    /* Test 3 */
    (void) fprintf(stderr, "\nRUNNING TEST 3!\n");
    numFiles = 3;
    char * filenames3[] = {  "second", "first", "third" };
    flags = 0;
    char * expectedOrder3[] = { "first", "second", "third" };
    expectedNull = 0;

    runTest(numFiles, filenames3, flags, expectedOrder3, expectedNull, "",
        "Test 3, alphabetise normally");

    /* Test 4 */
    (void) fprintf(stderr, "\nRUNNING TEST 4!\n");
    numFiles = 3;
    char * filenames4[] = { "second", "first", "third" };
    flags = FLAG_R;
    char * expectedOrder4[] = { "third", "second", "first" };
    expectedNull = 0;

    runTest(numFiles, filenames4, flags, expectedOrder4, expectedNull, "",
        "Test 4, alphabetise in reverse");

    /* Test 5 */
    (void) fprintf(stderr, "\nRUNNING TEST 5!\n");
    numFiles = 4;
    char * filenames5[] = { "second", "first", "third", "fourth" };
    flags = FLAG_T;
    char * expectedOrder5[] = { "first", "second", "third", "fourth" };
    expectedNull = 0;

    runTest(numFiles, filenames5, flags, expectedOrder5, expectedNull, "",
        "Test 5, chronological normally");

    /* Test 6 */
    (void) fprintf(stderr, "\nRUNNING TEST 6!\n");
    numFiles = 4;
    char * filenames6[] = { "fourth", "second", "first", "third" };
    flags = FLAG_T + FLAG_R;
    char * expectedOrder6[] = {  "fourth", "third", "second", "first" };
    expectedNull = 0;

    runTest(numFiles, filenames6, flags, expectedOrder6, expectedNull, "",
        "Test 6, chronological in reverse");
}

/*
 * Function Name: runTest()
 * Function Prototype: void runTest(unsigned int bank[], char * expectedOutput,
                                     char * testDesc );
 * Description:  Helper function to actually run a test of displayLights.
 *               Prints test description (as specified by testDesc), and
 *               calls displayLights, handling segfaults.
 * Parameters:
 *     arg1: unsigned int bank[] -- bank of lights
 *     arg2: char * expectedOutput -- the expected output to be printed by
 *                                    displayLights()
 *     arg3: char * testDesc -- Description of the test being run
 * Side Effects: Outputs the result of the test to stderr
 * Error Conditions: None
 * Return Value: None
 */
static void runTest(int numFiles, char * filenames[], unsigned int flags,
    char * expectedOrder[], int expectedNull, char * expectedErr,
    char * testDesc) {
    /* 
     * Begin setup to capture stderr to a file. You aren't expected to know how
     * to do this, but it never hurts to learn!
     */
    testFilePtr = fopen(testFileName, "w+");
    int saveErr = dup(fileno(stderr));
    if (testFilePtr == NULL) {
        perror("Could not open test file");
        exit(1);
    }

    if (dup2(fileno(testFilePtr), fileno(stderr)) == -1) {
        perror("Could not duplicate stderr file descriptor");
        exit(1);
    }
    /* End setup to capture stdout */

    /* buffer for comparing output */
    char buf[BUFSIZ] = {
        0
    };

    /* Print test description */
    (void) fprintf(stdout, "%s\n", testDesc);

    /* Sort the files and flush stderr */
    FILE * * sortedFiles = sortFiles(numFiles, filenames, flags);
    (void) fflush(stderr);

    /* Reset file pointer */
    (void) fseek(testFilePtr, 0, SEEK_SET);

    /* Read from test file and compare */
    (void) fgets(buf, BUFSIZ, testFilePtr);

    /* Close file when done and restore stderr*/
    (void) fclose(testFilePtr);
    if (dup2(saveErr, fileno(stderr)) == -1) {
        perror("Could not restore stderr file descriptor");
        exit(1);
    }

    /* Real testing starts here */

    /* That any errors printed matched first */
    TEST(strncmp(buf, expectedErr, BUFSIZ) == 0);
    if (strncmp(buf, expectedErr, BUFSIZ) != 0) {
        (void) fprintf(stderr, "Expected output: %s\n", expectedErr);
        (void) fprintf(stderr, "Actual output: %s\n\n", buf);
    }

    /* check if an error was expected */
    if (expectedNull) {
        TEST(sortedFiles == NULL);
    } else {
        int notSortedCorrectly = 0;

        for (int i = 0; i < numFiles; ++i) {
            
            struct stat * eFI = malloc(sizeof(struct stat));
            // expected file info
            stat(expectedOrder[i], eFI);

            struct stat * sFI = malloc(sizeof(struct stat)); 
            // sorted file info
            fstat(fileno(sortedFiles[i]), sFI);
            // use file descriptor to get stat

            if(sFI -> st_ino != eFI -> st_ino) notSortedCorrectly = 1;

            free(eFI);
            free(sFI);
        }

        TEST(notSortedCorrectly == 0);
    }

}

int main() {

    (void) fprintf(stderr, "Running tests for sortFiles...\n");
    testsortFiles();
    (void) fprintf(stderr, "\nDone running tests!\n");

    return 0;
}
