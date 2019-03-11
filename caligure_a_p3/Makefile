#
# Specifiy the target
make:	submission

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
submission:		program3.o PriceProblem.o
	g++ program3.o PriceProblem.o -o submission

program3.o:		program3.cpp
	g++ -c program3.cpp

PriceProblem.o:	PriceProblem.cpp PriceProblem.h
	g++ -c PriceProblem.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o submission
