# ------------------------------------------------------------------------------
# FILE:         Makefile
#
# DESCRIPTION:  Makefile for S2017 CS202 Project 3: Matrix Math Program
#
# NOTES:        None
#
# ------------------------------------------------------------------------------

CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCES=matrix_math.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=matrix_math

all : $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o :
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm $(OBJECTS);\
		find . -name "$(EXECUTABLE)" ! -name "*.cpp" -type f -delete;\
		find . -name "gen" ! -name "*.cpp" -type f -delete

gen :
	$(CC) -Wall -std=c++11 gen.cpp -o gen
