
CFLAGS=-Wall -Wextra -Werror -Wpedantic -std=c99
#CC=clang $(CFLAGS)

all		:
	make decode
	make encode
decode	: decode.o word.o trie.o io.o
	$(CC) -o decode decode.o word.o trie.o io.o -lm
encode	: encode.o word.o trie.o io.o
	$(CC) -o encode encode.o word.o trie.o io.o -lm
encode.o	:	encode.c
	$(CC) -c encode.c
decode.o	: decode.c
	$(CC) -c decode.c
word.o		: word.c
	$(CC) -c word.c
trie.o		: trie.c
	$(CC) -c trie.c
io.o		: io.c
	$(CC) -c io.c
clean:
	rm -f decode encode decode.o encode.o word.o trie.o io.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
