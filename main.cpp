#include <clocale>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <string>
#include <utility>
#include <vector>

#include "include/Items.h"
#include "include/mystack.h"
#include "ncurses.h"
#include "qrencode.h"
#include "util/urlpath.h"
#include "util/windowmanager.h"
#include "wchar.h"

/*
  configuration
*/
constexpr int numberItem = 21;
constexpr int shift_left = 45;
constexpr int row_perbox = 7;
constexpr int space_x = 1;
constexpr int offset_y = 8;
constexpr int Itemrows =
    ((numberItem % row_perbox == 0) ? numberItem / row_perbox
                                    : numberItem / row_perbox + 1);
constexpr int space_y = (Itemrows > 3) ? 0 : 1;

/*
  Import data
*/
const std::vector<Item> items = getItemFrom("Items.csv", numberItem);
int selected_window_id = 0;
ASCstack* ascStack = createEmptyStack();

const int receipt_offset_x = 1;
const int receipt_offset_y = 2;

const int receipt_items_offset_x = 2;
const int col_size = receipt_items_offset_x + 12;
const int col_qty = receipt_items_offset_x + 17;
const int col_price = receipt_items_offset_x + 23;
const int col_amount = receipt_items_offset_x + 30;

// clang-format off
const wchar_t* welcome[] = {
    L"██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗",
    L"██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝",
    L"██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗",
    L"██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝",
    L"╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗",
    L" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝"};
const wchar_t* team[] = {
    L"████████╗███████╗ █████╗ ███╗   ███╗    ███╗   ███╗███████╗███╗   ███╗██████╗ ███████╗██████╗ █████╗",
    L"╚══██╔══╝██╔════╝██╔══██╗████╗ ████║    ████╗ ████║██╔════╝████╗ ████║██╔══██╗██╔════╝██╔══██╗██╔══╝",
    L"   ██║   █████╗  ███████║██╔████╔██║    ██╔████╔██║█████╗  ██╔████╔██║██████╔╝█████╗  ██████╔╝█████╗",
    L"   ██║   ██╔══╝  ██╔══██║██║╚██╔╝██║    ██║╚██╔╝██║██╔══╝  ██║╚██╔╝██║██╔══██╗██╔══╝  ██╔══██╗╚══██║",
    L"   ██║   ███████╗██║  ██║██║ ╚═╝ ██║    ██║ ╚═╝ ██║███████╗██║ ╚═╝ ██║██████╔╝███████╗██║  ██║█████║",
    L"   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝    ╚═╝     ╚═╝╚══════╝╚═╝     ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝╚════╝"};
const wchar_t* tina[] = {L" ██╗       ████████╗██╗███╗   ██╗ █████╗      ",
                         L"███║       ╚══██╔══╝██║████╗  ██║██╔══██╗     ",
                         L"╚██║          ██║   ██║██╔██╗ ██║███████║     ",
                         L" ██║          ██║   ██║██║╚██╗██║██╔══██║     ",
                         L" ██║██╗       ██║   ██║██║ ╚████║██║  ██║     ",
                         L" ╚═╝╚═╝       ╚═╝   ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝     "};
const wchar_t* len[] = {L"██████╗        ██╗     ███████╗███╗   ██╗     ",
                        L"╚════██╗       ██║     ██╔════╝████╗  ██║     ",
                        L" █████╔╝       ██║     █████╗  ██╔██╗ ██║     ",
                        L"██╔═══╝        ██║     ██╔══╝  ██║╚██╗██║     ",
                        L"███████╗██╗    ███████╗███████╗██║ ╚████║     ",
                        L"╚══════╝╚═╝    ╚══════╝╚══════╝╚═╝  ╚═══╝     "};
const wchar_t* joly[] = {L"██████╗             ██╗ ██████╗ ██╗  ██╗   ██╗",
                         L"╚════██╗            ██║██╔═══██╗██║  ╚██╗ ██╔╝",
                         L" █████╔╝            ██║██║   ██║██║   ╚████╔╝ ",
                         L" ╚═══██╗       ██   ██║██║   ██║██║    ╚██╔╝  ",
                         L"██████╔╝██╗    ╚█████╔╝╚██████╔╝███████╗██║   ",
                         L"╚═════╝ ╚═╝     ╚════╝  ╚═════╝ ╚══════╝╚═╝   "};
