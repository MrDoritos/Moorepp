#pragma once
#include "jba.h"
#include "bitarray.h"
#include <iostream>


/*
 * intobjectarray
 * It maps an integer id to an address
 * It does not allocate like an array,
 * It uses blocks to save CPU time and
 * reducing memory leaks by not having
 * to copy memory often and using
 * smaller blocks of memory.
 *
 */
template<class T>
class intobjectarray {
public:
intobjectarray() {}
intobjectarray(size_t blocksize) {
this->blocksize = (blocksize > 0 ? blocksize : 2);
map = new T**[1];
map[0] = new T*[blocksize];
allocated_blocks = 1;
allocmap.add(0);
available_map = jaggedbitarray();
}

//Add an object
T* add(T* t, int pos);
//See if an object exists by its id
bool exists(int pos);
//Get an object by its id
T* get(int pos);
//Remove an object by its id
void remove(int pos);
//Allocate a block by its absolute block number
void alloc(int blocknum);
//Using a value, getindex will determine the block
//	that the value is in
//Returns -1 if the block does not exist
int getindex(int i);
//Retrieves the next value from allocmap
//Returns -1 if there are no more blocks
//Should probably not be recursive
int getnextalloc(int last);
//Retrieves the next value from any block
//Returns -1 if there are no values left
int getnext(int last);

//This tells us how many blocks we have allocated in total
int allocated_blocks;

//This tells us which blocks have been allocated
bitarray allocmap;

//This tells us which items exist
jaggedbitarray available_map;

//This tells us the blocksize;
size_t blocksize;

//This is the 2D array of pointers,	the first index gives us the block,
//					the second index gives us a pointer
//However, the allocmap must be used to find the relative index, because
//					usused blocks are not allocated yet
//					to save heap space
//'available_map' tells us which items are not null
T*** map;
};
