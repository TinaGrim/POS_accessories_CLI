#ifndef MYSTACK_H
#define MYSTACK_H

#include "Items.h"
#include <iostream>
#include <string>
struct ASC {
  Item item;
  ASC* next;
};

struct ASCstack {
  int size;
  ASC* top;
};

// Create Empty Stack
ASCstack* createEmptyStack();

// Check Empty
bool isEmpty(ASCstack* s);

// Push
void push(ASCstack* s, Item item);

// Pop
Item* pop(ASCstack* s);

// Get Item At
Item* getItemAt(ASCstack* s, const int n);

// READ
// void displayProducts(ASCstack* s) {
//
//   if (isEmpty(s)) {
//     return;
//   }
//
//   ASC* temp = s->top;
//
//
//   while (temp != nullptr) {
//
//
//     temp = temp->next;
//   }
// }

// SEARCH
Item* searchProduct(ASCstack* s, int searchID);

// UPDATE
bool updateProduct(ASCstack* s, int updateID, std::string name, int price);

// DELETE
bool deleteProduct(ASCstack* s, int deleteID);
#endif // !MYSTACK_H
