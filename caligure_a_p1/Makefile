#
# Specifiy the target
make:	program1

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
program1:		maxProfit.o PriceProblem.o
	g++ maxProfit.o PriceProblem.o -o program1

maxProfit.o:		maxProfit.cpp
	g++ -c maxProfit.cpp

PriceProblem.o:	PriceProblem.cpp PriceProblem.h
	g++ -c PriceProblem.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o program1
