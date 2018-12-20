#include "crypto.h"
#include "base64encodedecode.h"
#include <string>
#include <bitset>
#include <iostream>
#define NOARGS -1
#define BADARGS 256
#define KEY 1
#define DECRYPT 2
#define ENCRYPT 4
#define ENCRYPTASCII 8
using namespace std;
using namespace macaron;

crypto *cryp;

template<typename T>
struct array {
size_t length;
T **arr;
};

template<typename T>
void resize(array<T>* arr, size_t newSize) 
{
T** a = new T*[newSize];
//Zero new array from the size of the old array
for (size_t i = arr->length - 1; i < newSize; i++) {
a[i] = 0;
}
//Copy all old elements
for (size_t i = 0; i < arr->length; i++) {
a[i] = arr->arr[i];
}
delete arr->arr;
arr->length = newSize;
arr->arr = a;
}

struct params {
array<string> encryptAscii;
array<string> encryptBase64;
array<string> decryptBase64;
string* key;
bool isKeyBase64;
int ret;
};

params* parse(int argc, char** argv) {
params* n = new params();
n->encryptAscii.length = 0;
n->encryptAscii.arr = 0;
n->encryptBase64.length = 0;
n->decryptBase64.length = 0;
n->ret = 0;
string* why;
for (int i = 0; i < argc; i++) {
why = new string(argv[i]);
//cout << "Param " << i << " : " << *why << endl;
if (*why == "-k") {
	if (i < argc - 1) {
		n->key = new string(argv[++i]);
		n->isKeyBase64 = false;
		n->ret |= KEY;
	}
} else 
if (*why == "-k64") {
	if (i < argc - 1) {
		n->key = new string(argv[++i]);
		n->isKeyBase64 = true;
		n->ret |= KEY;
	}
} else
if (*why == "-e") {
	if (i < argc - 1) {
		resize<string>(&n->encryptAscii,n->encryptAscii.length+1);
		//string *m = new string(argv[++i]);
		//cout << "Addr:" << m << endl;
		//cout << "Addr:" << &(n->encryptAscii) << endl;
		//cout << "Addr:" << (n->encryptAscii.arr) << endl;
		//cout << "Addr:" << (n->encryptAscii.arr)[n->encryptAscii.length - 1] << endl;
		(n->encryptAscii.arr)[n->encryptAscii.length - 1] = (new string(argv[++i]));
		n->ret |= ENCRYPTASCII;
	}
} else
if (*why == "-e64") {
	if (i < argc - 1) {
		resize<string>(&n->encryptBase64,n->encryptBase64.length+1);
		(n->encryptBase64.arr)[n->encryptBase64.length - 1] = (new string(argv[++i]));
		n->ret |= ENCRYPT;
	}
} else
if (*why == "-d") {
	if (i < argc - 1) {
		resize<string>(&n->decryptBase64,n->decryptBase64.length+1);
		(n->decryptBase64.arr)[n->decryptBase64.length - 1] = (new string(argv[++i]));
		n->ret |= DECRYPT;
	}
}
delete why;
}
return n;
}

void printHelp() {

}

int main(int argc, char** argv)
{
params *n = parse(argc, argv);
//cout << "Parse ret: " << n->ret << " [" << bitset<32>(n->ret) << "]" << endl;
if ((n->ret & KEY) == KEY) 
{
cout << "Key" << (n->isKeyBase64 ? " (Base64)" : " (ASCII)") << ": " << *n->key << endl;
}
if ((n->ret & ENCRYPTASCII) == ENCRYPTASCII){
for (int i = 0; i < n->encryptAscii.length; i++){
cout << "Encrypt (ASCII): " << *n->encryptAscii.arr[i] << endl;
}
}
if ((n->ret & ENCRYPT) == ENCRYPT) {
for (int i = 0; i < n->encryptBase64.length; i++) {
cout << "Encrypt (Base64): " << *n->encryptBase64.arr[i] << endl;
}
}
if ((n->ret & DECRYPT) == DECRYPT) {
for (int i = 0; i < n->decryptBase64.length; i++) {
cout << "Decrypt (Base64): " << *n->decryptBase64.arr[i] << endl;
}
}
if ((n->ret & KEY) == KEY) {
crypto* cryp;
if (n->isKeyBase64) {
string ek;
Base64::Decode(*n->key, ek);
cryp = new crypto(ek.c_str(), ek.length());
} else {
cryp = new crypto(n->key->c_str(), n->key->length());
}
//Encrypt ASCII
char *b;
string *ne;
for (int i = 0; i < n->encryptAscii.length; i++) {
b = cryp->encrypt(n->encryptAscii.arr[i]->c_str(), n->encryptAscii.arr[i]->length(), true);
cout << n->encryptAscii.arr[i]->length() << endl;
ne = new string(b, n->encryptAscii.arr[i]->length());
cout << *n->encryptAscii.arr[i] << "->" << Base64::Encode(*ne) << endl;
}
//Decrypt Base64
for (int i = 0; i < n->decryptBase64.length; i++) {
ne = new string();
Base64::Decode(*n->decryptBase64.arr[i], *ne);
b = ne->c_str();
cryp->decrypt(b, ne->length(), false);
ne = new string(b,ne->length());
cout << *n->decryptBase64.arr[i] << "->" << *ne << endl;
}
} else {
printHelp();
return 1;
}
/*
string* fuck = new string("QWERTY keyboards are cool");
cout << "Plaintext: " << *fuck << endl;
int thelength = fuck->length();
string keystr = "your mom gay";
//cout << keystr.length() << endl;
const char* key = keystr.c_str();
string temp(key, keystr.length());
cout << "Key is (plaintext): " << keystr << endl;
cout << "Key is (base64): " << Base64::Encode(temp) << endl;
crypto* nigga = new crypto(key, keystr.length());
const char* b = fuck->c_str();
//cout << b << endl;
nigga->encrypt(b, thelength, false);
//for (int i = 0; i < thelength; i++)
//cout << bitset<8>(b[i]) << ' ';
//cout << endl;
string dd(b, thelength);
cout << "Encrypted (base64): " << Base64::Encode(dd) << endl;
nigga->decrypt(b, thelength, false);
//for (int i = 0; i < thelength; i++)
//cout << bitset<8>(b[i]) << ' ';
//cout << endl;
string ss(b, thelength);
cout << "Decrypted: " << ss << endl;
*/
return 0;
}
