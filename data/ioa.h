#pragma once
#include "jba.h"
#include "bitarray.h"
#include <iostream>
#define BLOCKOF(x) (x / blocksize)
#define INDEXOF(x) (x % blocksize)

/*
 * intobjectarray
 * It maps an integer id to an address
 * It does not allocate like an array,
 * It uses blocks to save CPU time and
 * reducing memory leaks by not having
 * to copy memory often and using
 * smaller blocks of memory.
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

int count() {
int cnt = 0;
for (int i = getnext(-1); i != -1; i = getnext(i)) {
cnt++;
}
return cnt;
}

//Add an object
T* add(T* t, int pos) {
if (allocmap.exists(BLOCKOF(pos))) {
int index = getindex(pos);
map[BLOCKOF(pos)][INDEXOF(pos)] = t;
available_map.add(pos);
} else {
alloc(BLOCKOF(pos));
add(t, pos);
}
}
//See if an object exists by its id
bool exists(int pos) {
//We will just used available_map to see if it exists or not
return (available_map.exists(pos));
}
//Get an object by its id
T* get(int pos) {
//We need to see if any object exists at that position
if (available_map.exists(pos)) {
//Return the value if it exists
return map[BLOCKOF(pos)][INDEXOF(pos)];
} else {
//Return null if the value does not exist
return 0ULL;
}
}
//Remove an object by its id
void remove(int pos) {
//We do not have to do anything fancy, just mark the available_map as empty
available_map.remove(pos);
}
//Allocate a block by its absolute block number
void alloc(int blocknum) {
if (allocmap.exists(blocknum)) return;
//Create a new map of T
T*** newmap = new T**[++allocated_blocks]; //We increment allocated_blocks here
int cur, relblk, curnewblk;
cur = -1;
relblk = 0;
curnewblk = 0;
allocmap.add(blocknum); // Tell the allocmap that we have allocated a new block
while ((cur = getnextalloc(cur)) != -1) {
if (cur != blocknum) {
newmap[curnewblk++] = map[relblk++];
} else {
newmap[curnewblk++] = new T*[blocksize];
}

}
delete map;
map = newmap;
}
//Using a value, getindex will determine the block
//	that the value is in
//Returns -1 if the block does not exist
int getindex(int i) {
//We will return -1 if allocmap says the block isn't allocated
if (!allocmap.exists(BLOCKOF(i))) return -1;
//Get the absolute block
int block = BLOCKOF(i);

//iter counts the number of iterations it takes until block == curblock,
//					the relative block
int iter = 0;
int curblock = 0;

while (curblock != block && (curblock = getnextalloc(curblock)) != -1) { iter++; }
return iter;
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
return available_map.getnext(last);
/*int value, currentblock;
value = last;
currentblock = BLOCKOF(value);

while (1) {
if (BLOCKOF(value) > currentblock) {
currentblock = getnextalloc(currentblock);
if (currentblock == -1) return -1;
} else {
value++;
if (allocmap.exis
*/
}

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
