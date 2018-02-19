/*
 * Filename: revFilenameCompare.s
 * Author: Yash Nevatia
 * User ID: cs30xpf
 * Description: This function will be used with qsort() to sort based on the
 * names of two struct fileInfo, in alphabetical order. Make sure to use the
 * offset defined in pa4Globals.c.
 * Date: 5 March 2017
 * Sources of Help
 */

 	.global revFilenameCompare

 	.section ".text"
/*
 * Function name: revFilenameCompare()
 * Function prototype: int revFilenameCompare( const void * p1,
 * 							const void * p2 );
 * Description: This function will be used with qsort() to sort based on the
 * names of two struct fileInfo, in alphabetical order. Make sure to use the
 * offset defined in pa4Globals.c.
 * Parameters:
 * 	p1 - the name of the first file to be compared
 * 	p2 - the name of the second file to be compared
 * Side Effects: none
 * Error Conditions: none
 * Return Value: -1 if the first name is smaller, 0 if the names are the same,
 * or +1 if the first name is larger.
 * Registers Used:
 * 	l0 - stat offset
 * 	l1 - filename offset
 * 	i0 - filename of p1
 * 	i1 - filename of p2
 */

revFilenameCompare:
	
	save	%sp, -96, %sp

	set 	statOffset, %l0
	ld 		[%l0], %l0
	set 	filenameOffset, %l1
	ld 		[%l1], %l1

	add 	%i0, %l0, %i0
	add 	%i0, %l1, %i0
	ld 		[%i0], %i0 			! rewrite filename of p1 into i0

	add 	%i1, %l0, %i1
	add 	%i1, %l1, %i1
	ld 		[%i1], %i1 			! rewrite filename of p2 into i1

	mov	 	%i0, %o0
	mov		%i1, %o1
	call 	strcmp 				! compare filenames
	nop

	cmp 	%o0, %g0
	be 		equal
	nop

	cmp 	%o0, %g0
	bl 		old
	nop

new: 							! return -1 if i0 comes after i1
	
	mov 	-1, %i0
	ba 		end
	nop

old: 							! return 1 if i0 comes before i1

	mov 	1, %i0
	ba 		end
	nop

equal: 							! return 0 if they're equal

	mov 	0, %i0

end:

ret
restore