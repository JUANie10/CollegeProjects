CFLAGS=-Wall -Wextra -Werror -pedantic

lrc		:	lrc.o

	$(CC) -o lrc lrc.o
lrc.o	:	lrc.c
	$(CC) -c lrc.c
clean	:
	rm -f lrc lrc.o
infer	:
	make clean; infer-capture -- make; inter-analyze -- make