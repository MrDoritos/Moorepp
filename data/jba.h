#include <stdlib.h>
#include <iostream>
#include <bitset>
#include "bitarray.h"
#pragma once
#define BLOCKSIZE (sizeof(size_t) * 8)
#define BLOCKOF(x) (x / (BLOCKSIZE))

class jaggedbitarray {
public:
jaggedbitarray() {
allocmap = bitarray();
allocmap.add(0);
allocated_blocks = 1;
map = new size_t[1];
map[0] = 0ULL;
}
//Counting
int count() {
int cnt = 0;
for (int i = getnext(-1); i != -1; i = getnext(i)) {
cnt++;
}
return cnt;
}


//Adds a value
void add(int i) {
//See if we have the block allocated
if (allocmap.exists(BLOCKOF(i))) {
//Get the relative block the value will go in
int index = getindex(i);
map[index] |= (1ULL << (i % BLOCKSIZE));
} else {
//We need to allocate that block
alloc(BLOCKOF(i));
add(i);
}
}

//Removes a value
void remove(int i) {
if (allocmap.exists(BLOCKOF(i))) {
int index = getindex(i);
map[index] &= ~(1ULL << (i % BLOCKSIZE));
}
}

//See if a value exists
bool exists(int i) {
if (allocmap.exists(BLOCKOF(i))) {
int index = getindex(i);
return ((map[index] & (1ULL << (i % BLOCKSIZE))) != 0);
} else {
return false;
}
}

//Allocate a block by its absolute block number
void alloc(int blocknum) {
if (allocmap.exists(blocknum)) return; //If the block already exists, return
size_t *newmap = new size_t[++allocated_blocks]; //We increment alloc... here
int cur = -1; //The current absolute block on map
int relblk = 0; //The current relative block on map
int curnewblk = 0; //The current block on newmap
allocmap.add(blocknum); // Tell the allocmap that we have a new block allocated
//We need to know the block that is not allocated, which is blocknum
while ((cur = getnextalloc(cur)) != -1) {
if (cur != blocknum) {
//Copy the old block
newmap[curnewblk++] = map[relblk++];
} else {
//Allocate the new block
newmap[curnewblk++] = 0ULL;
}
}
delete map; // Free the old map
map = newmap; // Copy the address

}

//Using a value, getindex will determine the block
//	that the value is in
//Returns -1 if the block does not exist
int getindex(int i) {
//Get the absolute block
int block = BLOCKOF(i);

//Check if the block exists in the allocation table
if (allocmap.exists(block)) {

//Counts the number of iterations until block == curblock
int iter = 0;
int curblock = 0;
while (curblock != block && (curblock = getnextalloc(curblock)) != -1) { iter++; }
//Return the relative index for the absolute block
return iter;
} else {
//Block is not even allocated
return -1;
}

}

//Retrieves the next value from allocmap
//Returns -1 if there are no more blocks
//Should probably not be recursive
int getnextalloc(int last) {
return (allocmap.exists(last + 1) ? last + 1 : (allocmap.getcapacity() < (last + 1) ? -1 : getnextalloc(last + 1)));
}

//Retrieves the next value from any block
//Returns -1 if there are no values left
int getnext(int last) {
//if (allocmap.exists(last / BLOCKSIZE)) { // Checks if the block is even allocated
//If we get a negative value, that means we are fucked in some cercumstances
if (last == -1) {
if (exists(0)) {
return 0;
} else {
return getnext(0);
}
}
//int block = last / BLOCKSIZE; // The block 'last' is in
int value = last;
int currentblock = BLOCKOF(value);

//if (BLOCKOF(value) >= allocated_blocks && !allocmap.exists(BLOCKOF(value))) return -1;

while (1) {
if (BLOCKOF(value) > currentblock)
{
//If the block of value is greater than the set currentblock, try to increment it
currentblock = getnextalloc(currentblock);
//If there are no new blocks, that must mean there are no new values, return -1
if (currentblock == -1)
return -1;
} else {
//Increment value if we are in block
value++;
//If the value exists, return it
if (allocmap.exists(BLOCKOF(value)) && (map[BLOCKOF(value)] & (1ULL << (value % BLOCKSIZE))) != 0) {
return value;
} else {
//If it doesn't, keep looping until we don't have any more blocks
}

}


}


//} else {
//return -1;
//}
}

//The map
size_t *map;
//Tells us how many blocks have been allocated
int allocated_blocks;
//Tells us which blocks have been allocated
bitarray allocmap;
};