const wchar_t* title[] = {L"  ████╗  ████╗ ████╗█████╗█████╗█████╗ ████╗ █████╗ ██╗█████╗█████╗",
                          L" ██╔═██╗██╔══╝██╔══╝██╔══╝██╔══╝██╔══╝██╔═██╗██╔═██╗██║██╔══╝██╔══╝",
                          L" ██████║██║   ██║   ███╗  █████╗█████╗██║ ██║█████╔╝██║███╗  █████╗",
                          L" ██╔═██║██║   ██║   ██╔╝  ╚══██║╚══██║██║ ██║██╔═██╗██║██╔╝  ╚══██║",
                          L" ██║ ██║╚████╗╚████╗█████╗█████║█████║╚████╔╝██║ ██║██║█████╗█████║",
                          L" ╚═╝ ╚═╝ ╚═══╝ ╚═══╝╚════╝╚════╝╚════╝ ╚═══╝ ╚═╝ ╚═╝╚═╝╚════╝╚════╝"};
const wchar_t* receipt[] = {L" ___            _      _   ",
                            L"  | _ \\___  __ ___(_)_ __| |_ ",
                            L"  |   / -_) _/ -_) | '_ \\  _|",
                            L"  |_|_\\___\\__\\___|_| .__/\\__|",
                            L"                   |_|"};
const wchar_t* receiptHeader[] = { L"█   ▀ █   ▃█▃ ",
                                   L"█   ▅ █   █▃█ ",
                                   L"█▅▅ █ █▅▅ █ █ ",
                                   L"╭────────────┬─────┬────┬──────┬───────╮",
                                   L"│Description │Size │Qty │Price │Amount │",
                                   L"╰────────────┴─────┴────┴──────┴───────╯"};

const wchar_t* receipt_footer[] = {
    L"THANK YOU FOR COMING >3",
    L"Wifi: lila@accessories123",
};

// Qrcode raw data
QRcode* qrcode;

// Qrcode string
std::wstring qr_code[40];
bool is_open_qrCode = false;

// Url Path
// std::string URL = "http://127.0.0.1:5000";
std::string URL = "https://pos-accessories-cli.onrender.com";
std::string BINARY_PATH = "";

// clang-format on
void drawBorderWin(WINDOW* win, const bool drawNow = true);
void drawBorder(WINDOW* win, const bool drawNow = true);
void drawTeamIntro(WINDOW* win);
void drawWelcome(WINDOW* win);
void drawReceiptTitle(WINDOW* win);
void drawListReceipt(WINDOW* win);
void createWindowItem(WINDOW* win,
                      std::vector<std::pair<WINDOW*, Item>>& ItemElement);

void change_selected_item_color(
    std::vector<std::pair<WINDOW*, Item>>& ItemElement, unsigned int id);

void reDrawItem(WINDOW* win, std::vector<std::pair<WINDOW*, Item>>& ItemElement,
                unsigned ID, unsigned int qty);
void drawItem(WINDOW* win, std::vector<std::pair<WINDOW*, Item>>& ItemElement);

Item* getWindowItem(std::vector<std::pair<WINDOW*, Item>> ItemElement,
                    unsigned int id);
Item* getWindowItem(std::vector<std::pair<WINDOW*, Item>> ItemElement, int y,
                    int x);

