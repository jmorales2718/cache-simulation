# makefile
# use to compile and test the assembler ASM for the STACK computer and
# its various components

DEBUG_FLAG= -DDEBUG -g -Wall
CFLAGS=-DDEBUG -g -Wall

.SUFFIXES: .cpp .o

.cpp.o:
	g++ $(CFLAGS) -c $<


cachetest: driver.o Cache.o Set.o Block.o 
	g++ -o cachetest driver.cpp Cache.o Set.o Block.o 

driver.o: driver.cpp

Block.o: Block.cpp Block.h

Set.o: Set.cpp Set.h Block.h

Cache.o: Cache.cpp Cache.h Set.h Block.h

clean:
	/bin/rm -f DCHECKER *.o core


