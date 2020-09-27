#comando per compilare
CC = g++
LINK = g++
CFLAGS = -c -std=c++11
COMPILE = $(CC) $(CFLAGS)

OBJ = sudoku.o

all: app
#lancia l'app in automatico
	./$<

sudoku.o: sudoku.cpp
	$(COMPILE) sudoku.cpp -o sudoku.o

#link all into an executable
app: $(OBJ)
#	linkiamo tutti gli object e la grafica SFML
	$(LINK) $(OBJ) -o app $(LINK_SFML)

#clean target
.PHONY: clean

clean:
	rm -rf *.o app
