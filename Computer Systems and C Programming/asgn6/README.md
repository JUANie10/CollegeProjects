There are 4 Null Dereference errors when I ran the make infer but I did not know how to fix it.
I tried reseaching online on how to fix it but came up short. I freed all the calloced spaces and
made sure that none of those calloced had anything in them afterwards by comparing it with 
NULL

In order to use encode.c and decode.c,  It is compiled using the makefile. 
Make clean removes the created files. Infer makes provides the user with errors and warnings.
Valgrind checks for memory leaks and reports any memory leaks. 

Speaking of valgrind checks, I pulled at elast 3 all nighters to fix and revise the memory leaks 
and my code but came up short. I hoenstly don't think I can fix any more memory leaks
because when I try to debug them, the program throws segments faults everytime. Whenever
I try to free a node after it was used, it would seg fault. 

I had a hard time trying to decompress the file. I couldn't solve the memory leaks. 
I stayed up for the past 3 days at least trying to work on this despite my other major classes
This was truly challenging. Thank you for being a TA this quarter. I learned alot and truly
appreciate it.

You can use my program by typing ./encode and decode and inputting flags such as -v to get
the stats of the program. -i and some input for the infile and -o for the outfile.



