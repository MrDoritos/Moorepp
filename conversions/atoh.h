#include <iostream>

//inline char __POS1(char x) { return (char((((x & 15) + 48) > 57) ? ((x & 15) + 65) : ((x & 15) + 48))); }
//inline char __POS2(char x) { return (char((((x >> 4) + 48) > 57) ? ((x >> 4) + 65) : ((x >> 4) + 48))); }

char __POS2(char x) {
if (((x & 15) + 48) > 57) {
return char((x & 15) + 87);
} else {
return char((x & 15) + 48);
}

}

char __POS1(char x) {
return __POS2((x & 240) >> 4);
}

char* atoh(char* buffer, int size) {
char* hh = new char[size*2];
for (int i = 0, b = 0; i < size; i++, b+=2) {
hh[b] = __POS1(buffer[i]);
hh[b + 1] = __POS2(buffer[i]);
}
return hh;
}
/*
std::string* atoh(char* buffer, int size) {
std::string* str = new std::string();
str->resize(size * 2);
for (int i = 0, b = 0; i < size; i++, b+=2) {
(str)[  b  ] = __POS1(buffer[i]);
(str)[b + 1] = __POS2(buffer[i]);
}
//std::cout << *str << std::endl;
return str;
}
*/
