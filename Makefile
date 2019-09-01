efile = tema2
ofile = main.o task1.o task2.o task3.o tree.o waitList.o addrList.o

build: $(ofile)
	gcc $(ofile) -o $(efile) -lm -g
$@.o: $@.c $@.h
	gcc -c $@.c
run: $(efile)
	./$(efile)
clean: 
	rm -f $(efile) $(ofile)
