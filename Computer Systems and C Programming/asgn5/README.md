There are 6 Null Dereference errors when I ran the make infer but I did not know how to fix it.
I tried reseaching online on how to fix it but came up short. I freed all the calloced spaces and
made sure that none of those calloced had anything in them afterwards by comparing it with 
NULL

In order to use newspeak.c, It is compiled using the makefile. The command make creates 
newspeak.o, ll.o, hash.o, pareser.o, gs.o, bf.o, bv.o, speck.o and the newspeak terminal file.
Make clean removes the created files. Infer makes provides the user with errors and warnings.
Valgrind checks for memory leaks and reports any memory leaks. 

Speaking of valgrind checks, I pulled at elast 3 all nighters to fix and revise the memory leaks 
and my code but came up short. I hoenstly don't think I can fix any more memory leaks
because when I try to debug them, the program throws segments faults everytime. Whenever
I try to free a node after it was used, it would seg fault. 

You can use my program by typing ./newspeak and inputting flags such as -s in order to get 
the stats of the program. -h (size) to set the size of the hashfilter -f (size) in order to set the size
of the bloomfilter. -m to set move_to_front to be true. -b to not set move_to_front.  The default
size of the hashtable 10000 and the default bloomfilter size would be 1048576. 

The output will be presented to you in gitbash.