void initQrcode(std::string url);
void drawQrCode(WINDOW* win);
void addItem(WINDOW* win, Item item);
int main(int argc, char* argv[]) {
  /*
    initialization
  */
  setlocale(LC_ALL, "en_US.UTF-8");
  std::vector<std::pair<WINDOW*, Item>> ItemElement;
  initQrcode(" ");

  /*
    start ncurses
  */
  initscr();

  /*
    cursor and mouse
  */
  curs_set(0);
  start_color();
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
  MEVENT mevent;
  noecho();

  /*
    create window
  */
  windowManager WM(shift_left);
  WM.init();
  WINDOW* mainWindow = WM.getmainWindow();
  WINDOW* receiptItemWindow = WM.getreceiptItemWindow();
  WINDOW* ItemWindow = WM.getItemWindow();
  WINDOW* welcomeWindow = WM.getwelcomeWindow();
  WINDOW* qrCodeWindow = WM.getqrCodeWindow();
  createWindowItem(ItemWindow, ItemElement);
  keypad(ItemWindow, TRUE);

  /*
    init color we needed
    text color with background color
  */
  init_pair(1, COLOR_BLACK, 235);          // blck with gray
  init_pair(2, COLOR_WHITE, 243);          // white with gray
  init_pair(3, COLOR_BLACK, 15);           // black with white
  init_pair(4, COLOR_BLACK, 243);          // black with gray
  init_pair(5, 236, COLOR_WHITE);          // gray with white
  init_pair(53, 53, COLOR_WHITE);          // purple with white
  init_pair(54, COLOR_BLACK, COLOR_WHITE); // black with white
  init_pair(227, 186, 245);                // yellow with gray
  init_pair(11, COLOR_BLACK, 11);          // back with yellow
  init_pair(15, 15, 15);                   // white with white
  init_pair(22, COLOR_BLACK, 17);          // black with deepblue

  /*
    set background
  */
  wbkgd(welcomeWindow, COLOR_PAIR(53));
  wbkgd(receiptItemWindow, COLOR_PAIR(11));
  wbkgd(ItemWindow, COLOR_PAIR(3));
  wbkgd(qrCodeWindow, COLOR_PAIR(3));

  /*
    Welcome slide in animations
  */
  for (size_t i = 0; i < COLS / 2 - WM.getWelcomePadding() / 2; i++) {
    mvwin(welcomeWindow, LINES / 4, i);
    drawWelcome(welcomeWindow);
    napms(6);

    if (i == COLS / 2 - WM.getWelcomePadding() / 2 - 1)
      break;

    wclear(welcomeWindow);
    wrefresh(welcomeWindow);
    wclear(mainWindow);
    wrefresh(mainWindow);
    wbkgd(mainWindow, COLOR_PAIR(1));
  }
  /*
    clear key buffer
  */
  flushinp();
  getch();

  /*
    Welcome slide out animations
  */
  for (size_t i = 0; i < 20; i++) {
    mvwin(welcomeWindow, LINES / 4 + i,
          COLS / 2 - WM.getWelcomePadding() / 2 - 1);
    drawWelcome(welcomeWindow);
    napms(20);

    wclear(welcomeWindow);
    wrefresh(welcomeWindow);
    wclear(mainWindow);
    wrefresh(mainWindow);
    wbkgd(mainWindow, COLOR_PAIR(1));
  }

  wbkgd(mainWindow, COLOR_PAIR(3));

  /*
    Team members
  */
  drawTeamIntro(mainWindow);

  /*
    clear key buffer
  */
  flushinp();
  getch();
  wclear(mainWindow);

  wbkgd(mainWindow, COLOR_PAIR(22));

  // Border
  drawBorder(mainWindow);

  // Receipt - Item
  drawListReceipt(receiptItemWindow);

  // List Available Item
  drawItem(ItemWindow, ItemElement);
  wrefresh(ItemWindow);

  int input;
  while ((input = wgetch(ItemWindow)) != 'q') {

    switch (input) {
    case '\n':
      break;
    case 'p':
      if (!is_open_qrCode) {
        /*
          Display Qr code
        */

        initQrcode(addUrlPath(URL, toBinaryPath(ascStack, numberItem)));
        drawQrCode(qrCodeWindow);
        wrefresh(qrCodeWindow);
        is_open_qrCode = true;
      } else {
        drawItem(ItemWindow, ItemElement);
        wrefresh(ItemWindow);
        is_open_qrCode = false;
      }
      break;
    case ' ': {
      if (selected_window_id == 0) {
        break;
      }
      Item* selected = getWindowItem(ItemElement, selected_window_id);
      if (selected != nullptr) {
        change_selected_item_color(ItemElement, selected_window_id);
        addItem(receiptItemWindow, *selected);
        reDrawItem(ItemWindow, ItemElement, selected_window_id,
                   searchProduct(ascStack, selected_window_id)->qty);
        wrefresh(ItemWindow);
      }
    } break;
    case KEY_BACKSPACE: {

      if (selected_window_id == 0) {
        break;
      }
      deleteProduct(ascStack, selected_window_id);
      drawListReceipt(receiptItemWindow);
      Item* search_in_receipt = searchProduct(ascStack, selected_window_id);

      if (search_in_receipt != nullptr) {
        reDrawItem(ItemWindow, ItemElement, selected_window_id,
                   search_in_receipt->qty);
        wrefresh(ItemWindow);
      } else {

        reDrawItem(ItemWindow, ItemElement, selected_window_id, 0);
        wrefresh(ItemWindow);
      }
    } break;
    case KEY_DOWN:
      selected_window_id = (selected_window_id + row_perbox <= numberItem)
                               ? (selected_window_id + row_perbox)
                               : (selected_window_id);
      change_selected_item_color(ItemElement, selected_window_id);
      wrefresh(receiptItemWindow);
      break;
    case KEY_UP:
      selected_window_id = (selected_window_id > row_perbox)
                               ? (selected_window_id - row_perbox)
                               : (selected_window_id);
      change_selected_item_color(ItemElement, selected_window_id);
      wrefresh(receiptItemWindow);
      break;
    case KEY_LEFT:
      selected_window_id = (((selected_window_id - 1) % row_perbox) > 0)
                               ? (selected_window_id - 1)
                               : (selected_window_id);
      change_selected_item_color(ItemElement, selected_window_id);
      wrefresh(receiptItemWindow);
      break;
    case KEY_RIGHT:
      selected_window_id = (((selected_window_id % row_perbox) != 0) ||
                            (selected_window_id == 0))
                               ? (selected_window_id + 1)
                               : (selected_window_id);
      change_selected_item_color(ItemElement, selected_window_id);
      wrefresh(receiptItemWindow);
      break;

    case KEY_MOUSE:
      if (getmouse(&mevent) == OK) {
        if ((mevent.bstate & BUTTON1_RELEASED) ||
            (mevent.bstate & BUTTON1_CLICKED) ||
            (mevent.bstate & BUTTON1_DOUBLE_CLICKED) ||
            (mevent.bstate & BUTTON1_TRIPLE_CLICKED)) {
          Item* selected = getWindowItem(ItemElement, mevent.y, mevent.x);
          if (selected != nullptr) {
            selected_window_id = selected->ID;
            change_selected_item_color(ItemElement, selected_window_id);
            addItem(receiptItemWindow, *selected);
            reDrawItem(ItemWindow, ItemElement, selected_window_id,
                       searchProduct(ascStack, selected_window_id)->qty);
            wrefresh(ItemWindow);
          }
        }
      }
      break;
    default:

      break;
    }
  }

  reset_color_pairs();
  delwin(welcomeWindow);
  delwin(mainWindow);
  delwin(receiptItemWindow);
  delwin(ItemWindow);
  endwin();
  return 0;
}
void drawBorderWin(WINDOW* win, bool drawNow) {
  int x, y;
  getmaxyx(win, y, x);

  mvwaddstr(win, 0, x - 1, "╮");
  mvwaddstr(win, 0, 0, "╭");
  mvwaddstr(win, y - 1, 0, "╰");
  mvwaddstr(win, y - 1, x - 1, "╯");

  for (size_t i = 1; i < y - 1; i++) {
    mvwaddstr(win, i, 0, "│");
    mvwaddstr(win, i, x - 1, "│");
  }
  for (size_t i = 1; i < x - 1; i++) {
    mvwaddstr(win, 0, i, "─");
    mvwaddstr(win, y - 1, i, "─");
  }
  if (drawNow)
    wrefresh(win);
  refresh();
}

