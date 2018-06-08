#sorry for this mess. Definitely need to write proper makefile.

default: mem reg  proc main.c 
	gcc -o run memory.o registers.o processor.o main.c -I.

test: utest mem reg  proc main.c 
		gcc -D TEST_MODE -o run_test memory.o registers.o unit_tests.o  processor.o main.c -I.
		./run_test

utest: unit_tests.c 
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
	rm -f run_test 