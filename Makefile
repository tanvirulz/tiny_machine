#sorry for this mess. Definitely need to write proper makefile.

default: mem reg ttm.c 
	gcc -o run memory.o registers.o ttm.c -I.
test: unit_tests.c 
	gcc -c -o unit_tests.o unit_tests.c -I.

mem: memory.c 
	gcc -c -o memory.o memory.c -I.

reg: registers.c 
	gcc -c -o registers.o registers.c -I.

proc: processor.c 
	gcc -c -o processor.o processor.c -I.


run: default
	./run
	rm -f *.o
	
clean: 
	rm -f run
	rm -f *.o
	