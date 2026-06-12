#include "windowmanager.h"
#include "ncurses.h"
#include <cmath>
#include <cstddef>
#include <wchar.h>

windowManager::windowManager(int shift_left, int qrcodelength)
    : shift_left(shift_left), qrcodeLength(qrcodelength) {
  mainWindow = nullptr;
  receiptItemWindow = nullptr;
  ItemWindow = nullptr;
  welcomeWindow = nullptr;
  qrCodeWindow = nullptr;
}
void windowManager::init() {
  getmaxyx(stdscr, y, x);
  mainWindow = newwin(LINES, COLS, 0, 0);
  receiptItemWindow =
      newwin(LINES - 2, shift_left - 3, 1, COLS - shift_left + 2);
  ItemWindow = newwin(LINES - 2, COLS - shift_left - 3, 1, 2);

  welcomePadding = (COLS / 2) <= 64 ? 64 : COLS / 2 - 2;
  welcomeWindow = newwin(LINES / 2 - 8, welcomePadding, LINES / 4, 0);

  qrCodeWindow =
      newwin(qrcodeLength / 2 + 10, qrcodeLength + 20,
             LINES / 2 - qrcodeLength / 2, COLS / 2 - qrcodeLength / 2);
}
int windowManager::getWelcomeWidth() { return welcomePadding; }
WINDOW* windowManager::getmainWindow() { return mainWindow; }
WINDOW* windowManager::getreceiptItemWindow() { return receiptItemWindow; }
WINDOW* windowManager::getItemWindow() { return ItemWindow; }
WINDOW* windowManager::getwelcomeWindow() { return welcomeWindow; }
WINDOW* windowManager::getqrCodeWindow() { return qrCodeWindow; }
void windowManager::mvWinTo(WINDOW* win, int y, int x) {
  int tem_x;
  int tem_y;
  getbegyx(win, tem_y, tem_x);
  mvwin(win, tem_y + y, tem_x + x);
}
void windowManager::animationSlide(WINDOW* win, int move_y, int move_x) {

  int des_x = 0, des_y = 0;
  wbkgd(mainWindow, COLOR_PAIR(1));
  while (des_y < std::abs(move_y) || des_x < std::abs(move_x)) {
    if (des_x < std::abs(move_x)) {
      mvWinTo(win, 0, ((move_x < 0) ? -1 : 1));
      wrefresh(win);
      napms(6);
      if (des_x < (std::abs(move_x) - 1)) {
        wclear(mainWindow);
        wrefresh(mainWindow);
      }
      des_x++;
    }
    if (des_y < std::abs(move_y)) {

      mvWinTo(win, (move_y < 0 ? -1 : 1), 0);
      // drawWelcome(win, text);
      wrefresh(win);
      napms(20);

      if (des_y < (std::abs(move_y) - 1)) {
        wclear(mainWindow);
        wrefresh(mainWindow);
      }

      des_y++;
    }
  }
}
void windowManager::drawWelcome(WINDOW* win, const wchar_t* text[]) {
  int tem_x, tem_y;
  getmaxyx(win, tem_y, tem_x);
  int ROWS = 6;
  for (int i = 0; i < ROWS; i++) {
    mvwaddwstr(win, (tem_y / 2) - 3 + i, tem_x / 2 - wcslen(text[0]) / 2,
               text[i]);
  }
  wattron(win, COLOR_PAIR(3));
  drawBorderWin(win);
  wattroff(win, COLOR_PAIR(3));
  wrefresh(win);
}
void windowManager::drawBorderWin(WINDOW* win) {
  int tem_x, tem_y;
  getmaxyx(win, tem_y, tem_x);

  mvwaddstr(win, 0, tem_x - 1, "╮");
  mvwaddstr(win, 0, 0, "╭");
  mvwaddstr(win, tem_y - 1, 0, "╰");
  mvwaddstr(win, tem_y - 1, tem_x - 1, "╯");

  for (size_t i = 1; i < tem_y - 1; i++) {
    mvwaddstr(win, i, 0, "│");
    mvwaddstr(win, i, tem_x - 1, "│");
  }
  for (size_t i = 1; i < tem_x - 1; i++) {
    mvwaddstr(win, 0, i, "─");
    mvwaddstr(win, tem_y - 1, i, "─");
  }
  wrefresh(win);
}
