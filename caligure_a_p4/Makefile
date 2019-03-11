#
# Specifiy the target
make:	program4

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
program4:	program4.o PriceProblem.o
	g++ program4.o PriceProblem.o -o program4

program4.o:	program4.cpp
	g++ -c program4.cpp

PriceProblem.o:	PriceProblem.cpp PriceProblem.h
	g++ -c PriceProblem.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o program4
