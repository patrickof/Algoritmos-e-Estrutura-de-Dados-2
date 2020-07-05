COMPILER=g++

# Flags
CFLAGS=-ansi


# Files to compile
FILES_ONE=grafo
FILES_TWO=main

# Executable name
EXE=exe


all: compilar run

compilar: $(FILES_ONE).o $(FILES_TWO).o 
	$(COMPILER) $(FILES_ONE).o $(FILES_TWO).o -o $(EXE)

$(FILES_ONE).o: $(FILES_ONE).c $(FILES_ONE).h 
	$(COMPILER) -c $(FILES_ONE).c  -o $(FILES_ONE).o

$(FILES_TWO).o: $(FILES_TWO).c $(FILES_ONE).h 
	$(COMPILER) -c $(FILES_TWO).c  -o $(FILES_TWO).o

run:
	./$(EXE) 


clean:
	rm -rf *.o *~ $(EXE)


