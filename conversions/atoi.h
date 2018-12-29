#include <iostream>

#define FORMAT_ERR

//ASCII ONLY
int atoi(char* buf, int* out) {
char a;
int pos = 0;
*out = 0;
bool negative = false;
if (buf[0] == '\0') {
*out = 0; return 0;
} else
 if (buf[0] == '-') {
negative = true;
}
int len = 0;
//Find length of the character array
while ((a = buf[pos++]) != '\0') {
len++;
}
pos = 0;
for (int i = len - 1; i > -1; i--) {
*out += (buf[pos++] - 48) * ((i == 0 ? 1 : (10 << i - 1)));
}
if (negative) {
*out = -(*out);
}
return 0;
}
