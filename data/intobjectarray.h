//#include "jaggedbitarray.h"
#include "bitarray.h"
#include <iostream>

template<class T>
class intobjectarray {
public:
intobjectarray(size_t blocksize) {
this->blocksize = (blocksize > 0 ? blocksize : 2);

}
T* add(T* obj, int pos) {
if (allocmap.exists(pos / blocksize)) {
int index = getindex(pos);
map[index][pos % blocksize] = T;
return obj;
} else {
alloc(pos / blocksize);
return add(obj, pos)
}
}

private:
int getnext(int last) {
int cap = allocmap.getcapacity();
while ((!(allocmap.exists(++last))) && last < cap) {}
return (last < cap ? last : -1);
}
int getindex(int i) {
if (i / blocksize == 0) return 0;
int abs_blk = blocksize;
int index = -1;
int iter = -1;
while ((index = getnext(index)) != -1) { iter++; }
return iter;
}

void alloc(int blocknum) {
if (allocmap.exists(blocknum)) return;
T** newmap = new *T[allocated_blocks + 1];
int cap = allocmap.getcapacity();
int cur = -1;
int curnewblk = 0;
while ((cur = getnext(cur)) != -1) {
if (cur != blocknum) {
std::memcpy(newmap[curnewblk++], map[cur], blocksize);
} else {
newmap[curnewblk++] = new T[blocksize];
}
} // END WHILE
allocated_blocks++;
delete map;
map = newmap;
allocmap.add(blocknum / blocksize);
}
int allocated_blocks;
bitarray allocmap;
jaggedbitarray ;
size_t blocksize;
T** map;
};
