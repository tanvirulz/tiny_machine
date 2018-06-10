# Sorry for the super messy version of makefile (  that works for now. )
# Definitely have to learn how to write a smarter one.

CC=gcc
IFLAGS=-I./include -I./unit_tests

TDIR=./unit_tests
SDIR=./src
ODIR=./obj


# nominal compile
default: mkobjdir nondeb mem reg  proc $(SDIR)/main.c 
	gcc -o run $(ODIR)/memory.o $(ODIR)/registers.o  $(ODIR)/debug.o $(ODIR)/processor.o $(SDIR)/main.c $(IFLAGS)

# if not exists, create obj directory to avoid error (output directory not found)!
mkobjdir: 
	mkdir -p obj
# run the testsuit *SKIP* the debug outputs
test: mkobjdir nondeb utest mem reg  proc $(SDIR)/main.c 
	gcc -D TEST_MODE  -o run_test $(ODIR)/memory.o $(ODIR)/registers.o $(ODIR)/unit_tests.o $(ODIR)/debug.o $(ODIR)/processor.o $(SDIR)/main.c $(IFLAGS)
	./run_test

# run the testsuit *PRINT* the debug outputs
dtest: mkobjdir deb utest mem reg  proc $(SDIR)/main.c 
	gcc -D TEST_MODE  -o run_test $(ODIR)/memory.o $(ODIR)/registers.o $(ODIR)/unit_tests.o $(ODIR)/debug.o $(ODIR)/processor.o $(SDIR)/main.c $(IFLAGS)
	./run_test

# compile debug that renders is senile
nondeb: mkobjdir $(SDIR)/debug.c 
	$(CC) -c -o $(ODIR)/debug.o $(SDIR)/debug.c $(IFLAGS)

# debug that you compile when you actually need it! 
deb: mkobjdir $(SDIR)/debug.c 
	$(CC) -c -D DEBUG_MODE -o $(ODIR)/debug.o $(SDIR)/debug.c $(IFLAGS)
 
utest: mkobjdir $(TDIR)/unit_tests.c 
	$(CC) -c -o $(ODIR)/unit_tests.o $(TDIR)/unit_tests.c $(IFLAGS)

mem: mkobjdir $(SDIR)/memory.c 
	$(CC) -c -o $(ODIR)/memory.o $(SDIR)/memory.c $(IFLAGS)

reg: mkobjdir $(SDIR)/registers.c 
	$(CC) -c -o $(ODIR)/registers.o $(SDIR)/registers.c $(IFLAGS)


proc: mkobjdir $(SDIR)/processor.c 
	$(CC) -c -o $(ODIR)/processor.o $(SDIR)/processor.c $(IFLAGS)

run: default
	./run

clean: 
	rm -f run
	rm -f $(ODIR)/*.o
	rm -f run_test