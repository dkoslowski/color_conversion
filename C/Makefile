#
# Simple Makefile
#
# Author: Dennis Koslowski <dennis.koslowski@gmx.de>
# Date:   2020-01-13
#

# Extra flags to give to the C compiler.
CFLAGS = -g

# Extra flags to give to the C++ compiler.
CXXFLAGS =

# Extra flags to give to the C preprocessor and programs that use it
# (the C and Fortran compilers).
CPPFLAGS = -Wall -Wextra

# Extra flags to give to compilers when they are supposed to invoke the
# linker, ‘ld’, such as -L. Libraries (-lfoo) should be added to the
# LDLIBS variable instead.
LDFLAGS =

# Library flags or names given to compilers when they are supposed to
# invoke the linker, ‘ld’. Non-library linker flags, such as -L,
# should go in the LDFLAGS variable.
LDLIBS = -lm

# All objects
OBJS = color_conversion.o rgb_hsv.o
# All programs
PROGS = color_conversion_test

default: $(OBJS) $(PROGS)

color_conversion_test: color_conversion_test.o color_conversion.o
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^

clean:
	rm -f $(OBJS) $(PROGS) *~