void drawBorder(WINDOW* win, bool drawNow) {
  int rows, cols;
  getmaxyx(win, rows, cols);
  wmove(win, 0, cols - shift_left);
  wvline(win, L'█', rows);

  if (drawNow)
    wrefresh(win);
}
void drawTeamIntro(WINDOW* win) {

  int cols, rows;
  getmaxyx(win, rows, cols);
  int ROWS = 6;
  /*
    team
  */
  for (size_t i = 0; i < ROWS; i++) {
    mvwaddwstr(win, i + rows / 9, cols / 2 - wcslen(team[0]) / 2, team[i]);
  }
  wrefresh(win);
  /*
    team + tina
  */
  for (size_t i = 0; i < 5; i++) {
    werase(win);
    for (int j = 0; j < ROWS; j++) {
      mvwaddwstr(win, j + rows / 9, cols / 2 - wcslen(team[0]) / 2, team[j]);
      mvwaddwstr(win, j + rows / 2.7, i, tina[j]);
    }
    wrefresh(win);
    napms(50);
  }
  /*
    team + tina + len
  */
  for (size_t i = 0; i < int(cols / 2) - wcslen(len[0]) / 2 - 20; i++) {
    werase(win);
    for (int j = 0; j < ROWS; j++) {
      mvwaddwstr(win, j + rows / 9, cols / 2 - wcslen(team[0]) / 2, team[j]);
      mvwaddwstr(win, j + rows / 2.7, 5, tina[j]);
      mvwaddwstr(win, j + rows / 1.8, i, len[j]);
    }
    wrefresh(win);
    napms(5);
  }
  /*
    team + tina + len + joly
  */
  for (size_t i = 0; i < cols - wcslen(joly[0]); i++) {
    werase(win);
    for (int j = 0; j < ROWS; j++) {
      mvwaddwstr(win, j + rows / 9, cols / 2 - wcslen(team[0]) / 2, team[j]);
      mvwaddwstr(win, j + rows / 2.7, 5, tina[j]);
      mvwaddwstr(win, j + rows / 1.8, int(cols / 2) - wcslen(len[0]) / 2,
                 len[j]);
      mvwaddwstr(win, j + rows / 1.3, i, joly[j]);
    }
    wrefresh(win);
    napms(1);
  }
  wrefresh(win);
}
void drawWelcome(WINDOW* win) {
  int x, y;
  getmaxyx(win, y, x);
  int ROWS = 6;
  for (int i = 0; i < ROWS; i++) {
    mvwaddwstr(win, (y / 2) - 3 + i, x / 2 - wcslen(welcome[0]) / 2,
               welcome[i]);
  }
  wattron(win, COLOR_PAIR(3));
  drawBorderWin(win);
  wattroff(win, COLOR_PAIR(3));

  wrefresh(win);
}
void drawReceiptTitle(WINDOW* win) {
  int x, y;
  getmaxyx(win, y, x);

  int ROWS = 5;
  wattron(win, COLOR_PAIR(3));
  for (int i = 0; i < ROWS; i++) {
    mvwaddwstr(win, i + 3, x - shift_left / 2 - 15, receipt[i]);
  }
  wattroff(win, COLOR_PAIR(3));
  wrefresh(win);
}
void drawListReceipt(WINDOW* win) {

  int x, y;
  int current = receipt_offset_y;
  getmaxyx(win, y, x);

  const int receipt_header_size = 6;
  int receipt_items_size = 0;
  const int receipt_footer_size = 2;
  /*
    header
  */
  for (size_t i = 0; i < receipt_header_size; i++) {
    mvwaddwstr(win, current++, receipt_offset_x, receiptHeader[i]);
  }

  /*
    Items
  */
  receipt_items_size = y - (current + 1) - 7;
  int idx = 0;
  for (size_t i = 0; i < receipt_items_size; i++) {
    Item* item = getItemAt(ascStack, idx);

    if (!(item == nullptr)) {

      if (receipt_items_size == i + 1) {
        mvwprintw(win, current, receipt_items_offset_x, "%s", "●");
        mvwprintw(win, current, receipt_items_offset_x + 2, "%-12s",
                  item->name.c_str());
        mvwprintw(win, current, col_size, "%5s", item->size.c_str());
        mvwprintw(win, current, col_qty, "%4d", item->qty);
        mvwprintw(win, current, col_price, "%6s",
                  (std::to_string(item->price) + "$").c_str());
        mvwprintw(win, current++, col_amount, "%7s",
                  (std::to_string(item->Amount) + "$").c_str());
      } else {
        mvwprintw(win, current, receipt_items_offset_x, "%s", "●");
        mvwprintw(win, current, receipt_items_offset_x + 2, "%-12s",
                  item->name.c_str());
        mvwprintw(win, current, col_size, "%5s", item->size.c_str());
        mvwprintw(win, current, col_qty, "%4d", item->qty);
        mvwprintw(win, current, col_price, "%6s",
                  (std::to_string(item->price) + "$").c_str());
        mvwprintw(win, current++, col_amount, "%7s",
                  (std::to_string(item->Amount) + "$").c_str());
        mvwprintw(win, current++, 0, "%s", "");
        i++;
      }
      idx++;
      continue;
    }
    int length = std::wcslen(receiptHeader[4]);
    mvwprintw(win, current++, 0, "%*s", length, " ");
  }
  mvwaddwstr(win, current++, receipt_items_offset_x,
             L"─────────────────────────────────────────");
  /*
    total
  */
  int total = Summation(ascStack);
  mvwprintw(win, current, receipt_items_offset_x, "TOTAL ($):");
  mvwprintw(win, current++, col_amount, "%7s",
            (std::to_string(total) + " $").c_str());

  mvwprintw(win, current, receipt_items_offset_x, "TOTAL (R):");
  mvwprintw(win, current++, col_amount - 3, "%10s",
            (std::to_string(total * 4100) + " R").c_str());

  mvwaddwstr(win, current++, receipt_items_offset_x,
             L"─────────────────────────────────────────");
  mvwprintw(win, current, receipt_items_offset_x, "(1$=4100R)");
  mvwprintw(win, current, col_qty, "By card: ");
  mvwprintw(win, current++, col_amount, "%7s",
            (std::to_string(total) + " $").c_str());
  /*
    footer
  */
  for (size_t i = 0; i < receipt_footer_size; i++) {
    int center =
        std::wcslen(receiptHeader[5]) / 2 - std::wcslen(receipt_footer[i]) / 2;
    mvwaddwstr(win, current++, center, receipt_footer[i]);
  }

  drawBorderWin(win);
  mvwaddstr(win, 0, x - shift_left / 2 - 4, "【Receipt】");
  wrefresh(win);
}
void createWindowItem(WINDOW* win,
                      std::vector<std::pair<WINDOW*, Item>>& ItemElement) {
  int cols, rows;
  int win_x_begin, win_y_begin;
  getmaxyx(win, rows, cols);
  getbegyx(win, win_y_begin, win_x_begin);

  const int box_x = int((cols - row_perbox - 1) / row_perbox);
  const int box_y = int((rows - 11) / Itemrows);
  const int length_x = (box_x + 1) * row_perbox - 1;

  int offset_x = ((cols - length_x) / 2) ? (cols - length_x) / 2 : 0;

  int COLS = 0;
  int ROWS = 0;
  for (size_t i = 0; i < items.size(); i++) {
    ROWS = i / (row_perbox);
    COLS = i % (row_perbox);

    WINDOW* newin = newwin(
        box_y, box_x, offset_y + win_y_begin + ROWS * box_y + space_y * ROWS,
        offset_x + win_x_begin + COLS * box_x + space_x * COLS);
    // wrefresh(newin);
    ItemElement.push_back({newin, items[i]});
  }
}
void reDrawItem(WINDOW* win, std::vector<std::pair<WINDOW*, Item>>& ItemElement,
                unsigned int ID, unsigned qty) {
  int cols, rows;

  getmaxyx(win, rows, cols);

  for (auto& [newin, item] : ItemElement) {
    if (item.ID == ID) {

      int win_y, win_x;
      getmaxyx(newin, win_y, win_x);

      wbkgd(newin, COLOR_PAIR(3));

      // name
      mvwaddstr(newin, (win_y % 2) ? win_y / 2 : win_y / 2 - 1,
                win_x / 2 - item.name.length() / 2, (item.name).c_str());

      std::string qtyString = std::to_string(qty);
      int qtyLength = qtyString.length();
      if (qty > 0) {
        // Quantity
        mvwaddstr(newin, (win_y % 2) ? win_y / 2 + 1 : win_y / 2,
                  win_x / 2 - qtyLength / 2, ("x" + qtyString).c_str());
      } else {

        // Quantity clear
        mvwaddstr(newin, (win_y % 2) ? win_y / 2 + 1 : win_y / 2,
                  win_x / 2 - qtyLength / 2, "     ");
      }
      // ID
      mvwaddstr(newin, 1, 1, ("#" + std::to_string(item.ID)).c_str());

      // price
      mvwaddstr(newin, win_y - 2,
                win_x - std::to_string(item.price).length() - 2,
                (std::to_string(item.price) + "$").c_str());
      wrefresh(newin);
    }
  }
  change_selected_item_color(ItemElement, ID);
}
void change_selected_item_color(
    std::vector<std::pair<WINDOW*, Item>>& ItemElement, unsigned id) {
  for (auto& [newin, item] : ItemElement) {
    if (item.ID == id) {
      wbkgd(newin, COLOR_PAIR(5));
      wrefresh(newin);
    } else {
      wbkgd(newin, COLOR_PAIR(3));
      wrefresh(newin);
    }
  }
}

