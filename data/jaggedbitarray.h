#include <stdlib.h>
#include "bitarray.h"
#define BLOCKSIZE sizeof(size_t) * 8

class jaggedbitarray {
public:
jaggedbitarray() {
allocmap = bitarray();
allocmap.add(0);
allocated_blocks = 1;
map = new size_t[1];
}
bool exists(int i) {
// if allocmap says the block exists, get the blocks index
// if the block contains the value
	//See if the block exists
if (allocmap.exists(i / BLOCKSIZE)) {
int index = getindex(i);
return ((map[index] & (1ULL << (i % BLOCKSIZE))) != 0);
} else {
return false;
}
}
void add(int i) {
if (allocmap.exists(i / BLOCKSIZE)) {
int index = getindex(i);
map[index] |= (1ULL << (i % BLOCKSIZE));
} else {
alloc(i / BLOCKSIZE);
add(i);
}
}
void remove(int i);
private:
bitarray allocmap;
size_t *map;
int getnext(int last) {
int cap = allocmap.getcapacity();
while (!(allocmap.exists(last)) && last <= cap) last++;
return (last <= cap ? last : -1);
}
int getindex(int i) {
if (i / BLOCKSIZE == 0) return 0;
int absolute_blk = BLOCKSIZE;
int index = -1;
int iter = -1;
while ((index = getnext(index)) != -1) {
iter++;
}
return iter;
}
int allocated_blocks;
void alloc(int blocknum) { // int blocknum : The block to allocate
if (allocmap.exists(blocknum)) return; //Make sure we aren't wasting CPU cycles
size_t *newmap = new size_t[allocated_blocks + 1]; // Allocate a new array with one extra block
int cap = allocmap.getcapacity();
int cur = -1;
int curnewblk = 0;
while ((cur = getnext(cur)) != -1) {
if (cur != blocknum) {
newmap[curnewblk++] = map[cur]; // Copy the old blocks
} else {
newmap[curnewblk++] = 0ULL; // Allocate the new block with no value
}
} // END WHILE
//Set variables
allocated_blocks++;
delete map;
map = newmap;
} // END ALLOC(int)

};

