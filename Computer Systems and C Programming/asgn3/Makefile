CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)

sequence		:	sequence.o sieve.o bv.o
	$(CC) -o sequence sequence.o sieve.o bv.o -lm
sequence.o	:	sequence.c
	$(CC) -c sequence.c
sieve.o	:	sieve.c
	$(CC) -c sieve.c
bv.o	:	bv.c
	$(CC) -c bv.c
clean	:
	rm -f sequence sequence.o sieve.o bv.o
infer	:
	make  clean; infer -capture  -- make; infer -analyze  -- make
