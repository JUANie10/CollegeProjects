There are 4 Null Dereference errors when I ran the make infer but I did not know how to fix it.
I tried reseaching online on how to fix it but came up short. I freed all the calloced spaces and
made sure that none of those calloced had anything in them afterwards by comparing it with 
NULL

 In order to use sorting.c, it is compiled using the makefile. The command make creates the 
 bubble.o, shell.o, quick.o, binary.o and sorting terminal file. Make clean removes the created 
 files. Infer makes provides the user with errors and warnings. Valgrind checks for memory 
 leaks and reports any memory leaks. 

You can use my program by typing ./sorting and inputing flags such as -b which would sort the
array using bubble sort, -s using shell sort, -q using quick sort, -i using binary insertion sort
,-p (integer) to print that many elements, -r (integer) to set the seed and -n (integer) to set the 
size of the array. The default for print is 100, seed is 8222022 and size is 100.

The output will be presented to you in gitbash.
