#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#define ESC "\x1B["
#define COLOR 'm'

#define RESET           0
#define BOLD            1
#define UNDERLINE       4
#define INVERSE         7
#define BOLD_OFF        21
#define UNDERLINE_OFF   24
#define INVERSE_OFF     27

//COLORS
#define BLACK           0
#define RED             1
#define GREEN           2
#define YELLOW          3
#define BLUE            4
#define MAGENTA         5
#define CYAN            6
#define WHITE           7

//USE THESE WHEN DIRECTLY INTERFACING THE CONSOLE
#define BLACK_FG        30
#define SETBLACKFG      "\x1B[30m"
#define RED_FG          31
#define SETREDFG        "\x1B[31m"
#define GREEN_FG        32
#define SETGREENFG      "\x1B[32m"
#define YELLOW_FG       33
#define SETYELLOWFG     "\x1B[33m"
#define BLUE_FG         34
#define SETBLUEFG       "\x1B[34m"
#define MAGENTA_FG      35
#define SETMAGENTAFG    "\x1B[35m"
#define CYAN_FG         36
#define SETCYANFG       "\x1B[36m"
#define WHITE_FG        37
#define SETWHITEFG      "\x1B[37m"

#define BLACK_BG        40
#define RED_BG          41
#define GREEN_BG        42
#define YELLOW_BG       43
#define BLUE_BG         44
#define MAGENTA_BG      45
#define CYAN_BG         46
#define WHITE_BG        47
#define CONSOLEWIDTH console::getconsolewidth()
#define CONSOLEHEIGHT console::getconsoleheight()

struct winsize w;

class console {
public:
static void setcursorposition(int x, int y) {
if (y < int(w.ws_col)) console::setcursory(y);
if (x < int(w.ws_row)) console::setcursorx(x);
}
inline static void setbackgroundcolor(int color) {
std::cout << ESC << color + 40 << COLOR;
}
inline static void setforegroundcolor(int color) {
std::cout << ESC << color + 30 << COLOR;
}
inline static void setcursorx(int x){
std::cout << ESC << x + 1 << 'G';
}
inline static void setcursory(int y){
std::cout << ESC << y + 1 << 'H';
}
inline static void readline(std::string& str) {
std::getline(std::cin, str);
}
inline static void clear(){
std::cout << ESC << 1 << 'J';
}
inline static int getconsolewidth() { return int(w.ws_col); }
inline static int getconsoleheight() { return int(w.ws_row); }
private:
};
