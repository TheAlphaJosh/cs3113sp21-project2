all: project2

project1: project2.c
	gcc -o project2 project2.c

clean: 
	rm -f project2
