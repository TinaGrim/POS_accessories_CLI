#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <vector>

typedef struct Item {
  std::string name;
  std::string size;
  unsigned int ID;
  unsigned int price;
  unsigned int qty;
  unsigned int Amount;
} Item;
std::vector<Item> getItemFrom(std::string filename, int n);
#endif // !ITEM.H
