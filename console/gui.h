#include <iostream>
#include "console.h"
#include <vector>
#include <string.h>
#include <stdlib.h>


class box {
public:
box(std::string& name, int bordercolor, int innercolor, bool transparent, int sizex, int sizey){
this->bordercolor = bordercolor;
this->innercolor = innercolor;
this->transparent = transparent;
this->sizex = sizex;
this->sizey = sizey;
}
int sizey;
int sizex;
int posy;
int posx;
int bordercolor;
int innercolor;
bool transparent;
};

class guicontext : private box {
public:
guicontext() : base (this->name, 4, 0, false)
{
windows.push_back(this);
focused = 0;
id = 1;
}
void add(box* b) {
windows.push_back(b);
}
void draw() {
for (int i = 0; i < id; i++) {
sel = windows[i];

}
}
box* getfocused() { return windows[focused]; }
void setfocused(int i) { focused = i; }
private:
void boxdraw(box* sel) {
console
}
box* sel;
static constexpr std::string name = "";
std::vector<box> windows();
int focused;
int id;
};
