#include "./myString.h"
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__)
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif // _WIN32

std::string getnString(int maxlen) {
  char buf[31];
  curs_set(1);
  echo();
  getnstr(buf, maxlen);
  curs_set(0);
  noecho();
  return std::string(buf);
}
