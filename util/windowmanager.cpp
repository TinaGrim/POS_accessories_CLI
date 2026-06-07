#include "windowmanager.h"
#include "ncurses.h"

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
  welcomeWindow = newwin(LINES / 2 - 8, welcomePadding, 0, 0);

  qrCodeWindow =
      newwin(qrcodeLength / 2 + 10, qrcodeLength + 20,
             LINES / 2 - qrcodeLength / 2, COLS / 2 - qrcodeLength / 2);
}
int windowManager::getWelcomePadding() { return welcomePadding; }
WINDOW* windowManager::getmainWindow() { return mainWindow; }
WINDOW* windowManager::getreceiptItemWindow() { return receiptItemWindow; }
WINDOW* windowManager::getItemWindow() { return ItemWindow; }
WINDOW* windowManager::getwelcomeWindow() { return welcomeWindow; }
WINDOW* windowManager::getqrCodeWindow() { return qrCodeWindow; }
