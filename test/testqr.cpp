#include "qrencode.h"
#include <iostream>
int main() {
  QRcode* qrcode;
  qrcode = QRcode_encodeString("hello", 0, QR_ECLEVEL_L, QR_MODE_8, 1);
  for (size_t i = 0; i < qrcode->width / 2 + 1; i++) {
    for (size_t j = 0; j < qrcode->width; j++) {
      if (qrcode->data[i * qrcode->width * 2 + j] & 1) {
        int bottomidx = i * qrcode->width * 2 + j + qrcode->width;
        bool bottom = (i * 2 + 1) < qrcode->width;

        if ((qrcode->data[bottomidx] & 1) && bottom) {
          std::cout << "█";
        } else {
          std::cout << "▀";
        }
      } else {
        if (qrcode->data[(i * qrcode->width * 2 + j + qrcode->width)] & 1) {
          std::cout << "▄";
        } else {
          std::cout << " ";
        }
      }
    }
    std::cout << std::endl;
  }
}
