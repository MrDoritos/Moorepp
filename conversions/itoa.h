#include <iostream>
#include <string.h>

void itoa(int value, char* buf, int base){
std::string s = std::to_string(value);
char const *pchar = s.c_str();
for (int i = 0; i < s.length(); i++)
buf[i] = pchar[i];
}

void itoa(int value, std::string &in){
in = std::to_string(value);
}

string* itoa(int value, std::string &in){
return &(in = std::to_string(value));
}
