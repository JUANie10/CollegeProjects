CFLAGS=-Wall -Wextra -Werror -Wpedantic
CC=clang $(CFLAGS)

sorting		:	sorting.o bubble.o shell.o quick.o binary.o
	$(CC) -o sorting sorting.o bubble.o shell.o quick.o binary.o -lm
sorting.o	:	sorting.c
	$(CC) -c sorting.c
bubble.o	:	bubble.c
	$(CC) -c bubble.c
shell.o	  :	shell.c
	$(CC) -c shell.c
quick.o	  :	quick.c
	$(CC) -c quick.c
binary.o	:	binary.c
	$(CC) -c binary.c
all :
	make
clean	:
	rm -f sorting sequence.o sorting.o bubble.o shell.o quick.o binary.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
valgrind :
	make
	valgrind --leak-check=full ./sorting -A
