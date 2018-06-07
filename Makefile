ttm: memory.c ttm.c registers.c 
	gcc -o run memory.c registers.c ttm.c -I.
run: ttm
	./run
clean: 
	rm run
	