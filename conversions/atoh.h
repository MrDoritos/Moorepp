#include <iostream>

#define __POS1(x) ((((x & 15) + 48) < 58) ? ((x & 15) + 48) : ((x & 15) + 65))
#define __POS2(x) ((((x >> 4) + 48) < 58) ? ((x >> 4) + 48) : ((x >> 4) + 65))

std::string* atoh(char* buffer, int size) {
std::string* str = new std::string();
str->resize(size * 2);
for (int i = 0, b = 0; i < size; i++, b+=2) {
(*str)[  b  ] = __POS1(buffer[i]);
(*str)[b + 1] = __POS2(buffer[i]);
}
return str;
}
