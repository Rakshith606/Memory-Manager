#ifndef header_h
#define header_h

extern char *p;
extern int size;
void allocate(int n); //function to allocate memory for the global array p, n number of bytes long.

void* mymalloc(int size); //function to allocate a block of size "size" from p

void myfree(void *b); //free the block pointed to by the parameter

void print_book(); // prints bytes used by the bookkeeping structure

void display_mem_map(); // print the memory array p in the following format

#endif
