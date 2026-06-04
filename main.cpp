
#include <clocale>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <string>
#include <utility>
#include <vector>

#include "Items.h"
#include "mystack.h"
#include "ncurses.h"
#include "wchar.h"

constexpr int numberItem = 21;
constexpr int shift_left = 45;
constexpr int row_perbox = 7;
constexpr int space_x = 1;
constexpr int offset_y = 8;
constexpr int Itemrows =
    ((numberItem % row_perbox == 0) ? numberItem / row_perbox
                                    : numberItem / row_perbox + 1);
constexpr int space_y = (Itemrows > 3) ? 0 : 1;
const std::vector<Item> items = getItemFrom("Items.csv", numberItem);

ASCstack* ascStack = createEmptyStack();
const int receipt_offset_x = 1;
const int receipt_offset_y = 2;

const int receipt_items_offset_x = 2;
const int col_size = receipt_items_offset_x + 14;
const int col_qty = receipt_items_offset_x + 20;
const int col_price = receipt_items_offset_x + 25;
const int col_amount = receipt_items_offset_x + 32;

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
// clang-format on
const wchar_t* receipt_header[] = {L"█   █ █   ▃█▃ ",
                                   L"█   ▅ █   █▃█ ",
                                   L"███ █ ███ █ █ ",
                                   L"╭────────────┬─────┬────┬──────┬───────╮",
                                   L"│Description │Size │Qty │Price │Amount │",
                                   L"╰────────────┴─────┴────┴──────┴───────╯"};
const wchar_t* receipt_footer[] = {
    L"THANK YOU FOR COMING",
    L"Wifi: lila@accessories123",
};

// clang-format on
void drawBorderWin(WINDOW* win, const bool drawNow = true);
void drawBorder(WINDOW* win, const bool drawNow = true);
void drawTeamIntro(WINDOW* win);
void drawWelcome(WINDOW* win);
void drawReceiptTitle(WINDOW* win);
void drawListReceipt(WINDOW* win);
void createWindowItem(WINDOW* win,
                      std::vector<std::pair<WINDOW*, Item>>& ItemElement);
void drawItem(WINDOW* win, std::vector<std::pair<WINDOW*, Item>>& ItemElement);
Item* getWindowItem(std::vector<std::pair<WINDOW*, Item>> ItemElement, int y,
                    int x);
