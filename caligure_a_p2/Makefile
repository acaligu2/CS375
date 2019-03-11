#
# Specifiy the target
make:	program2

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
program2:		program2.o extendedHeapFunctions.o Contestant.o
	g++ program2.o Contestant.o extendedHeapFunctions.o -o program2

program2.o:		program2.cpp
	g++ -c program2.cpp

extendedHeapFunctions.o: extendedHeapFunctions.cpp
	g++ -c extendedHeapFunctions.cpp

Contestant.o: Contestant.cpp Contestant.h
	g++ -c Contestant.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o program2
