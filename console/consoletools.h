#include <iostream>
#include "console.h"
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#define IN_EXIT 1
#define IN_OK 0

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
private:
bool usesignals;
static bool exiting;
static void handler(sig_t s) {
exiting = true;
}
};
