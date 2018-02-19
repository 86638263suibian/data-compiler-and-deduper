/*
 * Filename: timeCompare.s
 * Author: Yash Nevatia
 * User ID: cs30xpf
 * Description: This function will be used with qsort() to sort based on the
 * modification times (oldest first) of two struct fileInfo (which are passed
 * in as void pointers). See man -s2 stat to figure out how to access the
 * modification time of a struct stat. Make sure to use the offset defined in
 * pa4Globals.c. This function must be a leaf subroutine.
 * Date: 5 March 2017
 * Sources of Help
 */

	.global timeCompare

	.section ".text"

/*
 * Function name: timeCompare()
 * Function prototype: int timeCompare( const void * p1, const void * p2 );
 * Description: This function will be used with qsort() to sort based on the
 * modification times (oldest first) of two struct fileInfo (which are passed
 * in as void pointers). See man -s2 stat to figure out how to access the
 * modification time of a struct stat. Make sure to use the offset defined in
 * pa4Globals.c. This function must be a leaf subroutine.
 * Parameters:
 * 	p1 - the name of the first file to be compared
 * 	p2 - the name of the second file to be compared
 * Side Effects: none
 * Error Conditions: none
 * Return Value: -1 if the first modification time is older, 0 if the
 * modification times are the same, or +1 if the first modification time is
 * newer.
 * Registers Used:
 * 	%o0 - pointer to p1, overwritten to modification time of p1
 * 	%o1 - pointer to p2, overwritten to modification time of p2
 *	%o2 - address of modification time of p1
 *	%o3 - address of modification time of p2
 *	%o4 - stat offset
 *	%o5 - time offset
 */

timeCompare:

	set 	statOffset, %o4
	ld 		[%o4], %o4
	set 	mtimeOffset, %o5
	ld 		[%o5], %o5

	add 	%o0, %o4, %o2
	add 	%o2, %o5, %o2
	ld 		[%o2], %o0 			! rewrite modification time of p1 into o0

	add 	%o1, %o4, %o3
	add 	%o3, %o5, %o3
	ld 		[%o3], %o1 			! rewrite modification time of p2 into o1

	cmp 	%o0, %o1
	be 		equal
	nop

	cmp 	%o0, %o1
	bl 		old
	nop

new: 							! returns 1 if p1 is newer than p2
	
	mov 	1, %o0
	ba 		end
	nop

old:  							! returns -1 if p2 is newer than p1

	mov 	-1, %o0
	ba 		end
	nop

equal: 							! returns 0 if they were modifided same last

	mov 	0, %o0

end:

retl
nop