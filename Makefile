all: wget_parser.o
	gcc -o wget_parser wget_parser.o -lm

wget_parser.o: wget_parser.c
	gcc -Wall -Werror -g -c wget_parser.c  -lm
	
clean:
	rm -f *.o
	rm -f wget_parser