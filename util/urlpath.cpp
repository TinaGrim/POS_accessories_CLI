
#include "../include/mystack.h"

std::string toBinaryPath(ASCstack* ASC, unsigned int n) {
  std::string BinaryPath;
  for (size_t i = 1; i <= n; i++) {
    Item* item = searchProduct(ASC, i);
    if (!(item == nullptr)) {
      BinaryPath += "1";
    } else {
      BinaryPath += "0";
    }
  }
  return BinaryPath;
}
std::string addUrlPath(std::string url, std::string path) {
  return url + "/items/" + path;
}
