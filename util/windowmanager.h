
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "ncurses.h"

class windowManager {
private:
  int x, y;
  WINDOW* mainWindow;
  WINDOW* receiptItemWindow;
  WINDOW* ItemWindow;
  WINDOW* welcomeWindow;
  WINDOW* qrCodeWindow;
  int welcomePadding;
  int shift_left;
  int qrcodeLength;

public:
  windowManager(int shift_left, int qrcodeLength = 20);
  void init();
  int getWelcomePadding();
  WINDOW* getmainWindow();
  WINDOW* getreceiptItemWindow();
  WINDOW* getItemWindow();
  WINDOW* getwelcomeWindow();
  WINDOW* getqrCodeWindow();
};
#endif // !WINDOWMANAGER_H
