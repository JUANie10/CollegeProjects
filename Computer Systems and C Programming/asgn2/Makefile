CFLAGS=-Wall -Wextra -Werror -pedantic

math		:	math.o

	$(CC) -o math math.o -lm
math.o	:	math.c
	$(CC) -c math.c
clean	:
	rm -f math math.o
infer	:
	make clean; infer-capture -- make; inter-analyze -- make