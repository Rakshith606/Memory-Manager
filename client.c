#include <stdio.h>
#include "header.h"
int main()
{
    allocate(200);
    display_mem_map();
    char *a = (char *)mymalloc(0* sizeof(char));
	char *b = (char *)mymalloc(22 * sizeof(char));
	char *c =(char *)mymalloc(40* sizeof(char));
	display_mem_map();
	// printf("\n");
	char *d = (char *)mymalloc(20* sizeof(char));
	// //printf("\n");
	myfree(a);
	myfree(c);
	display_mem_map();
	// printf("\n");
	// display_mem_map();
	char *f = (char *)mymalloc(3* sizeof(char));
	myfree(d);
	myfree(f);
	myfree(b);
	display_mem_map();
	return 0;
}