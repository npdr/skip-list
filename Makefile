all:
	gcc -c main.c skiplist.c linkedlist.c
	gcc main.o skiplist.o linkedlist.o -o main

run:
	./main

ll:
	gcc -c linkedlistmain.c linkedlist.c
	gcc linkedlistmain.o linkedlist.o -o ll
	./ll