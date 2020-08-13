CFLAGS=-Wall -Wextra -Werror -Wpedantic
CC=clang $(CFLAGS)

newspeak		:	newspeak.o gs.o ll.o hash.o speck.o bf.o parser.o bv.o
	$(CC) -o newspeak newspeak.o gs.o ll.o hash.o speck.o bf.o parser.o bv.o -lm
newspeak.o	:	newspeak.c
	$(CC) -c newspeak.c
gs.o	:	gs.c
	$(CC) -c gs.c
ll.o	:	ll.c
	$(CC) -c ll.c
hash.o	:	hash.c
	$(CC) -c hash.c
speck.o	:	speck.c
	$(CC) -c speck.c
bf.o	:	bf.c
	$(CC) -c bf.c
parser.o	:	parser.c
	$(CC) -c parser.c
bv.o	:	bv.c
	$(CC) -c bv.c
all :
	make
clean	:
	rm -f newspeak newspeak.o gs.o ll.o hash.o speck.o bf.o parser.o bv.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
valgrind :
	make
	valgrind --leak-check=full ./newspeak 
