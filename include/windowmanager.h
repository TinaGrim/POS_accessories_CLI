#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "../include/Items.h"
#include "../include/mystack.h"
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
  int getWelcomeWidth();
  WINDOW* getmainWindow();
  WINDOW* getreceiptItemWindow();
  WINDOW* getItemWindow();
  WINDOW* getwelcomeWindow();
  WINDOW* getqrCodeWindow();
  void mvWinTo(WINDOW* win, int y, int x);
  void animationSlide(WINDOW* win, int des_y, int des_x);
  void drawWelcome(WINDOW* win, const wchar_t* text[]);
  void drawBorderWin(WINDOW* win);

  // -----
  // void drawBorderWin(WINDOW* win, bool drawNow);
  //
  // void drawBorder(WINDOW* win, bool drawNow);
  // void drawTeamIntro(WINDOW* win);
  // void drawReceiptTitle(WINDOW* win);
  // void drawListReceipt(WINDOW* win);
  // void createWindowItem(WINDOW* win);
  // void reDrawItem(WINDOW* win,
  //                 std::vector<std::pair<WINDOW*, Item>>& ItemElement,
  //                 unsigned int ID, unsigned qty);
  // void
  // change_selected_item_color(std::vector<std::pair<WINDOW*, Item>>&
  // ItemElement,
  //                            unsigned id);
  //
  // void drawItem(WINDOW* win, ASCstack* AS,
  //               std::vector<std::pair<WINDOW*, Item>>& ItemElement);
  // Item* getWindowItem(std::vector<std::pair<WINDOW*, Item>> ItemElement,
  //                     unsigned int id);
  // Item* getWindowItem(std::vector<std::pair<WINDOW*, Item>> ItemElement, int
  // y,
  //                     int x);
  // void initQrcode(std::string url);
};
#endif // !WINDOWMANAGER_H
