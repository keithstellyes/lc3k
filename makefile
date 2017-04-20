all: lc3ksim.o delet.c instructions.h test
	gcc -DINSTRUCTIONS_DBB delet.c -o a.out lc3ksim.o

test: lc3ksim.o tests.c
	gcc -DINSTRUCTIONS_DBB lc3ksim.o tests.c -o tests.out
	@echo ...TESTING...
	@echo .............
	@./tests.out ||	echo FAIL
	@echo .............

lc3ksim.o: lc3ksim.c lc3ksim.h instructions.h
	gcc lc3ksim.c -c


