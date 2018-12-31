#include <iostream>
#include "console.h"
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "itoa.h"
#define IN_EXIT 1
#define IN_OK 0

//#define QUERYINDEX std::string("Enter number.")

//bool consoletools::exiting;

class consoletools {
public:
consoletools(bool usesignals = true) {
this->usesignals = usesignals;
exiting = false;
if (usesignals) signal (SIGINT,handler);
}
int gets(std::string& query, std::string& out) {
out = std::string();
if (usesignals) std::cout << "^C + ENTER to EXIT" << std::endl;
std::cout << query << std::endl;
std::getline(std::cin,out);
if (exiting) return IN_EXIT; else return IN_OK;
}
int getmulti(std::string& query, std::string *options, int count, int& out, bool usedefault = false, int defaultvalue = 0) {
if (usesignals) std::cout << "^C + ENTER to EXIT" << std::endl;
std::cout << query << std::endl;
if (usedefault) {
std::cout << "Defaults to '" << options[defaultvalue] << "'" << std::endl;
}
for (int i = 0; i < count; i++)
std::cout << "[" << i << "] " << options[i] << std::endl;

int s;
while (true) {
out = 0;
static std::string qq = std::string("Enter index value.");
s = geti(qq, out, usedefault, defaultvalue);
if (exiting) { if (usedefault) out = defaultvalue; return IN_EXIT; }
switch (s) {
case IN_OK:
if (out >= count || out < 0) {
std::cout << "Index out of bounds." << std::endl;
break;
} else {
return IN_OK;
}
case IN_EXIT:
if (usedefault) out = defaultvalue;
return IN_EXIT;
}
}
}
int geti(std::string& query, int& out, bool usedefault = false, int defaultvalue = 0) {
if (usesignals) std::cout << "^C + ENTER to EXIT" << std::endl;
std::cout << query << std::endl;
if (usedefault) {
std::cout << "Defaults to '" << defaultvalue << "'" << std::endl;
}
int s;

while (true) {
out = 0;
s = scanf("%i", &out);
if (exiting) { if (usedefault) out = defaultvalue;  return IN_EXIT; }
switch (s) {
	//default:
	case 1:
		return IN_OK;
	default:
		if (usedefault) { out = defaultvalue; return IN_OK; }
		std::cout << "Invalid Input" << std::endl;
}
}
}
private:
bool usesignals;
static bool exiting;
static void handler(sig_t s) {
exiting = true;
}
};
