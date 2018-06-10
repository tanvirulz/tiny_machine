#sorry for this mess. Definitely need to write proper makefile.

# nominal compile
default: mem reg  proc main.c 
	gcc -o run memory.o registers.o processor.o main.c -I.

# run the testsuit *SKIP* the debug outputs
test: nondeb utest mem reg  proc main.c 
		gcc -D TEST_MODE  -o run_test memory.o registers.o unit_tests.o debug.o processor.o main.c -I.
		./run_test

# run the testsuit *PRINT* the debug outputs
dtest: deb utest mem reg  proc main.c 
		gcc -D TEST_MODE  -o run_test memory.o registers.o unit_tests.o debug.o processor.o main.c -I.
		./run_test

# compile debug that renders is senile
nondeb: debug.c 
	gcc -c -o debug.o debug.c -I.
	
# debug that you compile when you actually need it! 
deb: debug.c 
	gcc -c -D DEBUG_MODE -o debug.o debug.c -I.

utest: unit_tests.c 
	gcc -c -o unit_tests.o unit_tests.c -I.

mem: memory.c 
	gcc -c -o memory.o memory.c -I.

reg: registers.c 
	gcc -c -o registers.o registers.c -I.

proc: processor.c 
	gcc -c -o processor.o processor.c -I.

# nominal run
run: default
	./run
	rm -f *.o
	
clean: 
	rm -f run
	rm -f *.o
	rm -f run_test 