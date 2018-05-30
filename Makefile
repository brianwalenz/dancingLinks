

CC   =  g++7
OPTS = -O3

dancingLinks: dancingLinks.o boardFrame.o hexomino.o
	$(CC) $(OPTS) -std=c++11 -o dancingLinks dancingLinks.o boardFrame.o hexomino.o


dancingLinks.o: dancingLinks.C boardFrame.H dancingLinks.H hexomino.H utility.H
	$(CC) $(OPTS) -std=c++11 -c -o dancingLinks.o dancingLinks.C

boardFrame.o: boardFrame.H boardFrame.C hexomino.H utility.H
	$(CC) $(OPTS) -std=c++11 -c -o boardFrame.o boardFrame.C

hexomino.o: hexomino.H hexomino.C
	$(CC) $(OPTS) -std=c++11 -c -o hexomino.o hexomino.C


clean:
	rm -f *.o dancingLinks

