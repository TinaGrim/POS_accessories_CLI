#include "Items.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<Item> getItemFrom(std::string filename, int n) {
  std::ifstream infile;
  std::string name;
  std::string ID, price;
  std::string size;
  std::string line;
  int count = 0;
  infile.open(filename);
  std::vector<Item> items;

  if (!infile.is_open()) {
    return items;
  }
  while (getline(infile, line) && count < n) {
    if (line.empty())
      continue;
    Item tem;

    std::stringstream ss(line);
    getline(ss, name, ',');
    getline(ss, ID, ',');
    getline(ss, price, ',');
    getline(ss, size, ',');

    tem.name = name;
    tem.ID = std::stoul(ID);
    tem.price = std::stoul(price);
    tem.size = size;
    items.push_back(tem);
    count++;
  }
  infile.close();

  return items;
}
