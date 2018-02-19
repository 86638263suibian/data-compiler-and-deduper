#
# Makefile template for CSE 30 -- PA4
# You should not need to change anything in this file.
#
# XXX DO NOT EDIT
#

TARGET		= pa4

HEADERS		= pa4.h pa4Strings.h

C_SRCS		= main.c sortFiles.c mergeFiles.c pa4Globals.c buildData.c \
		  displayOutput.c compareLines.c compareLinesIgnoreCase.c

ASM_SRCS	= timeCompare.s revTimeCompare.s filenameCompare.s \
		  revFilenameCompare.s

C_OBJS		= $(C_SRCS:.c=.o)
ASM_OBJS	= $(ASM_SRCS:.s=.o)
OBJS		= $(C_OBJS) $(ASM_OBJS)

TEST_BINS	= testsortFiles testfilenameCompare testrevFilenameCompare \
		  testtimeCompare testrevTimeCompare


#
# Relevant man pages:
#
# man gcc
# man as
# man lint
#

GCC		= /usr/ccs/bin/gcc
ASM		= $(GCC)
LINT		= lint

GCC_FLAGS	= -c -g -Wall -D__EXTENSIONS__  -std=c99
LINT_FLAGS1	= -c -err=warn
LINT_FLAGS2	= -u -err=warn
ASM_FLAGS	= -c -g
LD_FLAGS	= -g -Wall


#
# Standard rules
#

.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Linting each C source file separately ..."
	$(LINT) $(LINT_FLAGS1) $<
	@echo ""
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Simply have our project target be a single default "a.out" executable.
#

$(TARGET):	$(OBJS)
	/bin/rm -f test*.o test*.ln
	@echo "2nd phase lint on all C source files ..."
	$(LINT) $(LINT_FLAGS2) *.ln
	@echo ""
	@echo "Linking all object modules ..."
	$(GCC) -o $(TARGET) $(LD_FLAGS) $(OBJS)
	@echo ""
	@echo "Done."

${C_OBJS}:      ${HEADERS}

clean:
	@echo "Cleaning up project directory ..."
	/usr/bin/rm -f *.o a.out *.ln core $(TARGET) $(TEST_BINS)
	@echo ""
	@echo "Clean."

new:
	make clean
	make

testsortFiles: test.h pa4.h sortFiles.o testsortFiles.o pa4Globals.o \
	filenameCompare.o timeCompare.o revFilenameCompare.o revTimeCompare.o
	@echo "Compiling testsortFiles.c"
	$(GCC) -D__EXTENSIONS__ -std=c99 -o testsortFiles testsortFiles.o \
	sortFiles.o pa4Globals.o filenameCompare.o timeCompare.o \
	revFilenameCompare.o revTimeCompare.o
	@echo "Done."

testfilenameCompare: test.h pa4.h testfilenameCompare.o filenameCompare.o \
	pa4Globals.o
	@echo "Compiling testfilenameCompare.c"
	$(GCC) -D__EXTENSIONS__ -std=c99 -o testfilenameCompare pa4Globals.o \
	testfilenameCompare.o filenameCompare.o
	@echo "Done."

testrevFilenameCompare: test.h pa4.h testrevFilenameCompare.o \
	revFilenameCompare.o pa4Globals.o
	@echo "Compiling testrevFilenameCompare.c"
	$(GCC) -D__EXTENSIONS__ -std=c99 -o testrevFilenameCompare \
	pa4Globals.o testrevFilenameCompare.o revFilenameCompare.o
	@echo "Done."

testtimeCompare: test.h pa4.h testtimeCompare.o timeCompare.o pa4Globals.o
	@echo "Compiling testtimeCompare.c"
	$(GCC) -D__EXTENSIONS__ -std=c99 -o testtimeCompare pa4Globals.o \
	testtimeCompare.o timeCompare.o
	@echo "Done."

testrevTimeCompare: test.h pa4.h testrevTimeCompare.o \
	revTimeCompare.o pa4Globals.o
	@echo "Compiling testrevTimeCompare.c"
	$(GCC) -D__EXTENSIONS__ -std=c99 -o testrevTimeCompare pa4Globals.o \
	testrevTimeCompare.o revTimeCompare.o
	@echo "Done."
