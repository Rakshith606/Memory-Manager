#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>  //for INT_MAX used in mymalloc
typedef struct book{
	struct book *next;  // pointer to next memory block
	int allocated;		// denotes how many bytes a given memory block is allocated
	int isfree;			//denotes if a memory location is free or not
}book;
char *p;
int size;
//allocate() allocates main book for given size n,free size available is n-sizeof(book)
void allocate(int n){
	size=n;
	p=(char *)malloc(sizeof(char)*n);
	book *main_block=(book *)(p);
	main_block->next=NULL;
	main_block->isfree=1;
	size=size-sizeof(book);
	main_block->allocated=size;
}
void* mymalloc(int size){
	book *main_block=(book *)(p);
	book *block=main_block;
	book *pres=NULL;
	int best=INT_MAX;
	while(block){
		int check=(block->allocated-size);
		if(block->isfree==1 && check<=best && check>=0){  //get the best fit
			pres=block;						//pres points to that block whose difference 
			best=block->allocated-size;		//is as small as possible
		}
		if(best<0)  //if requested size is more than 1st found free block reset best and search again 
			best=INT_MAX;
		block=block->next;
	}                        
	if(best==INT_MAX || pres==NULL)  //no block found
		return NULL;
	int check=pres->allocated-(sizeof(book)+size);
	if(check<=0){  //if available free space is too small to keep a book return the entire block
		pres->isfree=0;
		return pres+1;
	}
	book *mem_block=(book *)((char *)pres+size+sizeof(book));//go to required location
	mem_block->allocated=pres->allocated-(size+sizeof(book));
	mem_block->isfree=1;					//split the free block 
	mem_block->next=pres->next;
	pres->allocated=size;
	pres->isfree=0;
	pres->next=mem_block;
	return pres+1; //Go to Starting address of Memory Location
}
void display_mem_map(){
	book *disp=(book *)(p);
	int cumulative=0;
	while(disp){
		printf("%d\t%d\t Book\n",cumulative,(int)sizeof(book));
		cumulative+=sizeof(book);
		printf("%d\t%d\t %s\n",cumulative,disp->allocated,(disp->isfree==0)?"Allocated":"Free");
		cumulative+=disp->allocated;
		disp=disp->next;
		}
	printf("\n");
}
void myfree(void *b){
	if(b){//if b is a valid pointer
		book *block=(book *)((char *)b-sizeof(book)); //access the book keeping structure of pointer
		if(block->isfree) // if already free
			return;
		block->isfree=1; 
		book *mem_block=(book *)(p); //get the first book 
		while(mem_block->next){   //mem block can never be NULL since there is atleast 1 Book present
			book *adj_block=mem_block->next;
			if((adj_block)&&(adj_block->isfree && mem_block->isfree)){ //while consecutive blocks are free
				mem_block->next=adj_block->next;						// keep merging
				mem_block->allocated+=adj_block->allocated+sizeof(book);// mem_block is not moved 
			}															//till next block is not free
			else//move to next block if and only if one of the block is not free
				mem_block=adj_block; 
		}
	}
}
void print_book(){
	printf("Size Of Book Keeping Structure %d\n",(int)sizeof(book));
}