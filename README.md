# The Tiny Machine Project
## Tiny description

This project builds:
1. A tiny virtual processor. 
2. A machine code that can be executed by the processor.
3. An assembly language that can be compiled into the machine code. 
4. A higher level programming language that compiles into the assembly language. 
5. A yet higher level programming language. 
6. And so on...

The goal is to play with the boot strapping process. By which a limited set of
computing capability is used to create a full fledge high level programming 
language. 

For a more elaborate description see the _General description_ section below. 
For a detail architectural overview consult the github wiki (so far non-existent).

## Build instruction 

From the terminal navigate to the project folder.

* To build the executable run:
    ```
    make
    ```
* To build, cleanup and run:
    make run
* To build the unit test version and run:
    make test
* To build the unit test version with additional debug outputs:
    make dtest
* To cleanup:
    make clean

## Folder structure

* All include files (.h) are in the `include` folder, except for the
 `unit_tests.h` which is in the `unit_tests` folder. 
* All source files (.c) are in the `src` folder, except for the
 `unit_tests.c` which is in the `unit_tests` folder. 
* Output object files are created in the `obj` folder. 
* The executable files are created in the project home. 

## General description

*under construction*