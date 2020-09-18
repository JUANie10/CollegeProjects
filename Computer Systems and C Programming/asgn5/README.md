
In order to use newspeak.c, It is compiled using the makefile. The command make creates 
newspeak.o, ll.o, hash.o, pareser.o, gs.o, bf.o, bv.o, speck.o and the newspeak terminal file.
Make clean removes the created files. Infer makes provides the user with errors and warnings.
Valgrind checks for memory leaks and reports any memory leaks. 

You can use my program by typing ./newspeak and inputting flags such as -s in order to get 
the stats of the program. -h (size) to set the size of the hashfilter -f (size) in order to set the size
of the bloomfilter. -m to set move_to_front to be true. -b to not set move_to_front.  The default
size of the hashtable 10000 and the default bloomfilter size would be 1048576. 

The output will be presented to you in gitbash.

