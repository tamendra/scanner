all: SCAN
SCAN: removal utility.o config.o SymbolTable.o TransitionGraph.o Scanner.o main.o
	g++ -o scan main.o utility.o config.o SymbolTable.o TransitionGraph.o Scanner.o
main.o: main.cpp
	g++ -c -g main.cpp
config.o: config.cpp
	g++ -c -g config.cpp
utility.o: utility.cpp
	g++ -c -g utility.cpp
SymbolTable.o: SymbolTable.cpp
	g++ -c -g SymbolTable.cpp
TransitionGraph.o: TransitionGraph.cpp
	g++ -c -g TransitionGraph.cpp
Scanner.o: Scanner.cpp
	g++ -c -g Scanner.cpp
removal:
	rm -f *.o