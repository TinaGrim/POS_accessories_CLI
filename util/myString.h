#ifndef MYSTRING_H
#define MYSTRING_H

#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif // _WIN32
#include <string>
std::string getnString(int maxlen = 30);
#endif // !MYSTRING_H
