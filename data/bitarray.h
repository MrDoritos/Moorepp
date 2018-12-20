#include <stdlib.h>

using namespace std;
class bitarray {
public:
//size_t* getarr() { return map; }
bitarray() {
map = new size_t[1];
map[0] = 0;
allocated_blocks = 1;
}
void remove(int i) {
if (i < getcapacity()) {
map[i / blocksize] &= ~(1 << (i % blocksize));
 }
}
void add(int i) {
if (i < getcapacity()) {
map[i / blocksize] |= (1ULL << (i % blocksize));
} else {
realloc(((i)/blocksize) + 1);
add(i);
}
}
inline bool exists(int i) {
return (i < getcapacity() && (map[i/blocksize] & (1ULL << (i % blocksize))) != 0);
}
inline size_t getcapacity() { return allocated_blocks * blocksize; }
private:
void realloc(size_t blocks) {
if (blocks < allocated_blocks) return; //Make sure we aren't wasting CPU cycles and reallocating memory for no reason

//Allocate new array
size_t *newmap = new size_t[blocks];

//Zero memory
/*bzero(&newmap[allocated_blocks], sizeof(size_t) * (allocated_blocks - blocks)); //This should work I hope*/ //Did not work
for (int i = 0; i < blocks; i++) {
newmap[i] = 0ULL;
}

//Copy old blocks
for (int i = 0; i < allocated_blocks; i++) {
newmap[i] = map[i];
}

//Set variables
allocated_blocks = blocks;

//Delete old map
delete map;

map = newmap;

}
int allocated_blocks;
size_t *map;
static const int blocksize = sizeof(size_t) * 8;

};