void drawItem(WINDOW* win, std::vector<std::pair<WINDOW*, Item>>& ItemElement) {
  int cols, rows;

  int win_x_begin, win_y_begin;
  getmaxyx(win, rows, cols);
  getbegyx(win, win_y_begin, win_x_begin);
  drawBorderWin(win);
  int ROWS = 6;
  int COLS = 0;

  /*
    Accessories
  */
  wattron(win, COLOR_PAIR(227));
  for (size_t i = 0; i < ROWS; i++) {
    mvwaddwstr(win, i + 1, cols / 2 - wcslen(title[0]) / 2, title[i]);
  }
  wattroff(win, COLOR_PAIR(227));

  /*
    Draw all Items
  */
  for (auto& [newin, item] : ItemElement) {
    int win_y, win_x;
    getmaxyx(newin, win_y, win_x);

    wbkgd(newin, COLOR_PAIR(3));

    // name
    mvwaddstr(newin, (win_y % 2) ? win_y / 2 : win_y / 2 - 1,
              win_x / 2 - item.name.length() / 2, item.name.c_str());

    // ID
    mvwaddstr(newin, 1, 1, ("#" + std::to_string(item.ID)).c_str());

    // price
    mvwaddstr(newin, win_y - 2, win_x - std::to_string(item.price).length() - 2,
              (std::to_string(item.price) + "$").c_str());

    drawBorderWin(newin);
    wrefresh(newin);
  }
}
Item* getWindowItem(std::vector<std::pair<WINDOW*, Item>> ItemElement,
                    unsigned int id) {
  if (id < 0 || id > numberItem) {
    return nullptr;
  }

  return &ItemElement[id - 1].second;
}
Item* getWindowItem(std::vector<std::pair<WINDOW*, Item>> ItemElement, int y,
                    int x) {

  /*
    getItem from the orginal file not stack
  */
  for (auto& [WIN, item] : ItemElement) {
    int win_x, win_y;
    int win_x_begin, win_y_begin;
    getmaxyx(WIN, win_y, win_x);
    getbegyx(WIN, win_y_begin, win_x_begin);
    if (x >= win_x_begin && x <= win_x_begin + win_x && y >= win_y_begin &&
        y <= win_y_begin + win_y) {
      return &item;
    }
  }
  return nullptr;
}
void initQrcode(std::string url) {
  /*
    Remake qr_code string
  */
  qrcode = QRcode_encodeString(url.c_str(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);
  for (size_t i = 0; i < qrcode->width / 2 + 1; i++) {
    std::wstring tem;
    for (size_t j = 0; j < qrcode->width; j++) {
      int bottomidx = i * qrcode->width * 2 + j + qrcode->width;
      bool bottom = (i * 2 + 1) < qrcode->width;
      if (qrcode->data[i * qrcode->width * 2 + j] & 1) {

        if ((qrcode->data[bottomidx] & 1) && bottom) {
          tem += L"█";
        } else {
          tem += L"▀";
        }
      } else {
        if ((qrcode->data[(bottomidx)] & 1) && bottom) {
          tem += L"▄";
        } else {
          tem += L" ";
        }
      }
    }
    qr_code[i] = tem;
  }
}
void drawQrCode(WINDOW* win) {
  /*
    Draw on the screen
  */
  int x, y;
  getmaxyx(win, y, x);
  drawBorderWin(win);
  int rows = 0;
  int size = qr_code->size();
  for (auto& line : qr_code) {
    mvwaddwstr(win, y / 2 - size / 4 + rows, x / 2 - size / 2, line.c_str());
    rows++;
  }
}
void addItem(WINDOW* win, Item item) {
  /*
    Add new Item if not exist otherwise increase Quantity
  */
  if (!checkExist(ascStack, item.ID)) {
    push(ascStack, item, 1, item.price * 1);
    drawListReceipt(win);
  } else {
    addexistProduct(ascStack, item.ID);
    drawListReceipt(win);
  }
}
