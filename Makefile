# Compiler
CXX = g++
CXXFLAGS = -Wall

# Default target
all: scanner cmos

# Build scanner from lex file
scanner: lex.yy.c
	$(CXX) lex.yy.c -o scanner

# Generate lex.yy.c from cmos.l
lex.yy.c: cmos.l
	lex cmos.l

# Build cmos program
cmos: cmos.cpp
	$(CXX) $(CXXFLAGS) cmos.cpp -o cmos

run:
	./PlagarismDetector Examples/Examples/

# Cleans all unneeded files
clean:
	rm -f lex.yy.c scanner cmos *.txt