int main(int argc, char* argv[]) {
  /*
    initialization
  */
  setlocale(LC_ALL, "en_US.UTF-8");
  std::vector<std::pair<WINDOW*, Item>> ItemElement;

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
  WINDOW* win = newwin(LINES, COLS, 0, 0);
  WINDOW* receiptItem =
      newwin(LINES - 2, shift_left - 3, 1, COLS - shift_left + 2);
  WINDOW* Item_window = newwin(LINES - 2, COLS - shift_left - 3, 1, 2);

  const int welcome_width = (COLS / 2) <= 64 ? 64 : COLS / 2 - 2;
  WINDOW* welcome_window = newwin(LINES / 2 - 8, welcome_width, 0, 0);
  createWindowItem(Item_window, ItemElement);
  keypad(Item_window, TRUE);
  keypad(receiptItem, TRUE);

  // init color we needed
  init_pair(1, COLOR_BLACK, 235);          // blck with gray
  init_pair(2, COLOR_WHITE, 243);          // white with gray
  init_pair(3, COLOR_BLACK, 15);           // black with white
  init_pair(4, COLOR_BLACK, 243);          // black with gray
  init_pair(5, 236, COLOR_WHITE);          // gray with white
  init_pair(6, 177, COLOR_WHITE);          // pink with white
  init_pair(53, 53, COLOR_WHITE);          // purple with white
  init_pair(54, COLOR_BLACK, COLOR_WHITE); // black with white
  init_pair(227, 186, 245);                // 245
  init_pair(188, 188, 15);
  init_pair(252, COLOR_BLACK, 246);
  init_pair(11, COLOR_BLACK, 11);
  init_pair(15, 15, 15);          // black with white
  init_pair(22, COLOR_BLACK, 17); // black with deepblue

  /*
    set background
  */
  wbkgd(welcome_window, COLOR_PAIR(53));
  wbkgd(receiptItem, COLOR_PAIR(11));
  wbkgd(Item_window, COLOR_PAIR(3));

  /*
    Welcome
  */
  for (size_t i = 0; i < COLS / 2 - welcome_width / 2; i++) {
    mvwin(welcome_window, LINES / 4, i);
    drawWelcome(welcome_window);
    napms(6);

    if (i == COLS / 2 - welcome_width / 2 - 1)
      break;

    wclear(welcome_window);
    wrefresh(welcome_window);
    wclear(win);
    wrefresh(win);
    wbkgd(win, COLOR_PAIR(1));
  }
  /*
    clear key buffer
  */
  flushinp();
  getch();

  for (size_t i = 0; i < 20; i++) {
    mvwin(welcome_window, LINES / 4 + i, COLS / 2 - welcome_width / 2 - 1);
    drawWelcome(welcome_window);
    napms(20);

    wclear(welcome_window);
    wrefresh(welcome_window);
    wclear(win);
    wrefresh(win);
    wbkgd(win, COLOR_PAIR(1));
  }

  wbkgd(win, COLOR_PAIR(3));

  /*
    Team members
  */
  drawTeamIntro(win);

  /*
    clear key buffer
  */
  flushinp();
  getch();
  wclear(win);

  wbkgd(win, COLOR_PAIR(22));

  // Border
  drawBorder(win);

  // Receipt - Item
  drawListReceipt(receiptItem);

  // Receipt - title
  // drawReceiptTitle(win);

  // List Available Item
  drawItem(Item_window, ItemElement);

  int input;
  while ((input = wgetch(Item_window)) != 'q') {

    switch (input) {
    case '\n':
      break;
    case KEY_MOUSE:
      if (getmouse(&mevent) == OK && (mevent.bstate & BUTTON1_PRESSED)) {
        Item* selected = getWindowItem(ItemElement, mevent.y, mevent.x);

        if (selected != nullptr) {

          if (!checkExist(ascStack, selected->ID)) {
            push(ascStack, *selected, 1, selected->price * 1);
            drawListReceipt(receiptItem);
          } else {
            updateProduct(ascStack, selected->ID, selected->name,
                          selected->size, selected->price, selected->qty);
            drawListReceipt(receiptItem);
          }
        }

        wrefresh(receiptItem);
      }
      break;
    default:

      break;
    }
  }

  reset_color_pairs();
  delwin(welcome_window);
  delwin(win);
  delwin(receiptItem);
  delwin(Item_window);
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
    mvwaddwstr(win, current++, receipt_offset_x, receipt_header[i]);
  }

  /*
    Items
  */

  receipt_items_size = y - (current + 2) - 6;
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
    mvwprintw(win, current++, 0, "%s", "");
  }
  mvwaddwstr(win, current++, receipt_items_offset_x,
             L"─────────────────────────────────────────");
  /*
    total
  */
  int total = Summation(ascStack);
  mvwprintw(win, current, receipt_items_offset_x, "TOTAL ($):");
  mvwprintw(win, current++, col_amount, "%7s",
            (std::to_string(total) + "$").c_str());

  mvwprintw(win, current, receipt_items_offset_x, "TOTAL (R):");
  mvwprintw(win, current++, col_amount, "%7s",
            (std::to_string(total * 4000) + "R").c_str());

  mvwaddwstr(win, current++, receipt_items_offset_x,
             L"─────────────────────────────────────────");
  /*
    footer
  */
  for (size_t i = 0; i < receipt_footer_size; i++) {
    int center =
        std::wcslen(receipt_header[5]) / 2 - std::wcslen(receipt_footer[i]) / 2;
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
    drawBorderWin(newin, false);
    // wrefresh(newin);
    ItemElement.push_back({newin, items[i]});
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
  wrefresh(win);

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

    wrefresh(newin);
  }
}
Item* getWindowItem(std::vector<std::pair<WINDOW*, Item>> ItemElement, int y,
                    int x) {

  for (auto& [WIN, item] : ItemElement) {
    int win_x, win_y;
    int win_x_begin, win_y_begin;
    getmaxyx(WIN, win_y, win_x);
    getbegyx(WIN, win_y_begin, win_x_begin);
    win_x_begin += 1;
    win_y_begin += 1;
    if (x >= win_x_begin && x <= win_x_begin + win_x && y >= win_y_begin &&
        y <= win_y_begin + win_y) {
      return &item;
    }
  }
  return nullptr;
}
