#include <iostream>
#include "base64encodedecode.h"
class crypto
{
public:
crypto(char* key, int length){
this->key = key;
this->keylength = length;
}
char* encrypt(char* plaintext, int length, bool copy)
{
if (copy)
{
char* arr = new char[length];
int i=0;
if (i >= keylength) return plaintext;
for (int b = 0; b < length; b++)
{
if (!(i < keylength)) { i = 0; }
arr[b] = char(int(plaintext[b]) + int(key[i++]));
}
return arr;
}
else
{
int i = 0;
if (i >= keylength) return plaintext;
for (int b = 0; b < length; b++)
{
if (!(i < keylength)) { i = 0; }
plaintext[b] = char(int(plaintext[b]) + int(key[i++]));
}
}
}
char* decrypt(char* ciphertext, int length, bool copy)
{
int i = 0;
if (copy) {

} else {
if (i >= keylength) return ciphertext;
for (int b = 0; b < length; b++) {
if (!(i < keylength)) { i = 0; }
ciphertext[b] = char(int(ciphertext[b]) - int(key[i++]));
}

}

}
char* get_key() { return key; }
private:
char* key;
int keylength;
};
